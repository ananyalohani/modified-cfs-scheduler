compile1:
	gcc test1.c -lgomp -o test1

run1: compile1
	./test1

compile2:
	gcc test2.c -lgomp -o test2

run2: compile2
	./test2

compile3:
	gcc test3.c -lgomp -o test3

run3: compile3
	./test3