all:
	gcc main.c word.c -o main -g

clean:
	rm -fr main *.o
