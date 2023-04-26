build:
	mkdir -p "bin"
	gcc -o ./bin/worker worker.c -lm
	gcc -o ./bin/stress-sqrt stress-sqrt.c