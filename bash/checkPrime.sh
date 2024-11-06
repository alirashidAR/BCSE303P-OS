#!/bin/bash

is_prime(){
    local num=$1
    if [ $num -le 1 ]; then
        echo "false"
        return
    fi

    for((i=2; i*i<=num; i++)); do
        if (( num%i == 0 )); then
            echo "false"
            return
        fi
    done
    echo "true"
}

read -p "Enter a number: " number

if [[ $number =~ ^[0-9]+$ ]]; then
    if [[ $(is_prime $number) == "true" ]]; then
        echo "$number is a prime number."
    else
        echo "$number is not a prime number."
    fi
else    
    echo "Please enter a valid positive integer."
fi