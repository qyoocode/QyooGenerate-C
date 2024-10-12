#!/bin/bash

# Function to generate a random color
generate_random_color() {
    RED=$(printf "%02x" $((RANDOM % 256)))
    GREEN=$(printf "%02x" $((RANDOM % 256)))
    BLUE=$(printf "%02x" $((RANDOM % 256)))
    echo "#$RED$GREEN$BLUE"
}

for i in {1..10}; do
    RAND_ID=$(shuf -i 0-68719476735 -n 1)
    FG_COLOR=$(generate_random_color)    # Random foreground color
    DOT_COLOR=$(generate_random_color)   # Random dot color
    ../bin/qyoo -id $RAND_ID -fg $FG_COLOR -dot $DOT_COLOR
done
