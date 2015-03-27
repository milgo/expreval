#include "divexpression.h"

template class Context<int>;
template class VariableExp<int>;
template class Expression<int>;
template class DivExpression<int>;

template <typename T>
DivExpression<T>::DivExpression(Expression<T>* op1, Expression<T>* op2){
    _operand1 = op1;
    _operand2 = op2;
}

template <typename T>
DivExpression<T>::~DivExpression(){}

template <typename T>
T DivExpression<T>::evaluate(Context<T>& context){
    return _operand1->evaluate(context) / _operand2->evaluate(context);
}

template <typename T>
Expression<T>* DivExpression<T>::copy()const{
    return new DivExpression<T>(_operand1->copy(), _operand2->copy());
}

template <typename T>
Expression<T>* DivExpression<T>::replace(const char* name, Expression<T>& exp){
    return 
           new DivExpression<T>(
               _operand1->replace(name, exp), 
               _operand2->replace(name, exp)
               );
}
