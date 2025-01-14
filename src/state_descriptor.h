#ifndef __STATE_DESCRIPTOR_H__
#define __STATE_DESCRIPTOR_H__

#include "common.h"

class StateDescriptor{
public:
	StateDescriptor(){
        addPointer( "_ram", "zf" ); // zero flag
        addPointer( "_ram", "cf" ); // carry flags
	}

	virtual ~StateDescriptor(){
        _predicate_var_types.clear();
        _typed_pointers.clear();
        _type_id.clear();
        _predicate_types.clear();
        _var_types.clear();
        _pointer_names.clear();
	}
	
	int getTypeID( const string &typed_name = "" ) const{
		auto it = _type_id.find( typed_name );
		if( it == _type_id.end() )
			return -1; // typed_name does not exist
		return it->second;
	}

	// Add to the system VarType
	bool addVar( const string &var_type ){
	    if( _type_id.find( var_type ) != _type_id.end() )
	        return false;

	    _var_types.push_back( var_type );
	    int next_type_id = int( _type_id.size() );
	    _type_id[ var_type ] = next_type_id;
	    _typed_pointers[ next_type_id ] = vector<int>();
	    _var_id_to_name_idx[ next_type_id ] = int(_var_types.size())-1;
	    return true;
	}

	// Add to the system: PredicateType( VarType1, VarType2, ..., VarTypeN )
	bool addPredicate( const string &predicate_type, const vector< string > &var_types = vector<string>() ){
	    if( _type_id.find( predicate_type ) != _type_id.end() )
	        return false; // predicate_type already exists

        vector< int > var_ids;
        for( auto var : var_types ){
            auto it = _type_id.find( var );
            // If the var type does not exist add it to the system
            if( it == _type_id.end() ){
                if( !addVar( var ) )
                    return false; // error while adding a new var type
                it = _type_id.find( var );
                assert( it != _type_id.end() );
            }
            var_ids.push_back( it->second );
        }

	    _predicate_types.push_back( predicate_type );
	    int next_type_id = int(_type_id.size());
	    _type_id[ predicate_type ] = next_type_id;
	    _predicate_var_types[ next_type_id ] = var_ids;
        _pred_id_to_name_idx[ next_type_id ] = int(_predicate_types.size())-1;
	    return true;
	}

	// Add to the system: VarType pointerX
	bool addPointer( const string &pointer_type, const string &pointer_name ){
        if( _type_id.find( pointer_name ) != _type_id.end() )
            return false; // pointer_name already exists

        auto it = _type_id.find( pointer_type );
        // If the pointer type does not exist, add a new var type
        if( it == _type_id.end() ){
            if( !addVar( pointer_type ) ){
                return false; // error while adding a new var type
            }
            it = _type_id.find( pointer_type );
            assert( it != _type_id.end() );
        }

        // Add pointer name and assign id
        _pointer_names.push_back( pointer_name );
        int next_type_id = int( _type_id.size() );
        _type_id[ pointer_name ] = next_type_id;

        // Link var type with pointer id
        auto it_var = _typed_pointers.find( it->second );
        assert( it_var != _typed_pointers.end() );
        (it_var->second).push_back(next_type_id);

        _pointer_id_to_var_type[ next_type_id ] = (it_var->first);
        _pointer_id_to_typed_idx[ next_type_id ] = int((it_var->second).size())-1;
        _pointer_id_to_name_idx[ next_type_id ] = int(_pointer_names.size())-1;
		return true;
	}

	vector< int > getTypedPointerIDs( const string &type_name ) const{
        auto id = getTypeID( type_name );
        auto it_p = _typed_pointers.find( id );
        assert( it_p != _typed_pointers.end() );
	    return (it_p->second);
	}

	int getNumTypedPointers( const string &type_name ) const {
        auto id = getTypeID( type_name );
        auto it_p = _typed_pointers.find( id );
        assert( it_p != _typed_pointers.end() );
	    return int(( it_p->second ).size());
	}

	int getNumPointers() const{
	    return int(_pointer_names.size());
	}

	int getPointerVarType( int pointer_id ) const{
	    auto it = _pointer_id_to_var_type.find( pointer_id );
	    assert( it != _pointer_id_to_var_type.end() );
	    return it->second;
	}

	int getPointerVarType( const string &pointer_name ) const{
	    auto pointer_id = getTypeID( pointer_name );
	    return getPointerVarType( pointer_id );
	}

	int getPointerTypedIDX( int pointer_id ) const{
        auto it = _pointer_id_to_typed_idx.find( pointer_id );
        assert( it != _pointer_id_to_typed_idx.end() );
        return (it->second);
	}

	int getPointerTypedIDX( const string &pointer_name ) const{
	    auto pointer_id = getTypeID( pointer_name );
	    return getPointerTypedIDX( pointer_id );
	}

