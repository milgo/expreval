#include <cstring>
#include "variableexpr.h"

template <typename T> 
VariableExp<T>::VariableExp(const char* name){
    _name = strdup(name);
}

template <typename T> 
T VariableExp<T>::evaluate(Context<T>& context){
    return context.lookup(_name);
}

template <typename T> 
Expression<T>* VariableExp<T>::copy() const{
    return new VariableExp(_name);
}

template <typename T> 
Expression<T>* VariableExp<T>::replace(const char* name, Expression<T>& exp){
    if(strcmp(name, _name) == 0){
        return exp.Copy();
    }else{
        return new VariableExp(_name);
    }
}