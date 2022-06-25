all: clear clean compile run

clear:
	@clear

compile: main.c
	@gcc -o ex.out main.c util.c -lm -ansi

run:
	@./ex.out

clean:
	@rm -f *.o
	@rm -f *.out
	@rm -f *.save
