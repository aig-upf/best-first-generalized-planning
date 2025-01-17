#define VALIDATOR
//#define DEBUG
#include "common.h"
#include "variable.h"
#include "state_descriptor.h"
#include "state.h"
#include "expression.h"
#include "condition.h"
#include "operation.h"
#include "action.h"
#include "domain.h"
#include "instance.h"
#include "parser.h"
#include "generalized_planning_problem.h"
#include "program_state.h"
#include "instruction.h"
#include "program.h"
#include "node.h"
#include "generalized_domain.h"
#include "heuristic.h"
#include "engine.h"


int main(  int argc, const char* argv[] ){
	if( argc < 3 ){
		cout << "[ERROR] Incorrect input." << endl;
		cout << "[INFO] Execute: ./validator.bin <program_file> <problem_folder/> (INF|NOINF)?" << endl;
		cout << "[INFO] Example: ./validator.bin triangular-sum.prog domains/validation/triangular-sum/" << endl;
		cout << "[INFO] The domain file must be domain.txt with all instances numbered from 1.txt to [n].txt" << endl;
		return -1;
	}

    int precision = 3;
    cout.setf( ios::fixed );
    cout.precision( precision );

    time_t start, parse_time;
    time( &start );

	bool infinite_detection = true;
	
	if( argc == 4 && string(argv[ 3 ]) == "NOINF" ){
		infinite_detection = false;
		cout << "[INFO] Validating without INFINITE detection." << endl;
	}
	else cout << "[INFO] Validating with INFINITE detection." << endl;

	string program_file = string( argv[ 1 ] );
	ifstream ifs_program( program_file );
	
	if( !ifs_program ){
		cout << "[ERROR] the program " << program_file << " does not exist." << endl;
		return -1;
	}
	
	vector< string > program_instructions;
	string instruction;
	while( getline( ifs_program, instruction ) ){
		if( instruction.size() == 0u ) continue;
		instruction = instruction.substr( instruction.find_first_of( ". " ) + 2 );
		program_instructions.push_back( instruction );
	}
		
	int program_lines = int( program_instructions.size() );	
	
	string problem_folder = string( argv[ 2 ] );
	ifstream ifs_domain( problem_folder + "domain.txt" );
	if( !ifs_domain ){
		cout << "[ERROR] domain.txt does not exist." << endl;
		return -2;
	}
	ifs_domain.close();
	
	Parser *parser = new Parser();
	Domain *dom = new Domain();
		
	if( !parser->parseDomain( dom, problem_folder + "domain.txt" ) ){
		cout << "[ERROR] while parsing domain.txt" << endl;
		delete dom;
		delete parser;
		return -3;
	}

    time( &parse_time );
    cout << "[INFO] Parsed domain. [" << difftime( parse_time, start ) << "]" << endl;
	
	// Generating the GP problem
	GeneralizedPlanningProblem *gpp = new GeneralizedPlanningProblem();
	gpp->addDomain( dom );
	
	int i = 1;	
	while( true ){
		Instance *ins = new Instance();
		string input_instance = problem_folder + to_string( i ) + ".txt";
		i++;
		
		ifstream ifs_instance( input_instance );
		if( !ifs_instance ){
			delete ins;
			break;
		}
		ifs_instance.close();
		
		if( parser->parseInstance( dom, ins, input_instance, i-2 ) )
			gpp->addInstance( ins );
		else{
			delete ins;
			cout << "[ERROR] while parsing " << input_instance << endl;
			return -4;
		}
	}

    time_t gpp_time;
    time( &gpp_time );
    cout << "[INFO] Generalized Planning Problem created. [" << difftime( gpp_time, parse_time ) << "]" << endl;
	
	GeneralizedDomain *gd = new GeneralizedDomain( dom, program_lines );

    time_t gd_time;
    time( &gd_time );
    cout << "[INFO] Generalized Domain created. [" << difftime( gd_time, gpp_time ) << "]" << endl;
			
	Program *p = new Program( program_lines );
	for( int i = 0; i < program_lines; i++ ){
		Instruction *ins = gd->searchInstruction( i, program_instructions[ i ] );
		if( ins == NULL ){
			cout << "[ERROR] Instruction " << program_instructions[ i ] << " not found." << endl;
			return -5;
		}
		p->setInstruction( i, ins );
	}

	time_t prog_time;
	time( &prog_time );
	cout << "[INFO] Program loaded. [" << difftime( prog_time, gd_time ) << "]" << endl;
	cout << "[INFO] Read program: " << endl;
	cout << p->toString( false ) << endl;
	
	vector< ProgramState* > vps = p->run( gpp, infinite_detection );
	if( int( vps.size() ) > 0 ){
		for( int i = 0; i < int( vps.size() ); i++ ){
			#ifdef DEBUG
			cout << "INSTANCE #" << (i+1) << endl;
			//cout << vps[ i ]->toString(dom->getStateDescriptor()) << endl;
			#endif
			if( vps[ i ] )
				delete vps[ i ];
		}
		cout << "[INFO] GOAL ACHIEVED!" << endl;
	}
	else{
		cout << "[INFO] INVALID GENERAL PLAN :(" << endl;
	}

	time_t end_time;
	time( &end_time );
	cout << "[INFO] Total time: " << difftime(end_time, start ) << endl;
		
	if( p ) delete p;
	if( gd ) delete gd;
	if( gpp ) delete gpp;
	if( parser ) delete parser;
}
