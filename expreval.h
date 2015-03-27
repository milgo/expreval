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
	int _var_count;
	
	VariableExp<double>* minus;
	Expression<double>* expression;
	Context<double> context;

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
		
		ostringstream ss;
		ss << _var_count++;
		string varname = string(ss.str());
		VariableExp<double>* var = new VariableExp<double>(varname);
		context.createVar(varname);
		context.assignVar(varname, res);
		
		if(end_ptr == expr) {
			// Report error
			throw string("EEE_WRONG_CHAR");
			_err = EEE_WRONG_CHAR;
			_err_pos = expr;
			return 0;
		}
		// Advance the pointer and return the result
		expr = end_ptr;
		return negative ? new MulExpression<double>(var, minus) : (Expression<double>*)var;
	}

public:
	
	ExprEval()
	{
		string varname = "minus";
		minus = new VariableExp<double>(varname);
		context.createVar(varname);
		context.assignVar(varname, -1.0);
	}

	Expression<double>* Eval(EVAL_CHAR* expr) 
	{
		_paren_count = 0;
		_var_count = 0;
		_err = EEE_NO_ERROR;
		
		Expression<double>* e = ParseSummands(expr);
		cout << e->evaluate(context) << endl;
		
		// Now, expr should point to '\0', and _paren_count should be zero
		if(_paren_count != 0 || *expr == ')') {
			_err = EEE_PARENTHESIS;
			_err_pos = expr;
			throw string("EEE_PARENTHESIS");
		}
		/*if(*expr != '\0') {
			printf("tutaj");
			_err = EEE_WRONG_CHAR;
			_err_pos = expr;
			return 0;
		}*/
		return e;
	}
	
	EXPR_EVAL_ERR GetErr() {
		return _err;
	}
	
	EVAL_CHAR* GetErrPos() {
		return _err_pos;
	}
};

#endif

