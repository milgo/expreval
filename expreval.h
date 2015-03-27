#ifndef __EXPREVAL
#define __EXPREVAL

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "context.h"
#include "expression.h"
#include "variableexpr.h"
#include "sumexpression.h"
#include "mulexpression.h"

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
	
	Expression<int>* expression;
	Context<int> context;

	// Parse a number or an expression in parenthesis
	double ParseAtom(EVAL_CHAR*& expr);

	// Parse multiplication and division
	double ParseFactors(EVAL_CHAR*& expr);

	// Parse addition and subtraction
	double ParseSummands(EVAL_CHAR*& expr);

public:
	double Eval(EVAL_CHAR* expr);
	EXPR_EVAL_ERR GetErr() {
		return _err;
	}
	EVAL_CHAR* GetErrPos() {
		return _err_pos;
	}
};

#endif

