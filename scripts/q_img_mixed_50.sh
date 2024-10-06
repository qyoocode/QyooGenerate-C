#!/bin/bash
for i in {1..50}; do
    RAND_ID=$((RANDOM + 1000))
    FG_COLOR=$(printf "#%06x" $((RANDOM % 16777216)))
    DOT_COLOR=$(printf "#%06x" $((RANDOM % 16777216)))
    BG_COLOR=$(printf "#%06x" $((RANDOM % 16777216)))
    TRANSPARENT_BG=$(($RANDOM % 2))
    if [ $TRANSPARENT_BG -eq 1 ]; then
        ../bin/qyoo -id $RAND_ID -fg $FG_COLOR -dot $DOT_COLOR -bg transparent -o ../output/q_img_mixed_$i.png
    else
        ../bin/qyoo -id $RAND_ID -fg $FG_COLOR -dot $DOT_COLOR -bg $BG_COLOR -o ../output/q_img_mixed_$i.png
    fi
done
