all: clear compile run clean

clear:
	@clear

compile: main.c util.c
	@gcc -o ex.out main.c util.c -lm

run:
	@./ex.out

clean:
	@rm -f *.o
	@rm -f *.out
	@rm -f *.save