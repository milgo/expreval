#ifndef __DIVEXPRESSION
#define __DIVEXPRESSION

#include "variableexpr.h"

template<typename T>
class DivExpression: public Expression<T>{
public:
       DivExpression(Expression<T>*, Expression<T>*);
       virtual ~DivExpression();
       
       virtual T evaluate(Context<T>&);
       virtual Expression<T>* replace(const char*, Expression<T>&);
       virtual Expression<T>* copy() const;
       
private:
        Expression<T>* _operand1;
        Expression<T>* _operand2;
        
};

#endif
