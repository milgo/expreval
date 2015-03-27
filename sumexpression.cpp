#include "sumexpression.h"

template class Context<int>;
template class VariableExp<int>;
template class Expression<int>;
template class SumExpression<int>;

template <typename T>
SumExpression<T>::SumExpression(Expression<T>* op1, Expression<T>* op2){
    _operand1 = op1;
    _operand2 = op2;
}

template <typename T>
SumExpression<T>::~SumExpression(){}

template <typename T>
T SumExpression<T>::evaluate(Context<T>& context){
    return _operand1->evaluate(context); /*+ _operand2->evaluate(context);*/
}

template <typename T>
Expression<T>* SumExpression<T>::copy()const{
    return new SumExpression<T>(_operand1->copy(), _operand2->copy());
}

template <typename T>
Expression<T>* SumExpression<T>::replace(const char* name, Expression<T>& exp){
    return 
           new SumExpression<T>(
               _operand1->replace(name, exp), 
               _operand2->replace(name, exp)
               );
}
