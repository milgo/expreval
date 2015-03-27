#ifndef __MULEXPRESSION
#define __MULEXPRESSION

#include "expressionoperation.h"

template<typename T>
class MulExpression: public ExprOperation<T>{
public:
       MulExpression(Expression<T>* op1, Expression<T>* op2):ExprOperation<T>(op1, op2){}
       virtual ~MulExpression(){}
       
       virtual T evaluate(Context<T>& context){
		return this->_operand1->evaluate(context) * this->_operand2->evaluate(context);
	   }
};

#endif
