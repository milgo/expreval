#ifndef __SUBEXPRESSION
#define __SUBEXPRESSION

#include "expression.h"
#include "variableexpr.h"
#include "expressionoperation.h"

template<typename T>
class SubExpression: public ExprOperation<T>{
public:
	
       SubExpression(Expression<T>* op1, Expression<T>* op2):ExprOperation<T>(op1, op2){}
       virtual ~SubExpression();
       
       virtual T evaluate(Context<T>& context){
		return this->_operand1->evaluate(context) - this->_operand2->evaluate(context);
	   }

};

#endif
