#!/bin/bash
for i in {1..10}; do
    RAND_ID=$((RANDOM + 1000))
    FG_COLOR=$(printf "#%06x" $((RANDOM % 16777216)))
    DOT_COLOR=$(printf "#%06x" $((RANDOM % 16777216)))
    ../bin/qyoo -id $RAND_ID -fg $FG_COLOR -dot $DOT_COLOR -o ../output/q_img_colors_$i.png
done
