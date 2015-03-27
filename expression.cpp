#include "expression.h"

template class Expression<int>;

template <typename T> 
Expression<T>::Expression(){}

template <typename T> 
Expression<T>::~Expression(){}

template <typename T> 
T Expression<T>::evaluate(Context<T>& context){}

template <typename T> 
Expression<T>* Expression<T>::replace(const char* c, Expression<T>& e){}

template <typename T> 
Expression<T>* Expression<T>::copy() const{}
