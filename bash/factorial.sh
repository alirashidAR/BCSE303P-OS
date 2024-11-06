#!/bin/bash

# factorial(){
#     if [ $1 -le 1 ]; then
#         echo 1
#     else
#         echo $(( $1 * $(factorial $(( $1-1 )) ) ))
    
#     fi
# }

factorial(){
    n=$1
    var=1
    for (( i=1; i<=n; i++)); do
        var=$(( var*i ))
    done
    echo "$var"
}

read -p "Enter a positive number: " number

if [[ $number =~ ^[0-9]+$ ]]; then
    result=$(factorial $number)
    echo "Factorial of $number is $result"
else
    echo "Please enter a valid positive integer"
fi
