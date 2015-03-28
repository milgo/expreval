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

	try
	{
        Context<double> context;
		puts("Enter an expression (or an empty string to exit):");
		for(;;) {

			static char buff[256];
			char *expr = fgets(buff, sizeof(buff), stdin);

			if(*expr == '\0')
				return 0;

			// Evaluate the expression
			ExprEval eval(context);
			Expression<double>* expression = eval.Eval(expr);
			
		}
	}	
	catch(string e)
	{
		cout << "Exception: " << e << endl;
	}
	
/*	Expression<int>* expression;
	Context<int> context;
	
	try
	{
		VariableExp<int>* x = new VariableExp<int>("x");
		VariableExp<int>* y = new VariableExp<int>("y");
		
		expression = new SumExpression<int>((Expression<int>*)x, 
	               (Expression<int>*)y);
		
		context.createVar(x);
		context.assignVar(x, 2);
		
		context.createVar(y);
		context.assignVar(y, 4);
		
		int res = expression->evaluate(context);
		
		cout << res << endl;
	}
	catch(string e)
	{
		cout << "Exception: " << e << endl;
	}*/
	
    system("PAUSE");
}
