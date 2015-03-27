#ifndef __SUMEXPRESSION
#define __SUMEXPRESSION

#include "variableexpr.h"

template<typename T>
class SumExpression: public Expression<T>{
public:
       SumExpression(VariableExp<T>*, VariableExp<T>*);
       virtual ~SumExpression();
       
       virtual T evaluate(Context<T>&);
       virtual Expression<T>* replace(const char*, Expression<T>&);
       virtual Expression<T>* copy() const;
private:
        Expression<T>* _operand1;
        Expression<T>* _operand2;
};

#endif