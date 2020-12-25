all:
	gcc main.c -o main -g

clean:
	rm -fr main *.o
