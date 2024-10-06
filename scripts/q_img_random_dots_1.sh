#!/bin/bash
../bin/qyoo -id $(shuf -i 0-68719476735 -n 1 | awk '{printf "%036d", $0}') -fg "#ffffff" -dot "#000000" -o ../output/q_img_random_dots_1.png

