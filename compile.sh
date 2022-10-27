#!/usr/bin/env bash

dir="$PWD/build/"
if [ ! -d "$dir" ];then
    cmake -G Ninja -S $PWD -B $dir -DCMAKE_EXPORT_COMPILE_COMMANDS=1
fi

mold -run cmake --build $dir

./build/wee
#latexmk -pdf resume/resume.tex
#latexmk -c resume/resume.tex
