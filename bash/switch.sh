#!/bin/sh
case "$2" in
    "+") ans=`expr $1 + $3`
         printf "%d %s %d = %d\n" $1 $2 $3 $ans
         ;;
    *)   echo "Unsupported operation"
         ;;
esac