	int getPointerIDX( int pointer_id ) const {
        auto it = _pointer_id_to_name_idx.find( pointer_id );
        assert( it != _pointer_id_to_name_idx.end() );
        auto idx = (it->second);
        assert( (unsigned)idx < _pointer_names.size() );
        return idx;
	}

    int getPointerIDX( const string &pointer_name ) const{
        auto pointer_id = getTypeID( pointer_name );
        return getPointerIDX( pointer_id );
    }

	string getPointerName( int pointer_id ) const {
	    auto idx = getPointerIDX( pointer_id );
	    return _pointer_names[ idx ];
	}

	int getVarIDX( int var_id ) const{
        auto it = _var_id_to_name_idx.find( var_id );
        assert( it != _var_id_to_name_idx.end() );
        auto idx = (it->second);
        assert( (unsigned)idx < _var_types.size() );
        return idx;
	}

    int getVarIDX( const string &var_type ) const{
        auto var_id = getTypeID( var_type );
        return getVarIDX( var_id );
    }

	string getVarName( int var_id ) const{
	    auto idx = getVarIDX( var_id );
	    return _var_types[ idx ];
	}

    int getPredicateIDX( int pred_id ) const {
        auto it = _pred_id_to_name_idx.find( pred_id );
        assert( it != _pred_id_to_name_idx.end() );
        auto idx = (it->second);
        assert( (unsigned)idx < _predicate_types.size() );
        return idx;
    }

    int getPredicateIDX( const string &pred_type ) const{
        auto pred_id = getTypeID( pred_type );
        return getPredicateIDX( pred_id );
    }

	string getPredicateName( int pred_id ) const {
	    auto idx = getPredicateIDX( pred_id );
	    return _predicate_types[ idx ];
	}

	vector< int > getPredicateVarTypeIDs( const string &pred_type ) const{
	    int pred_id = getTypeID( pred_type );
	    assert( pred_id != -1 );
	    auto it_pred2vars = _predicate_var_types.find( pred_id );
	    assert( it_pred2vars != _predicate_var_types.end() );
	    return (it_pred2vars->second);
	}

	vector< string > getPredicateVarNames( const string &pred_type ) const{
	    auto var_ids = getPredicateVarTypeIDs( pred_type );
	    vector< string > var_names;
	    for( auto v_id : var_ids ){
            var_names.push_back( getVarName( v_id ) );
	    }
	    return var_names;
	}

	// ToDo test this function in the state descriptor tests
	void computeGroundedParams( const vector< string > &params, vector< string > &grounded_params,
                                unsigned param_idx = 0, const string &current_grounding = "" ) const{
	    assert( param_idx <= params.size() );
	    if( param_idx == params.size() ) {
	        grounded_params.push_back( current_grounding );
            return;
        }
	    auto typed_pointers = getTypedPointerIDs( params[ param_idx ] );
	    for( auto tp_id : typed_pointers ){
	        auto p_name = getPointerName( tp_id );
            // Avoid duplicate pointers as parameters (if required, add an extra pointer of the same type)
	        if( current_grounding.find(p_name) == string::npos )
                computeGroundedParams( params, grounded_params, param_idx+1,
                             current_grounding + (param_idx?",":"") + getPointerName(tp_id) );
	    }
	}

	vector< vector< int > > computeGroundedParamIDs( const vector< string > &params,
                                                     vector< string > &grounded_params ) const{
	    if( params.size() == 0u )
	        return vector<vector<int> >();
        computeGroundedParams( params, grounded_params );
        vector< vector< int > > grounded_params_ids;
        for( auto gp : grounded_params ){
            vector< int > gp_ids;
            size_t pos = 0, last_pos = 0;
            while( (pos = gp.find(",",last_pos)) != string::npos ){
                auto s = gp.substr( last_pos, pos-last_pos );
                gp_ids.push_back( getTypeID( s ) );
                last_pos = pos + 1;
            }
            gp_ids.push_back( getTypeID( gp.substr( last_pos ) ) );
            grounded_params_ids.push_back( gp_ids );
        }
        return grounded_params_ids;
	}

	void setStateVarBound( int var_id, int instance_id, int var_domain ){
	    auto var_ins = make_pair( var_id, instance_id );
	    _var_bounds[ var_ins ] = var_domain;
	}

	void setStateVarBound( const string &var_type, int instance_id, int var_domain ){
	    auto var_id = getTypeID( var_type );
        setStateVarBound( var_id, instance_id, var_domain );
	}

	int getStateVarBound( int var_id, int instance_id ) const{
	    auto var_ins = make_pair( var_id, instance_id );
	    auto it = _var_bounds.find( var_ins );
	    if( it != _var_bounds.end() )
	        return (it->second);
	    return 0;
	}

