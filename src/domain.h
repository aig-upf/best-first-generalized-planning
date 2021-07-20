#ifndef __DOMAIN_H__
#define __DOMAIN_H__

#include "common.h"
#include "state_descriptor.h"
#include "action.h"

class Domain{
public:
	Domain( const string &name = "" ){
		_name = name;
		//_sd = NULL;
	}
		
	~Domain(){
        _action_name_to_idx.clear();
		for( int i = 0; i < int( _actions.size() ); i++ ){
			if( _actions[ i ] )
				delete _actions[ i ];
		}
        if( _sd ) delete _sd;
	}

	void setName( const string &name = "" ){
		_name = name;
	}

	void setStateDescriptor( StateDescriptor *sd ){
		_sd = sd;
	}
	
	void addAction( Action *a ){
		_actions.push_back( a );
        _action_name_to_idx[ a->getName() ] = int( _actions.size() ) - 1;
	}
	
	StateDescriptor* getStateDescriptor(){
		return _sd;
	}
	
	vector< Action* > getActions() const{
		return _actions;
	}
	
	Action* getAction( int id ){
		return _actions[ id ];
	}

	Action* getAction( const string &name = "" ){
	    auto it = _action_name_to_idx.find( name );
	    if( it == _action_name_to_idx.end() )
	        return NULL;
	    return getAction( it->second );
	}
	
	int getNumActions() const{
		return _actions.size();
	}
	
	string getName() const{
		return _name;
	}
	
	string toString() const{
		string ret = "[DOMAIN]: " + _name + "\n";
		if( _sd )
			ret += "\n" + _sd->toString();
		for( int i = 0; i < int( _actions.size() ); i++ ){
			ret += "\n" + _actions[ i ]->toString();
		}
		return ret;
	}
	
private:
	string _name;
	StateDescriptor *_sd;
	vector< Action* > _actions;
	map< string, int > _action_name_to_idx;
}; 

#endif
