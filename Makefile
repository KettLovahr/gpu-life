build:
	gcc -o gpu_life main.c -lraylib

run: build
	./gpu_life
