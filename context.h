#ifndef __CONTEXT
#define __CONTEXT

#define MAX_VARIABLES 50
#define MAX_FUNCTIONS 5

#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>
#include "variableexpr.h"

using namespace std;

template <typename T>
class VariableExp;

template <typename T>
class Context{
      
public:

	Context(){
	    n = 0;	    
		_var_count = 0;
		_func_count = 0;
	}
	
	~Context(){                      
	}
	
	T lookup(string varName){
	    
	    int i = getVarIndex(varName);
	    if(!assigned[i]){
	    	throw string("Variable " + varName + " not assigned");
	        return 0;
		}
	    
	    return value[i];
	}
	
	void createVar(VariableExp<T>* v){
	    if(n > MAX_VARIABLES - 1)return;
	    _varName[n] = v->getName();
	    assigned[n] = false;
	    n++;
	}
	
	void createVar(string varName){
	    if(n > MAX_VARIABLES - 1)return;
	    if(getVarIndex(varName) < n)
            throw string( "Duplicate variable name: " + varName);
	    _varName[n] = varName;
	    assigned[n] = false;
	    n++;
	}
	
	void createFunc(string funcName, string (*funcPtr)(string)){
         if(_func_count > MAX_FUNCTIONS - 1)return;
         if(getFuncIndex(funcName) < _func_count)
            throw string( "Duplicate func name: " + funcName);
         _funcName[_func_count] = funcName;
         _funcPointers[_func_count] = funcPtr;
         _func_count++;
    }
    
    string callFunc(string funcName, string param){
         return(*_funcPointers[getFuncIndex(funcName)])(param);
    }
	
	void assignVar(VariableExp<T>* v, T x){
		assignVar(v->getName(), x);
	}
	
	void assignVar(string varName, T x){
		int i = getVarIndex(varName);
		value[i] = x;
		assigned[i] = true;
		cout << "var " << varName << " = "<< value[i] << endl;
	}
	
    string getNewVarName(){
  		return Util::intToStr(_var_count++);
    }
    
    void deleteVariables(){
        for(int i=0; i<MAX_VARIABLES; i++)
            _varName[i]="";
        _var_count = 0;
        n = 0;
    }
       
private:
       string _varName[MAX_VARIABLES];
       string _funcName[MAX_FUNCTIONS];       
       string(*_funcPointers[MAX_FUNCTIONS])(string);
       
       T value[MAX_VARIABLES];
       bool assigned[MAX_VARIABLES];
       
       int _var_count;
       int _func_count;
       int n;
       
       
       int getVarIndex(string varName)
	   {
	   		int i;
	   		for(i=0; i<MAX_VARIABLES; i++)
			{
	       		if(_varName[i].length() == 0)
					break;
	        	if(_varName[i] == varName)return i;;
	    	}
	    
	    	if(i == MAX_VARIABLES - 1){
	        	throw string( "Variable " + varName + " not declared");
	         	return 0;
	    	}
	    	
	    	return i;
	   }
	   
	   int getFuncIndex(string funcName)
	   {
	   		int i;
	   		for(i=0; i<MAX_FUNCTIONS; i++)
			{
	       		if(_funcName[i].length() == 0)
					break;
	        	if(_funcName[i] == funcName)return i;
	    	}
	    
	    	if(i == MAX_FUNCTIONS - 1){
	        	throw string( "Function " + funcName + " not declared");
	         	return 0;
	    	}
	    	
	    	return i;
	   }
};


#endif
