#include "expreval.h"

double ExprEval::ParseAtom(EVAL_CHAR*& expr) {
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
		double res = ParseSummands(expr);
		if(*expr != ')') {
			// Unmatched opening parenthesis
			_err = EEE_PARENTHESIS;
			_err_pos = expr;
			return 0;
		}
		expr++;
		_paren_count--;
		return negative ? -res : res;
	}
		// It should be a number; convert it to double
	char* end_ptr;
	double res = strtod(expr, &end_ptr);
	if(end_ptr == expr) {
		// Report error
		_err = EEE_WRONG_CHAR;
		_err_pos = expr;
		return 0;
	}
	// Advance the pointer and return the result
	expr = end_ptr;
	return negative ? -res : res;
}
	// Parse multiplication and division
double ExprEval::ParseFactors(EVAL_CHAR*& expr) {
	double num1 = ParseAtom(expr);
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
		double num2 = ParseAtom(expr);
		// Perform the saved operation
		if(op == '/') {
			// Handle division by zero
			if(num2 == 0) {
				_err = EEE_DIVIDE_BY_ZERO;
				_err_pos = pos;
				return 0;
			}
			num1 /= num2;
		}
		else
			num1 *= num2;
	}
}
	// Parse addition and subtraction
double ExprEval::ParseSummands(EVAL_CHAR*& expr) {
	double num1 = ParseFactors(expr);
	for(;;) {
		// Skip spaces
		while(*expr == ' ')
			expr++;
		EVAL_CHAR op = *expr;
		if(op != '-' && op != '+')
			return num1;
		expr++;
		double num2 = ParseFactors(expr);
		if(op == '-')
			num1 -= num2;
		else
			num1 += num2;
	}
}

double ExprEval::Eval(EVAL_CHAR* expr) {
	_paren_count = 0;
	_err = EEE_NO_ERROR;
	double res = ParseSummands(expr);
	// Now, expr should point to '\0', and _paren_count should be zero
	if(_paren_count != 0 || *expr == ')') {
		_err = EEE_PARENTHESIS;
		_err_pos = expr;
		return 0;
	}
	/*if(*expr != '\0') {
		printf("tutaj");
		_err = EEE_WRONG_CHAR;
		_err_pos = expr;
		return 0;
	}*/
	return res;
}
