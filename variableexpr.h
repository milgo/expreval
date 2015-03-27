#ifndef __VARIABLEEXPR
#define __VARIABLEEXPR

#include "context.h"
#include "expression.h"
#include <string>

using namespace std;

template <typename T>
class Context;

template <typename T>
class Expression;

template <typename T>
class VariableExp: public Expression<T>{
public:

	T evaluate(Context<T>& context){
	    return context.lookup(_name);
	}
	
	VariableExp(string name){
	    _name = name;
	}
	
	~VariableExp(){}
	
	Expression<T>* copy() const{
	    return new VariableExp(_name);
	}
	
	Expression<T>* replace(const char* name, Expression<T>& exp){
	    if(_name == name){
	        return exp.copy();
	    }else{
	        return new VariableExp(_name);
	    }
	}
	
	string getName(){return _name;}

private:
        string _name;

};


#endif
