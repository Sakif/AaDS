compile: build
	cmake --build $^

build:
	mkdir -p $@
	cmake -G Ninja -S . -B $@

run: compile
	./build/bol_sfml/bol

cv:
	latexmk -pdf resume/tasneem_cv.tex
	gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.7 -dNOPAUSE -dQUIET -dBATCH -dPrinted=false -sOutputFile=Tasneem_Zahur.pdf tasneem_cv.pdf
	latexmk -C resume/*.tex
