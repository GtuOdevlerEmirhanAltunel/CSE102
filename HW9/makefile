all: clear clean compile run clean

clear:
	@clear

compile: main.c
	@gcc -o ex.out main.c -lm

run:
	@./ex.out

clean:
	@rm -f *.o
	@rm -f *.out
	@rm -f *.save
