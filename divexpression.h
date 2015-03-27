#ifndef __DIVEXPRESSION
#define __DIVEXPRESSION

#include "expressionoperation.h"

template<typename T>
class DivExpression: public ExprOperation<T>{
public:
		DivExpression(Expression<T>* op1, Expression<T>* op2):ExprOperation<T>(op1, op2){}
       
       	virtual T evaluate(Context<T>& context){
			return this->_operand1->evaluate(context) / this->_operand2->evaluate(context);
	   	}
        
};

#endif
