#ifndef __GENERALIZED_DOMAIN_H__
#define __GENERALIZED_DOMAIN_H__

#include "common.h"
#include "state_descriptor.h"
#include "action.h"
#include "domain.h"
#include "condition.h"
#include "instruction.h"

class GeneralizedDomain{
public:
	// Instructions can be created only once but we keep the logic
	// of which actions can be programmed in each line here, so the
	// engine does not have to reason about it
	GeneralizedDomain( Domain *d, int program_lines ){
		StateDescriptor *sd = d->getStateDescriptor();
	
		_instructions_line.resize( program_lines );
		
		// Planning Actions
		vector< Action* > actions = d->getActions();
		// [2] Symmetry Breaking - Only End can be programmed in last line
		for( int i = 0; i + 1 < program_lines; i++ ){
			for( int j = 0; j < int( actions.size() ); j++ ){
				_instructions_line[ i ].push_back( new PlanningAction( actions[ j ] ) );
			}
		}
		
		// Extending planning actions with pointer instructions
        auto v_pointers = sd->getPointerNames();
        // [2] Symmetry Breaking - extra actions cannot be programmed in the last two lines
        for( int line = 0; line + 2 < program_lines; line++ ){
            for( auto p : v_pointers ){
                // zf and cf flags are indirectly modified by other pointer math updates
                if( p == "zf" or p == "cf" )
                    continue;

                //1. inc(pointer). Increase a pointer
                Action *inc_act = new Action("inc("+p+")");

                Condition *inc_cond = new Add( sd,
                        new Variable( p, "pointer", sd->getTypeID(p) ),
                        new Variable( "1", "constant", 1 ) );
                inc_act->addCondition( inc_cond );

                Operation *add_assign_op = new AddAssign( sd,
                        new Variable( p, "pointer", sd->getTypeID( p ) ),
                        new Variable( "1", "constant", 1 ) );
                inc_act->addOperation( add_assign_op );

                _extra_actions.push_back( inc_act );
                Instruction *inc_ins = new PlanningAction( inc_act );
                _instructions_line[ line ].push_back( inc_ins );

                //2. dec(pointer). Decrease a pointer
                Action *dec_act = new Action("dec("+p+")");

                Condition *dec_cond = new Subtract( sd,
                        new Variable( p, "pointer", sd->getTypeID( p ) ),
                        new Variable( "1", "constant", 1 ) );
                dec_act->addCondition( dec_cond );

                Operation * sub_assign_op = new SubtractAssign( sd,
                        new Variable( p, "pointer", sd->getTypeID( p ) ),
                        new Variable( "1", "constant", 1 ) );
                dec_act->addOperation( sub_assign_op );

                _extra_actions.push_back( dec_act );
                Instruction *dec_ins = new PlanningAction( dec_act );
                _instructions_line[ line ].push_back( dec_ins );

                /* 3. & 4. are not needed with conditional effects
                //3. test-max(pointer). Test if a pointer is pointing the last typed element
                Action *test_act = new Action( "test-max("+p+")" );

                // NO CONDITION

                Operation *test_op = new TestMax( sd, new Variable(p, "pointer", sd->getTypeID(p)),
                                                  new Variable("","constant",0));
                test_act->addOperation( test_op );

                _extra_actions.push_back( test_act );
                Instruction *test_ins = new PlanningAction( test_act );
                _instructions_line[ line ].push_back( test_ins );

                //4. cmp(pointer,0). Test if a pointer is pointing the first typed element
                Action *cmp_act = new Action("test-min("+p+")");
                // NO CONDS
                Operation *cmp_op = new Compare( sd,
                                                 new Variable( p, "pointer", sd->getTypeID( p ) ),
                                                 new Variable( "0", "constant", 0 ) );
                cmp_act->addOperation( cmp_op );

                _extra_actions.push_back( cmp_act );
                Instruction *cmp_ins = new PlanningAction( cmp_act );
                _instructions_line[ line ].push_back( cmp_ins );
                */

                for( auto p2 : v_pointers ){
                    if( p2 == "zf" or p2 == "cf" or p == p2 or sd->getPointerVarType(p) != sd->getPointerVarType(p2) )
                        continue;

                    //5. set(pointer1,pointer2). Assign pointer2 to pointer1
                    Action *set_act = new Action("set(" + p + "," + p2 + ")");
                    //NO CONDS
                    Operation *assign_op = new Assign(sd, new Variable( p, "pointer", sd->getTypeID( p )),
                                                      new Variable( p2, "pointer", sd->getTypeID( p2 ) ) );
                    set_act->addOperation(assign_op);

                    _extra_actions.push_back(set_act);
                    Instruction *set_ins = new PlanningAction(set_act);
                    _instructions_line[line].push_back(set_ins);

                    // [3] Symmetry breaking - allow to compare only in one direction
                    if( sd->getTypeID(p) >= sd->getTypeID(p2) )
                        continue;

                    //6. cmp(pointer1,pointer2). CMP instruction between two pointers
                    Action *cmp_act = new Action("cmp("+p+","+p2+")");
                    // NO CONDS
                    Operation *cmp_op = new Compare( sd,
                                                     new Variable( p, "pointer", sd->getTypeID( p ) ),
                                                     new Variable( p2, "pointer", sd->getTypeID( p2 ) ) );
                    cmp_act->addOperation( cmp_op );

                    _extra_actions.push_back( cmp_act );
                    Instruction *cmp_ins = new PlanningAction( cmp_act );
                    _instructions_line[ line ].push_back( cmp_ins );
                }
            }
        }

        // Extending planning actions with register instructions
        auto v_pred_types = sd->getPredicateTypes();
        for( auto pred_type : v_pred_types ){
            auto pred_id = sd->getTypeID( pred_type );
            auto param_var_ids = sd->getPredicateVarTypeIDs( pred_type );
            vector< string > param_var_names( param_var_ids.size() );
            for( unsigned i = 0; i < param_var_ids.size(); i++ )
                param_var_names[i] = sd->getVarName( param_var_ids[i] );
            vector< string > pointer_params;
            vector<vector<int> > param_pointer_ids = sd->computeGroundedParamIDs( param_var_names, pointer_params );

            // Add an empty param when the predicate has no parameters
            if( param_var_ids.size() == 0 ) {
                pointer_params.push_back("");
                param_pointer_ids.push_back( vector<int>() );
            }

            // [3] Symmetry breaking - allow to compare only in one direction
            for (int line = 0; line + 1 < program_lines; line++) {
                for( unsigned i = 0; i < pointer_params.size(); i++ ) {
                    auto pred1_name = pred_type + "(" + pointer_params[i] + ")";

                    /* // Not needed with conditional effects
                    //7. test-max(register). Test if a register is MAX_VAL
                    Action *test_act = new Action( "test-max("+pred1_name+")" );

                    // NO CONDITION

                    Operation *test_op = new TestMax( sd, new Variable(pred1_name, "predicate", pred_id, param_pointer_ids[i] ),
                                                      new Variable("","constant",0));
                    test_act->addOperation( test_op );

                    _extra_actions.push_back( test_act );
                    Instruction *test_ins = new PlanningAction( test_act );
                    _instructions_line[ line ].push_back( test_ins );
                    */

                    // 8. & 9. only relevant for numerical domains
                    //8. cmp(register,0). Test if a register is 0
                    Action *cmp_act = new Action("test-min("+pred1_name+")");
                    // NO CONDS
                    Operation *cmp_op = new Compare( sd,new Variable(pred1_name, "predicate", pred_id, param_pointer_ids[i] ),
                                                     new Variable( "0", "constant", 0 ) );
                    cmp_act->addOperation( cmp_op );

                    _extra_actions.push_back( cmp_act );
                    Instruction *cmp_ins = new PlanningAction( cmp_act );
                    _instructions_line[ line ].push_back( cmp_ins );

                    for (unsigned j = i + 1; j < pointer_params.size(); j++) {
                        auto pred2_name = pred_type + "(" + pointer_params[j] + ")";
                        //9. cmp(register1,register2). CMP instruction between two registers
                        Action *cmp_act = new Action("cmp(" + pred1_name + "," + pred2_name +")");
                        // NO CONDS
                        Operation *cmp_op = new Compare(sd,
                            new Variable(pred1_name, "predicate", pred_id, param_pointer_ids[i] ),
                            new Variable(pred2_name, "predicate", pred_id, param_pointer_ids[j]));
                        cmp_act->addOperation(cmp_op);

                        _extra_actions.push_back(cmp_act);
                        Instruction *cmp_ins = new PlanningAction(cmp_act);
                        _instructions_line[line].push_back(cmp_ins);
                    }
                }
            }
        }
		
		// Conditional Gotos
		// Set 4 different conditions ZF, !ZF, CF, !CF
		_conds.resize( 4 );
		_conds[ 0 ] = new Equals( sd,
		        new Variable( "zf", "pointer", sd->getTypeID( "zf" ) ),
		        new Variable( "1", "constant", 1 ) );
		_conds[ 1 ] = new Equals( sd,
		        new Variable( "zf", "pointer", sd->getTypeID( "zf" ) ),
		        new Variable( "0", "constant", 0 ) );
		_conds[ 2 ] = new Equals( sd,
		        new Variable( "cf", "pointer", sd->getTypeID( "cf" ) ),
		        new Variable( "1", "constant", 1 ) );
		_conds[ 3 ] = new Equals( sd,
		        new Variable( "cf", "pointer", sd->getTypeID( "cf" ) ),
		        new Variable( "0", "constant", 0 ) );
			
		// Only End can be programmed in last line
		for( int from = 0; from + 1 < program_lines; from++ ){
			for( int to = 0; to < program_lines; to++ ){
				// A goto cannot jump over itself or next line
				if( from == to || from+1 == to ) 
					continue;				
				for( int k1 = 0; k1 < 2; k1++ ){
					for( int k2 = 2; k2 < 4; k2++ ){
						Instruction *ins = new Goto( to );
						ins->addCond( _conds[ k1 ] );
						ins->addCond( _conds[ k2 ] );
						_instructions_line[ from ].push_back( ins );
					}
				}
			}
		}
		
		// End
		for( int i = 0; i < program_lines; i++ ){
			_instructions_line[ i ].push_back( new End() );
		}

		//cout << toString();
	}
	