	int getStateVarBound( const string &var_type, int instance_id ) const{
	    auto var_id = getTypeID( var_type );
	    return getStateVarBound( var_id, instance_id );
	}

	bool isPointer( int id ) const{
	    return _pointer_id_to_name_idx.find( id ) != _pointer_id_to_name_idx.end();
	}

	bool isVar( int id ) const{
	    return _var_id_to_name_idx.find( id ) != _var_id_to_name_idx.end();
	}

	bool isPredicate( int id ) const{
	    return _pred_id_to_name_idx.find( id ) != _pred_id_to_name_idx.end();
	}

	bool isPointer( const string &name ) const{
	    auto id = getTypeID(name);
	    if( -1 == id ) return false;
	    return isPointer( id );
	}

	bool isPredicate( const string &name ) const{
        auto id = getTypeID(name);
        if( -1 == id ) return false;
	    return isPredicate( id );
	}

	// ToDo set a max value for predicate types; by default is MAX_VAL
	int getBound( int id, int instance_id ) const{
        int bound = MAX_VAL; // for predicates, max value allowed
        //if( isVar(id) or isPredicate(id) )
        //    bound = getStateVarBound( id, instance_id );
        if(isVar(id) )
            bound = getStateVarBound( id, instance_id );
        else if( isPointer(id) ){
            auto var_id = getPointerVarType( id );
            bound = getStateVarBound( var_id, instance_id );
        }
        return bound;
	}

	int getBound( const string &name_type, int instance_id ) const{
        auto id = getTypeID( name_type );
        return getBound( id, instance_id );
	}

	const vector< string > getPointerNames() const{
	    return _pointer_names;
	}

	const vector<string> getVarTypes() const{
	    return _var_types;
	}

    const vector<string> getPredicateTypes() const{
        return _predicate_types;
    }
	
	string toString() const{
		string ret = "[STATE DESCRIPTOR]:\n";
		ret += "POINTERS:\n";
		for( auto p : _pointer_names ){
		    auto it = _type_id.find( p );
		    assert( it != _type_id.end() );
		    ret += "\t" + p + ": " + to_string(it->second) + "\n";
		}
		ret += "VARIABLE TYPES:\n";
		for( auto var : _var_types ){
		    auto it = _type_id.find( var );
		    assert( it != _type_id.end() );
		    auto it_p = _typed_pointers.find( it->second );
		    assert( it_p != _typed_pointers.end() );
            ret += "\t" + var + ": with id " + to_string(it->second) + " and " +
                    ((it_p->second).size()?"pointers:":"no pointers");
		    for( auto p_ids : (it_p->second) ){
		        ret += " " + to_string(p_ids) + ";" ;
		    }
		    ret +="\n";
		}
		ret += "PREDICATE TYPES:\n";
		for( auto pred : _predicate_types ){
		    auto it_pred2id = _type_id.find( pred );
		    assert(it_pred2id != _type_id.end());
		    auto it_pred2vars = _predicate_var_types.find( it_pred2id->second );
		    assert(it_pred2vars != _predicate_var_types.end() );
		    ret += "\t" + pred + ": with id " + to_string(it_pred2id->second) +
		            " and " + ((it_pred2vars->second).size()?"variable types:":"no variable types");
		    for( auto v : (it_pred2vars->second)){
		        ret += " " + to_string(v) ;
		    }
		    ret += "\n";
		}

		return ret;
	}

private:
    // TYPE NAMES
    vector< string > _pointer_names; // POINTER NAMES
    vector< string > _var_types; // VAR NAMES
	vector< string > _predicate_types; // PREDICATE NAMES
	// TYPE to ID
    map< string, int > _type_id; // MAP OF TYPES TO IDs
    // ID to list of IDs
    map< int, vector<int> > _typed_pointers; // VAR TYPE ID -> LIST OF TYPED POINTERS IDs
	map< int, vector<int> > _predicate_var_types; // PRED TYPE ID -> LIST OF TYPED VARS IDs
	// ID to IDX (for name retrieval)
	map< int, int > _pointer_id_to_var_type; // POINTER ID -> VAR TYPE ID
	map< int, int > _pointer_id_to_typed_idx; // POINTER ID -> VAR TYPE POINTER IDX
	map< int, int > _pointer_id_to_name_idx; // POINTER ID -> NAME IDX
	map< int, int > _var_id_to_name_idx; // VAR ID -> NAME (TYPE) IDX
	map< int, int > _pred_id_to_name_idx; // PRED ID -> NAME (TYPE) IDX
	// POINTER/VAR/PRED BOUNDS FOR EACH INSTANCE
	map< pair<int,int>, int > _var_bounds; // (POINTER/VAR/PRED) ID & INSTANCE ID -> VAR BOUND
}; 

#endif
