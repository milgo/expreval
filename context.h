#ifndef __CONTEXT
#define __CONTEXT

#define MAX_VARIABLES 50

#include <map>
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
	}
	
	~Context(){                      
	}
	
	T lookup(string varname){
	    
	    int i = getVarIndex(varname);
	    if(!assigned[i]){
	    	throw string("Variable " + varname + " not assigned");
	        return 0;
		}
	    
	    return value[i];
	}
	
	void createVar(VariableExp<T>* v){
	    if(n > MAX_VARIABLES - 1)return;
	    name[n] = v->getName();
	    assigned[n] = false;
	    n++;
	}
	
	void createVar(string varname){
	    if(n > MAX_VARIABLES - 1)return;
	    name[n] = varname;
	    assigned[n] = false;
	    n++;
	}
	
	void assignVar(VariableExp<T>* v, T x){
		assignVar(v->getName(), x);
	}
	
	void assignVar(string varname, T x){
		int i = getVarIndex(varname);
		value[i] = x;
		assigned[i] = true;
	}
       
private:
       string name[MAX_VARIABLES];
       T value[MAX_VARIABLES];
       bool assigned[MAX_VARIABLES];
       int n;
       
       
       int getVarIndex(string varname)
	   {
	   		int i;
	   		for(i=0; i<MAX_VARIABLES; i++)
			{
	       		if(name[i].length() == 0)
				{
					break;
				}
	        	if(name[i] == varname)break;
	    	}
	    
	    	if(i == n){
	        	throw string( "Variable " + varname + " not declared");
	         	return 0;
	    	}
	    	
	    	return i;
	   }
};


#endif
