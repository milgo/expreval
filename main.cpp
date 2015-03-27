// (c) Peter Kankowski, 2007. http://smallcode.weblogs.us mailto:kankowski@narod.ru
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "expreval.h"
#include "context.h"
#include "expression.h"

int main() {
    
	static const char *errors[] = {
		"no error",
		"parentheses don't match",
		"invalid character",
		"division by zero"};

	puts("Enter an expression (or an empty string to exit):");
	for(;;) {
		// Get a string from console
		static char buff[256];
		char *expr = fgets(buff, sizeof(buff), stdin);
		printf(buff);
		// If the string is empty, then exit
		if(*expr == '\0')
			return 0;

		// Evaluate the expression
		ExprEval eval;
		double res = eval.Eval(expr);
		if(eval.GetErr() != EEE_NO_ERROR) {
			printf("  Error: %s at %s\n", errors[eval.GetErr()], eval.GetErrPos());
		} else {
			printf("  = %g\n", res);
		}
	}
}
