objs := main.o word.o

all : $(objs)
	gcc -g -o main $^

%.o : %.c
	gcc -c -o $@  $<

clean:
	rm -fr main *.o
