#include "context.h"

template class Context<int>;

template <typename T> 
Context<T>::Context(){
    n = 0;
}

template <typename T> 
Context<T>::~Context(){
    delete [] name;
    delete [] value;                       
}


template <typename T>
T Context<T>::lookup(const char* c)const{
    int i;
    for(i=0; i<MAX_VARIABLES, name[i] != c; i++);
    return value[i];
}

template <typename T>
void Context<T>::assign(VariableExp<T>* v, T x){
    if(n > MAX_VARIABLES - 1)return;
    name[n] = v->getName();
    value[n] = x;
    n++;
}
