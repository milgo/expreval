#include "mulexpression.h"

template class Context<int>;
template class VariableExp<int>;
template class Expression<int>;
template class MulExpression<int>;

template <typename T>
MulExpression<T>::MulExpression(Expression<T>* op1, Expression<T>* op2){
    _operand1 = op1;
    _operand2 = op2;
}

template <typename T>
MulExpression<T>::~MulExpression(){}

template <typename T>
T MulExpression<T>::evaluate(Context<T>& context){
    return _operand1->evaluate(context) * _operand2->evaluate(context);
}

template <typename T>
Expression<T>* MulExpression<T>::copy()const{
    return new MulExpression<T>(_operand1->copy(), _operand2->copy());
}

template <typename T>
Expression<T>* MulExpression<T>::replace(const char* name, Expression<T>& exp){
    return 
           new MulExpression<T>(
               _operand1->replace(name, exp), 
               _operand2->replace(name, exp)
               );
}
