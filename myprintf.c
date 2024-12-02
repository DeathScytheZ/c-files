#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int myprintf(const char* str, ...){
    va_list args;
    va_start(args, str);
    for(int i = 0; str[i] != '\0'; i++){ 
        if(str[i] == '%' && str[i + 1] != '\0'){
            i++;
            switch(str[i]){
                case 's':
                    fprintf(stdout, "%s", va_arg(args, char*)); break;
                case 'd':
                    fprintf(stdout, "%d", va_arg(args, int)); break;
                case 'c':
                    fprintf(stdout, "%c", va_arg(args, int)); break;
                case 'f':
                    fprintf(stdout, "%f", va_arg(args, double)); break;
                case 'p':
                    fprintf(stdout, "%p", va_arg(args, void*)); break;
                default:
                    fprintf(stdout, "%%%c", str[i]); 
            }
        }else{
            fprintf(stdout, "%c", str[i]);
        }
    }    
    va_end(args);
    return 0;
}

int main(){
    myprintf("%s%d\n", "gis", 5);
}
