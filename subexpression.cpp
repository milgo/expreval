#include "subexpression.h"

template class Context<double>;
template class VariableExp<double>;
template class Expression<double>;
template class SubExpression<double>;

template <typename T>
SubExpression<T>::SubExpression(Expression<T>* op1, Expression<T>* op2){
    _operand1 = op1;
    _operand2 = op2;
}

template <typename T>
SubExpression<T>::~SubExpression(){}

template <typename T>
T SubExpression<T>::evaluate(Context<T>& context){
    return _operand1->evaluate(context) + _operand2->evaluate(context);
}

template <typename T>
Expression<T>* SubExpression<T>::copy()const{
    return new SubExpression<T>(_operand1->copy(), _operand2->copy());
}

template <typename T>
Expression<T>* SubExpression<T>::replace(const char* name, Expression<T>& exp){
    return 
           new SubExpression<T>(
               _operand1->replace(name, exp), 
               _operand2->replace(name, exp)
               );
}
