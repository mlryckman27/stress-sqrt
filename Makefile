build:
	mkdir -p "bin"
	gcc -o ./bin/stress-sqrt stress-sqrt.c -lm
