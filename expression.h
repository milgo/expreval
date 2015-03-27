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
       virtual T evaluate(Context<T>&);
       virtual Expression<T>* replace(const char*, Expression<T>&);
       virtual Expression<T>* copy() const;
};

#endif
