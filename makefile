compile: build
	cmake --build $^

build:
	mkdir -p $@
	cmake -G Ninja -S . -B $@

run: compile
	./build/bol_sfml/bol

cv:
	latexmk -pdf resume/seven_min_safety.tex
	gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.7 -dNOPAUSE -dQUIET -dBATCH -dPrinted=false -sOutputFile=presentation.pdf seven_min_safety.pdf
	latexmk -C resume/*.tex
