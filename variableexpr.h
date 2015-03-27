#ifndef __VARIABLEEXPR
#define __VARIABLEEXPR

#include "context.h"
#include "expression.h"

template <typename T>
class Context;

template <typename T>
class VariableExp: public Expression<T>{
public:
       VariableExp(const char*);
       virtual ~VariableExp();
       
       virtual T evaluate(Context<T>&);
       virtual Expression<T>* replace(const char*, Expression<T>&);
       virtual Expression<T>* copy() const;
private:
        char *_name;
};

#endif
