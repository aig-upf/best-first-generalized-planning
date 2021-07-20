#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "common.h"
#include "program_state.h"
#include "instruction.h"
#include "generalized_planning_problem.h"

class Program{
public:
	Program( int program_lines = 1 ){
        assert( program_lines >= 1 );
		_instructions = vector<Instruction*>( program_lines, NULL );
        _num_of_steps = 0;
	}
	
	Program( Program* p ){
		vector< Instruction* > vi = p->getInstructions();
		_instructions.resize( vi.size() );
		for( int i = 0; i < int( _instructions.size() ); i++ )
			_instructions[ i ] = vi[ i ];
        _num_of_steps = 0;
	}
	
	~Program(){
	}
	
	Program* copy(){
		return new Program( this );
	}
	
	vector< Instruction* > getInstructions() const{
		return _instructions;
	}
	
	void setInstruction( int pl, Instruction* ins ){
	    assert( pl < int( _instructions.size() ) );
		_instructions[ pl ] = ins;
	}
	
	Instruction* getInstruction( int pl ){
	    assert( pl < int( _instructions.size() ) );
		return _instructions[ pl ];
	}
	
	int getNumInstructions() const{
		return int( _instructions.size() );
	}
	
	bool haltingCondition( ProgramState* ps, int &error ){
		int line = ps->getLine();
		// EMPTY line is a halting condition (no transition defined)
		if( _instructions[ line ] == NULL ){
			return true;
		}

		// Either True or False evaluation of End instructions is a halting condition
		End* ins_end = dynamic_cast< End* > ( _instructions[ line ] );
		if( ins_end ) return true;

        // Conditional effects, actions do not have to be necessarily applicable
		// (OLD) If it's a planning action, it must be applicable
		/*PlanningAction* ins_act = dynamic_cast< PlanningAction* > ( _instructions[ line ] );
		if( ins_act && !ins_act->isApplicable( ps ) ){
            #ifdef VALIDATOR
		    cout << ps->toString() << endl;
		    cout << ins_act->toString() << endl;
            #endif
			error = -2; // ERROR 2: inapplicable instruction
			return true;
		}*/
		
		return false;
	}
	
	bool checkGoal( ProgramState *ps, Instance *ins, int &error ){
		int line = ps->getLine();
		if( _instructions[ line ] == NULL ) return false;
		End *end = dynamic_cast<End*>( _instructions[ line ] );
		if( end and !end->isGoalState( ins, ps ) ){
            #ifdef DEBUG
			cout << ps->toString() << endl;
            #endif
			error = -1; // ERROR 1: Incorrect program
			return false;
		}
		return false;
	}
	
	vector< ProgramState* > run( GeneralizedPlanningProblem *gpp, bool infinite_detection = true ){
        _num_of_steps = 0;

		int num_instances = gpp->getNumInstances();
		StateDescriptor *sd = (gpp->getDomain())->getStateDescriptor();
		
		// One program state per instance
		vector< ProgramState* > pss( num_instances ) ;
		for( int i = 0; i < num_instances; i++ )
			pss[ i ] = new ProgramState();


        #ifdef VALIDATOR
        time_t start_instance, end_instance;
        time( &start_instance );
        #endif
        int errors = 0;
        for( int id = 0; id < num_instances; id++ ){
			// Initialize local initial state
			Instance *ins = gpp->getInstance( id );			
			ProgramState *ps = pss[ id ];
			State *s = ( ins->getInitialState() )->copy();
			int line = ps->getLine();
			ps->setState( s );
			
			// For detecting infinite loops
			// (it can be enhanced with a hash or bigint identifier)
			set< vector<int> > visited;
			int error = 0;

			while( !haltingCondition( ps, error ) ){
				if( infinite_detection ){
					// Checking infinite loop
					Goto *g = dynamic_cast<Goto*>( _instructions[ line ] );
					if( g ){
						vector<int> state_id = ps->asVector();
						// Infinite loop detected
						if( visited.find( state_id ) != visited.end() ){
							error = -3; // ERROR 3: Infinite program
							break;
						}
						visited.insert( state_id ); 
					}
				}
				
				// Retrieving program line
				line = ps->getLine();
                //cout << ps->toString(sd) << endl;
				// Applying current instruction						
				int res = _instructions[ line ]->apply( ps );
				_num_of_steps++;

				// Mathematical planning actions update zero and carry flag
				PlanningAction *act = dynamic_cast< PlanningAction* >( _instructions[ line ] );				
				if( act && act->getType() == "math" ){
					s->setPointer(sd, "zf", ( res == 0 ?1:0) ); // zero-flag
					s->setPointer(sd, "cf", ( res > 0 ? 1:0) ); // carry-flag
				}
			}
			
			checkGoal( ps, ins, error );
			
			// [ENHANCEMENT] Continue execution in validation for coverage metric
			#ifdef VALIDATOR
            time(&end_instance);
			if( error < 0 ){
			    errors++;
				cout << "INSTANCE #" << (id+1) << " ERROR " << error << "... :( [" << difftime(end_instance,start_instance) << "]" << endl;
				//for( int i = 0; i < int( pss.size() ); i++ ){
				//    cout << pss[i]->toString( sd ) << endl;
				//}
			}
			else
				cout << "INSTANCE #" << (id+1) << " SOLVED! [" << difftime(end_instance,start_instance) <<"]" << endl;
			start_instance = end_instance;
            #else
            if( error < 0 ){
                errors++;
                break;
                /*for( int i = 0; i < int( pss.size() ); i++ ){
                    //cout << pss[i]->toString( sd ) << endl;
                    if( pss[i] ) delete pss[i];
                }
                return vector<ProgramState*>();*/
            }
			#endif
		}

        if( errors ){
            for( int i = 0; i < int( pss.size() ); i++ ){
                if( pss[i] ) delete pss[i];
            }
            return vector<ProgramState*>();
        }
		
		return pss;
	}

	int getNumOfSteps() const{
	    return _num_of_steps;
	}
	
	string toString( bool full_info = true ) const{
		string ret = "";
		if( full_info ){
			ret = "[PROGRAM]:\n";
			for( int i = 0; i < int( _instructions.size() ); i++ ){
				ret += "LINE " + to_string( i ) + ": ";
				if( _instructions[ i ] != NULL ) 
					ret += _instructions[ i ]->toString();
				else ret += "[INSTRUCTION] EMPTY\n";
			}
		}
		else{
			for( int i = 0; i < int( _instructions.size() ); i++ ){
				ret += to_string( i ) + ". ";
				if( _instructions[ i ] != NULL )
					ret += _instructions[ i ]->toString( full_info );
				else ret += "empty\n";
			}
		}
		return ret;
	}
	
private:
	vector< Instruction* > _instructions;
	int _num_of_steps;
};

#endif
