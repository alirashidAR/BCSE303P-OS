#!/bin/bash

# factorial(){
#     n=$1
#     var=1
#     for(( i=1;i<=n;i++ )); do
#         var=$(( var*i ))
#     done

#     echo "$var"
# }

fib(){
    n=$1
    a=0
    b=1

    for(( i=0;i<=n;i++ )); do
        echo "$fn"
        fn=$(( a+b ))
        a=$b
        b=$fn
    done

    echo
}



read -p "Enter a number :" number

fib $number