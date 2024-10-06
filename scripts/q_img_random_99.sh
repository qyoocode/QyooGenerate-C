#!/bin/bash
for i in {1..99}; do
    RAND_ID=$(shuf -i 0-68719476735 -n 1)
    ../bin/qyoo -id $RAND_ID -fg "#ffffff" -dot "#000000" -bg transparent
done