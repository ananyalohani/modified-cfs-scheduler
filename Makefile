compile1:
	gcc test1.c -lgomp -o test1

run1: compile1
	./test1

compile2:
	gcc test2.c -lgomp -o test2

run2: compile2
	./test2

runtest3:
	gcc mytest3.c -o mytest
	./mytest

runtest:
	gcc mytest.c -lgomp -o mytest
	./mytest