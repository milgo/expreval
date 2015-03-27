#ifndef __EXPRESSIONOPERATION
#define __EXPRESSIONOPERATION

#include "expression.h"
#include "variableexpr.h"


template<typename T>
class ExprOperation: public Expression<T>{
public:

		ExprOperation(Expression<T>* op1, Expression<T>* op2){
		    _operand1 = op1;
		    _operand2 = op2;
		}
		
		virtual ~ExprOperation(){}
		virtual T evaluate(Context<T>&){}

		virtual Expression<T>* copy()const{
		    return new ExprOperation<T>(_operand1->copy(), _operand2->copy());
		}

		virtual Expression<T>* replace(const char* name, Expression<T>& exp){
    		return 
	           new ExprOperation<T>(
	               _operand1->replace(name, exp), 
	               _operand2->replace(name, exp)
	               );
	    }
       
protected:
        Expression<T>* _operand1;
        Expression<T>* _operand2;
        
};

#endif
