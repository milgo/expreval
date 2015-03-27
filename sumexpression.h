#ifndef __SUMEXPRESSION
#define __SUMEXPRESSION

#include "expression.h"
#include "variableexpr.h"
#include "expressionoperation.h"

template<typename T>
class SumExpression: public ExprOperation<T>{
public:
	
		SumExpression(Expression<T>* op1, Expression<T>* op2):ExprOperation<T>(op1, op2){}
       	virtual ~SumExpression();
       
       	virtual T evaluate(Context<T>& context){
			return this->_operand1->evaluate(context) - this->_operand2->evaluate(context);
	   	}
};

#endif
