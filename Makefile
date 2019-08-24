objects = main.o thread.o ThreadPool.o ThreadPoolUnitTest.o
test: $(objects)
	g++  -g -pthread -o test $(objects) /usr/local/lib/libgtest.a

main.o:  ThreadPoolUnitTest.h ../common.h
thread.o: thread.h ../common.h
ThreadPool.o: ThreadPool.h ../common.h
ThreadPoolUnitTest.o: ThreadPoolUnitTest.h msgqueue.h ../common.h

.PHONY:clean
clean:
	-rm test *.o $(objects)