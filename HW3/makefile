all: print compile run

clear:
	@clear

print:
	@echo "───────────────────────────────────────────"
	@echo "\033[0;32mEmirhan Altunel 200104004035\033[0m"

compile: main.c
	@echo "───────────────────────────────────────────"
	@echo "Compiling..."
	@gcc -o ex main.c -lm

run:
	@echo "───────────────────────────────────────────"
	@echo "Running the tests...."
	@echo "═══════════════════════════════════════════"
	@./ex
	@echo "═══════════════════════════════════════════"
	@echo "Completed tests...."

clean:
	@echo "───────────────────────────────────────────"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f ex
	@rm -f *.txt
	@rm -f *.out
	@rm -f *.save
