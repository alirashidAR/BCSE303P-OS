#!/bin/bash

# echo "Hello World";
# echo "Second Hello World";

# variable="Some String"
# # echo "$variable"

# # echo "${variable/Some/A}"
# # length=7
# # echo "${variable:0:length}"
# echo "${variable: -1}" # make sure to give space afte colon or it will recognise :- as a character 

# echo "${#variable}" #Length of the string

# array=(one two three four five six)

# echo "${array[0]}"


# for item in "${array[@]}"; 
# do
#     echo "$item"
# done


# echo {1..10}
# echo {a..z}


# echo "What is your name?"
# read name

# echo "Hello, $name!"

# echo "What is your age?"
# read age

# if [[ "$name" == "Steve" ]] || [[ "$name" == "Ali" ]]; then
#     echo "This will run if $name is Steve or Ali"
# fi



# echo $(( 5 + 10 ))
# ls -l | LS "\.c"

# contens = $(cat readerWriter.c)

# (echo "First, I'm here: $PWD") && (cd ..; echo "Then, I'm here: $PWD")




case "$1" in
    0) echo "There is a zero.";;
    1) echo "There is a one.";;
    *) echo "It is not null.";;
esac

for Variable in {1..10}
do 
    echo "$Variable"
done


for ((a=1; a<=3; a++))
do 
    echo $a
done


for output in $(ls)
do
    echo "$output"
done

function foo() {
    echo "Arguments work just like script arguments: $@"
    echo "And: $1 $2..."
    echo "This is a function"
    returnValue=0    # Variable values can be returned
    return $returnValue
}

# Call the function `foo` with two arguments, arg1 and arg2:
foo arg1 arg2
# => Arguments work just like script arguments: arg1 arg2
# => And: arg1 arg2...
# => This is a function

# Get the return value from the function using $?
resultValue=$?
echo "The return value is: $resultValue"
