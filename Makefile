objs := main.o word.o

all : $(objs)
	gcc -o main $^

%.o : %.c
	gcc -g -c -o $@  $<

clean:
	rm -fr main *.o
