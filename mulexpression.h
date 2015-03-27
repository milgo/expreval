#ifndef __MULEXPRESSION
#define __MULEXPRESSION

#include "variableexpr.h"

template<typename T>
class MulExpression: public Expression<T>{
public:
       MulExpression(Expression<T>*, Expression<T>*);
       virtual ~MulExpression();
       
       virtual T evaluate(Context<T>&);
       virtual Expression<T>* replace(const char*, Expression<T>&);
       virtual Expression<T>* copy() const;
       
private:
        Expression<T>* _operand1;
        Expression<T>* _operand2;
        
};

#endif
