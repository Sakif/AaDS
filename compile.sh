#!/usr/bin/env bash

dir="$PWD/build/"

if [ ! -d "$dir" ];then
    cmake -G Ninja -S $PWD -B $dir -DCMAKE_EXPORT_COMPILE_COMMANDS=1
fi

mold -run cmake --build $dir

# ./build/bol
./build/leet_c

# latexmk -pdf resume/resume.tex
# gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.7 -dNOPAUSE -dQUIET -dBATCH -dPrinted=false -sOutputFile=SAKIF_FAHMID_ZAMAN.pdf resume.pdf
# latexmk -C resume/*.tex
