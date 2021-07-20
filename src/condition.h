#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "common.h"
#include "variable.h"
#include "state_descriptor.h"
#include "state.h"
#include "expression.h"

class Condition : public Expression{
public:
	// Non-parameterized actions
	Condition( StateDescriptor *sd, const string &name = "", Variable *lhs = 0, Variable *rhs = 0 ) : Expression( name, lhs, rhs ){
	    _sd = sd;
	}

	virtual ~Condition(){}
	
	virtual bool evalCondition( const State *s ) const{
		return true;
	}

	virtual string toString( bool titled = true ) const{
		string ret = "";
		if( titled ){
			ret += "[CONDITION]: ";
		}
		ret += "( " + _lhs->toString() + " " + _name + " " + _rhs->toString() + " )";
		if( titled ) ret+= "\n";
		return ret;
	}

protected:
    StateDescriptor *_sd;
};

class GreaterEqual : public Condition{
public:
	GreaterEqual( StateDescriptor *sd, Variable *lhs, Variable *rhs ) : Condition( sd, ">=", lhs, rhs ) {}
	
	virtual ~GreaterEqual(){}
	
	virtual bool evalCondition( const State *s ) const{
		int lhs = getLHS( _sd, s );
		int rhs = getRHS( _sd, s );
		return lhs >= rhs;
	}

}; 

class LesserEqual : public Condition{
public:
	LesserEqual( StateDescriptor *sd, Variable *lhs, Variable *rhs ) : Condition( sd, "<=", lhs, rhs ) {}
	
	virtual ~LesserEqual(){}
	
	virtual bool evalCondition( const State *s ) const{
		int lhs = getLHS( _sd, s );
		int rhs = getRHS( _sd, s );
		return lhs <= rhs;
	}

}; 
class Greater : public Condition{
public:
	Greater( StateDescriptor *sd, Variable *lhs, Variable *rhs ) : Condition( sd, ">", lhs, rhs ) {}
	
	virtual ~Greater(){}
	
	virtual bool evalCondition( const State *s ) const{
		int lhs = getLHS( _sd, s );
		int rhs = getRHS( _sd, s );
		return lhs > rhs;
	}

}; 

class Lesser : public Condition{
public:
	Lesser( StateDescriptor *sd, Variable *lhs, Variable *rhs ) : Condition( sd, "<", lhs, rhs ) {}
	
	virtual ~Lesser(){}
	
	virtual bool evalCondition( const State *s ) const{
		int lhs = getLHS( _sd, s );
		int rhs = getRHS( _sd, s );
		return lhs < rhs;
	}

}; 

class Equals : public Condition{
public:
	Equals( StateDescriptor *sd, Variable *lhs, Variable *rhs ) : Condition( sd, "=", lhs, rhs ) {}
	
	virtual ~Equals(){}
	
	virtual bool evalCondition( const State *s ) const{
		int lhs = getLHS( _sd, s );
		int rhs = getRHS( _sd, s );
		return lhs == rhs;
	}

}; 

class Add : public Condition{
public:
	Add( StateDescriptor *sd, Variable *lhs, Variable *rhs ) : Condition( sd, "+", lhs, rhs ){}
	
	virtual ~Add(){}
	
	virtual bool evalCondition( const State *s ) const{
		int lhs = getLHS( _sd, s );
		int rhs = getRHS( _sd, s );
		auto bound = _sd->getBound( _lhs->getID(), s->getInstanceID() );
		return lhs + rhs < bound;
	}
}; 

class Subtract : public Condition{
public:
	Subtract( StateDescriptor *sd, Variable *lhs, Variable *rhs ) : Condition( sd, "-", lhs, rhs ) {}
	
	virtual ~Subtract(){}
	
	virtual bool evalCondition( const State *s ) const{
		int lhs = getLHS( _sd, s );
		int rhs = getRHS( _sd, s );
		return lhs >= rhs;
	}

}; 

class Different : public Condition{
public:
	Different( StateDescriptor *sd, Variable *lhs, Variable *rhs ) : Condition( sd, "!=", lhs, rhs ) {}
	
	virtual ~Different(){}
	
	virtual bool evalCondition( const State *s ) const{
		int lhs = getLHS( _sd, s );
		int rhs = getRHS( _sd, s );
		return lhs != rhs;
	}

};

#endif
