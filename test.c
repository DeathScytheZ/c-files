#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
int Max(int n, ...){
    if(n == 0){
        return INT_MIN; 
    }
    int max;
    va_list args;
    va_start(args, n);
    for(int i = 0; i < n; i++){
        if(i == 0){
            max = va_arg(args, int);
        }else{
            int num = va_arg(args ,int);
            if(num > max){
               max = num;
            }
        }
    }
    va_end(args);
    return max;
}

int greatest(int argc, char* argv[]){
    if(!argc){ 
        return INT_MIN;
    }
    int max = atoi(argv[1]); 
    for(int i = 2; i < argc; i++){
        int num = atoi(argv[i]);
        max = (num > max) ? num : max;
    }
    return max;
}

int sum(int n, ...){
    if(!n){
        return INT_MIN;
    }
    int result = 0;
    va_list ptr;
    va_start(ptr, n);
    for(int i = 0; i < n; i++){
        result += va_arg(ptr, int); 
    }
    va_end(ptr);
    return result;
}


int largest(int n, ...){
    if(!n){
        return INT_MIN;
    }
    va_list ptr;
    va_start(ptr, n);
    int max = va_arg(ptr, int);
    for(int i = 0; i < n; i++){
        int num = va_arg(ptr, int);
        max = (num > max) ? num : max;
    }
    va_end(ptr);
    return max;
}

void print(int n, ...){
    va_list args;
    va_start(args, n);
    for(int i = 0; i < n; i++){
        printf("%s ", va_arg(args, char*));
    }
    va_end(args);
}


int main(int argc, char* argv[]){
    print(3, "hi,", "how's it going?", "hope you're doing well (:");
}
