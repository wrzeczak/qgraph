build:
	gcc -o graph main.c -Wall -Wextra -lraylib -lm

run: build
	./graph

install: build
	./setup.sh

clean:
	rm -rf ./imgs
	rm graph
