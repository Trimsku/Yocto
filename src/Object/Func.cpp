#include "object/Func.h"
#include "backend/Interpreter.h"


obj_ptr Func::call(Interpreter & ip, ObjList && args){
	// Create new scope from closure where function was declared
	scope_ptr closure_scope = std::make_shared<Scope>(closure);
	scope_ptr previous = ip.get_scope();
	ip.enter_scope(closure_scope);

	for(size_t i = 0; i < params.size(); i++){
		if(i >= args.size() && params[i].default_val){
			ip.get_scope()->define(params[i].name, {LocalDeclType::Var, params[i].default_val});
		}else{
			ip.get_scope()->define(params[i].name, {LocalDeclType::Var, args[i]});
		}
	}

	obj_ptr return_val = nullptr;

	try {
		ip.execute_block(body.get(), ip.get_scope());
	}catch(ReturnValue & val){
		return_val = val.value ? val.value : null_obj;
	}

	// I don't `exit_scope`, because I need to move to the previous scope,
	// but not to closure

	ip.enter_scope(previous);

	return return_val;
}