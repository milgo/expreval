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
    for(i=0; i<MAX_VARIABLES; i++){
        printf("%s\n", name[i]);
        if(name[i] == NULL){
            printf("Variable not declared %s", c);
            break;
        }
        if(strcmp(name[i], c) == 0)break;
    }
    
    if(i == MAX_VARIABLES-1){
         printf("Variable not declared %s", c);
         return 0;
    }
    return value[i];
}

template <typename T>
void Context<T>::assignVar(VariableExp<T>* v, T x){
    if(n > MAX_VARIABLES - 1)return;
    int len = strlen(v->getName());
    name[n] = new char[len];
    strncpy(name[n], (const char*)v->getName(), len);
    name[n][len] = 0;
    value[n] = x;
    assigned[n] = true;
    n++;
}

template <typename T>
void Context<T>::assignVar(char* varname){
    if(n > MAX_VARIABLES - 1)return;
    int len = strlen(varname);
    name[n] = new char[len];
    strncpy(name[n], varname, len);
    name[n][len] = 0;
    printf("%s", name[n]);
    assigned[n] = false;
    n++;
}
