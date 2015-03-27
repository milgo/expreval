#ifndef __CONTEXT
#define __CONTEXT

#include "variableexpr.h"

template <typename T>
class VariableExp;

template <typename T>
class Context{
public:
       T lookup(const char* c)const;
       void assig(VariableExp<T>* v, T x);
};

#endif
