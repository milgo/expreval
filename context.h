#ifndef __CONTEXT
#define __CONTEXT

#define MAX_VARIABLES 50

#include <map>
#include "variableexpr.h"

using namespace std;

template <typename T>
class VariableExp;

template <typename T>
class Context{
public:
       Context();
       ~Context();
       T lookup(const char* c)const;
       void assign(VariableExp<T>* v, T x);
private:
       const char* name[MAX_VARIABLES];
       T value[MAX_VARIABLES];
       int n;
};


#endif
