#ifndef __EXPREVAL
#define __EXPREVAL

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>

#include "context.h"
#include "expression.h"
#include "variableexpr.h"
#include "sumexpression.h"
#include "subexpression.h"
#include "mulexpression.h"
#include "divexpression.h"

using namespace std;

enum EXPR_EVAL_ERR {
	EEE_NO_ERROR = 0,
	EEE_PARENTHESIS = 1,
	EEE_WRONG_CHAR = 2,
	EEE_DIVIDE_BY_ZERO = 3
};

typedef char EVAL_CHAR;

class ExprEval {
private:
	EXPR_EVAL_ERR _err;
	EVAL_CHAR* _err_pos;
	int _paren_count;
	
	VariableExp<double>* minus;
	
    Context<double> doubleContext;
    Context<string> stringContext;
    
	Expression<double>* ParseSummands(EVAL_CHAR*& expr) {
		Expression<double>* num1 = ParseFactors(expr);
		for(;;) {
			// Skip spaces
			while(*expr == ' ')
				expr++;
			EVAL_CHAR op = *expr;
			if(op != '-' && op != '+')
				return num1;
			expr++;
			Expression<double>* num2 = ParseFactors(expr);
			if(op == '-')
				num1 = new SubExpression<double>(num1, num2);
			else
				num1 = new SumExpression<double>(num1, num2);
		}
	}
	
	// Parse multiplication and division
	Expression<double>* ParseFactors(EVAL_CHAR*& expr) {
		Expression<double>* num1 = ParseAtom(expr);
		for(;;) {
			// Skip spaces
			while(*expr == ' ')
				expr++;
			// Save the operation and position
			EVAL_CHAR op = *expr;
			EVAL_CHAR* pos = expr;
			if(op != '/' && op != '*')
				return num1;
			expr++;
			Expression<double>* num2 = ParseAtom(expr);
			// Perform the saved operation
			if(op == '/') {
				// Handle division by zero
				if(num2 == 0) {
					throw string("EEE_DIVIDE_BY_ZERO");
					//_err = EEE_DIVIDE_BY_ZERO;
					//_err_pos = pos;
					return 0;
				}
				num1 = new DivExpression<double>(num1, num2);
			}
			else
				num1 = new MulExpression<double>(num1, num2);
		}
	}
	
	Expression<double>* ParseAtom(EVAL_CHAR*& expr) {
		// Skip spaces
		while(*expr == ' ')
			expr++;
			// Handle the sign before parenthesis (or before number)
		bool negative = false;
		if(*expr == '-') {
			negative = true;
			expr++;
		}
		if(*expr == '+') {
			expr++;
		}
			// Check if there is parenthesis
		if(*expr == '(') {
			expr++;
			_paren_count++;
			Expression<double>* res = ParseSummands(expr);
			if(*expr != ')') {
				// Unmatched opening parenthesis		
				throw string("EEE_PARENTHESIS");
				//_err = EEE_PARENTHESIS;
				_err_pos = expr;
				return 0;
			}
			expr++;
			_paren_count--;
			return negative ? new MulExpression<double>(res, minus) : (Expression<double>*)res;
		}
		
		// It should be a number; convert it to double
		char* end_ptr;
		double res = strtod(expr, &end_ptr);
		
		if(end_ptr != expr){
//    		cout << "res=" << res  << "|" << end_ptr << endl;
    		string varname = doubleContext.getNextVarName();
    		VariableExp<double>* var = new VariableExp<double>(varname);
    		doubleContext.createVar(varname);
    		doubleContext.assignVar(varname, res);
    		expr = end_ptr;
		    return negative ? new MulExpression<double>(var, minus) : (Expression<double>*)var;
        }
		else if(end_ptr == expr) {
            string s = string(expr);
            string varname = s.substr(0, s.find_first_of("+-*/) "));
            VariableExp<double>* var = new VariableExp<double>(varname);
		    doubleContext.createVar(varname);
            expr += varname.length();
		    return negative ? new MulExpression<double>(var, minus) : (Expression<double>*)var;
		}
		cout << "wrong" << endl;
		return new Expression<double>();
	}
	
	
    string trim(string& str)
    {
        size_t first = str.find_first_not_of(" \t\r\n;");
        size_t last = str.find_last_not_of(" \t\r\n;");
        return str.substr(first, (last-first+1));
    }


public:
	
	ExprEval(Context<double>& d, Context<string> s)
	{
        doubleContext = d;
        stringContext = s;
        
		string varname = "minus";
		minus = new VariableExp<double>(varname);
		doubleContext.createVar(varname);
		doubleContext.assignVar(varname, -1.0);
	}

	Expression<double>* evalDouble(string strexpr) 
	{
		_paren_count = 0;
		_err = EEE_NO_ERROR;
		
		strexpr = trim(strexpr);
		EVAL_CHAR* expr = (char*)strexpr.c_str();
		
		Expression<double>* e = ParseSummands(expr);
		cout << e->evaluate(doubleContext) << endl;
		
		// Now, expr should point to '\0', and _paren_count should be zero
		if(_paren_count != 0 || *expr == ')') {
			_err = EEE_PARENTHESIS;
			_err_pos = expr;
			throw string("EEE_PARENTHESIS");
		}
		/*if(*expr != '\0') {
			_err = EEE_WRONG_CHAR;
			_err_pos = expr;
			return 0;
		}*/
		return e;
	}
	
	Expression<string>* evalString(EVAL_CHAR* expr) 
	{
        string varname = stringContext.getNextVarName();
        Expression<string>* e = new VariableExp<string>(varname);
        stringContext.createVar(varname);
        stringContext.assignVar(varname, "");
        
        string strexpr = string(expr);
        int offset = 0;
        for(int i=0; i <= strexpr.length(); i++){
            if(strexpr[i] == '+' || i == strexpr.length()){
                //zmienna - tylko znaki a-zA-z0-9
                //stala - wszystko pomiedzy ""
                //funkcja - nazwa(,)
                
                string s = strexpr.substr(offset, i - offset);
                s = trim(s);
                if(s.length() == 0){throw string("string eval error");}
                offset = i + 1;
                
                if(s[0] == '"' && s[s.length()-1] == '"'){
                    s = s.substr(1, s.length()-2);
                    string varname = stringContext.getNextVarName();
                    VariableExp<string>* var = new VariableExp<string>(varname);
    		        stringContext.createVar(varname);
    		        stringContext.assignVar(varname, s);
    		        e = new SumExpression<string>(e, var);
                }
            }
        }
        
        cout << e->evaluate(stringContext) << endl;
        
    }
	
	EXPR_EVAL_ERR GetErr() {
		return _err;
	}
	
	EVAL_CHAR* GetErrPos() {
		return _err_pos;
	}
};

#endif

