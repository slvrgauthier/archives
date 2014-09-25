all: ensemble

ensemble : ensemble.c typesBase/typeBase.o
	gcc -o test_ensemble test_ensemble.c ensemble.c typesBase/typeBase.o

typeBase.o: typesBase/typeBase.c
	gcc -c typesBase/typeBase.c

clean:
	rm *.o *~ ensemble

