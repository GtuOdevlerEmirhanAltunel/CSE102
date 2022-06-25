all: clear clean compile run clean

clear:
	@clear

compile: 200104004035.c
	@gcc -o ex.out 200104004035.c -lm

run:
	@./ex.out

clean:
	@rm -f *.o
	@rm -f *.txt
	@rm -f *.out
	@rm -f *.save
