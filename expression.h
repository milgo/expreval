#ifndef __EXPRESSION
#define __EXPRESSION

#include "context.h"
#include "expression.h"

template <typename T>
class Context;

template <typename T>
class Expression{
public:
       Expression();
       
       virtual ~Expression();
       virtual T evaluate(Context<T>&) = 0;
       virtual Expression<T>* replace(const char*, Expression<T>&) = 0;
       virtual Expression<T>* copy() const = 0;
};

#endif
