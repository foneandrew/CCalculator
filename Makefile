CC = gcc
FILES = main.c infix.c postfix.c
OUT_EXE = CCalculator

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)
