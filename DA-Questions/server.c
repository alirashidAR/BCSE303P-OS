#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char *argv[]){
    if(argc!=4){
        fprintf(stderr,"Usage: server <int1> <int2> <operator>\n");
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int op = argv[3][0];
    int result;

    if(op == '+'){
        result = num1+num2;
    }else if( op == '-'){
        result = num1-num2;
    }else{
        fprintf(stderr,"Invalid operator.");
        return 1;
    }

    exit(result);
}