	~GeneralizedDomain(){
		for( int i = 0; i < int( _instructions_line.size() ); i++ ){
			for( int j = 0; j < int( _instructions_line[ i ].size() ); j++ ){
				if( _instructions_line[ i ][ j ] ) 
					delete _instructions_line[ i ][ j ];
			}
		}
		
		for( int i = 0; i < int( _conds.size() ); i++ ){
			if( _conds[ i ] )
				delete _conds[ i ];
		}
		
		for( int i = 0; i < int( _extra_actions.size() ); i++ ){
			if( _extra_actions[ i ] )
				delete _extra_actions[ i ];
		}
	}
	
	Instruction* searchInstruction( int program_line, const string &name ){
		if( program_line >= int( _instructions_line.size() ) )
			return NULL;
		for( int i = 0; i < int( _instructions_line[ program_line ].size() ); i++ ){
			if( _instructions_line[ program_line ][ i ]->toString( false ) ==  (name+"\n") )
				return _instructions_line[ program_line ][ i ];
		}
		return NULL;
	}
	
	vector< vector< Instruction* > > getInstructions(){
		return _instructions_line;
	}
	
	vector< Instruction* > getInstructions( int program_line ){
		if( program_line >= int( _instructions_line.size() ) )
			return vector<Instruction*>();
		return _instructions_line[ program_line ];
	}
	
	Instruction* getInstruction( int program_line, int id ){
		return _instructions_line[ program_line ][ id ];
	}
	
	string toString(){
		string ret = "[GENERALIZED DOMAIN]:\n";
		for( int i = 0; i < int( _instructions_line.size() ); i++ ){
			ret += "[LINE " + to_string( i ) +"]:\n";
			for( int j = 0; j < int( _instructions_line[ i ].size() ); j++ ){
				//ret += "ID: " + to_string(j) + " ";
				ret += _instructions_line[ i ][ j ]->toString() + "\n";
			}
		}
		return ret;
	}
	
	
private:
	vector< vector< Instruction* > > _instructions_line;
	vector< Condition* > _conds;
	vector< Action* > _extra_actions;
};

#endif
