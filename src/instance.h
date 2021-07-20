#ifndef __INSTANCE_H__
#define __INSTANCE_H__

#include "common.h"
#include "state.h"
#include "condition.h"

class Instance{
public:
	Instance( const string &name = "", int instance_id = 0 ){
		_name = name;
		_init = NULL;
		_instance_id = instance_id;
	}
	
	~Instance(){
		if( _init ) delete _init;

		for( int i = 0; i < int( _goal.size() ); i++ ){
			if( _goal[ i ] )
				delete _goal[ i ];
		}
		_goal.clear();
	}
	
	void setName( const string &name = "" ){
		_name = name;
	}
	
	void setInitialState( State *init ){
		_init = init;
		_init->setInstanceID( _instance_id );
	}
	
	void setGoalCondition( vector< Condition* > &goal ){
		_goal = goal;
	}
	
	void addCondition( Condition* cond ){
		_goal.push_back( cond );
	}
	
	string getName() const{
		return _name;
	}
	
	State* getInitialState(){
		return _init;
	}
	
	vector< Condition* > getGoalCondition(){
		return _goal;
	}
	
	Condition* getCondition( int id ){
		return _goal[ id ];
	}

	void addObject( StateDescriptor *sd, const string &name, const string &obj_type ){
	    auto num_of_objects = sd->getStateVarBound( obj_type, _instance_id );
	    assert( obj_to_type.find( name ) == obj_to_type.end() );
	    obj_to_type[ name ] = obj_type;
	    obj_to_address[ name ] = num_of_objects;
	    sd->setStateVarBound( obj_type, _instance_id, num_of_objects+1 );
	}

	string getObjectType( const string &obj_name ) const{
	    auto it = obj_to_type.find( obj_name );
	    assert( it != obj_to_type.end() );
	    return it->second;
	}

	int getObjectAddress( const string &obj_name ) const{
	    auto it = obj_to_address.find( obj_name );
	    assert( it != obj_to_address.end() );
	    return it->second;
	}

	void setInstanceID( int instance_id ){
	    _instance_id = instance_id;
	    if( _init ) _init->setInstanceID( _instance_id );
	}

	int getInstanceID() const {
	    return _instance_id;
	}

	// Full info printing
	string toString() const{
		string ret = "[INSTANCE]: " + _name + "\n";

        ret += "\nOBJECTS:\n";
        for( auto it : obj_to_type ){
            auto it2 = obj_to_address.find(it.first);
            ret += (it.first) + ":" + (it.second) +" @" + to_string(it2->second) +"\n";
        }

		ret += "\nINIT:\n";
		if( _init )
			ret += _init->toString();

		ret += "\nGOAL:\n";
		for( int i = 0; i < int( _goal.size() ); i++ )
			ret += _goal[i]->toString();
		return ret;
	}

	// Pretty printing
	string toString( StateDescriptor *sd ){
		string ret = "[INSTANCE]: " + _name + "\n";

		ret += "\nOBJECTS:\n";
		for( auto it : obj_to_type ){
		    ret += (it.first) + ":" + (it.second) +" @" + to_string(obj_to_address[ (it.first) ]) +"\n";
		}
		
		ret += "\nINIT:\n";
		if( _init )
			ret += _init->toString( sd );
		ret += "\nGOAL:\n";
		for( int i = 0; i < int( _goal.size() ); i++ )
			ret += _goal[i]->toString( false ) + "\n";
		return ret;
	}
	
private:
	string _name;
	State *_init;
	vector< Condition* > _goal;
	int _instance_id;
	map< string, string > obj_to_type;
	map< string, int > obj_to_address;
};

#endif
