objects = main.o thread.o ThreadPool.o
test: $(objects)
	g++ -g -pthread -o test $(objects) /usr/local/lib/libgtest.a

main.o: ThreadPool.h  ../common.h
thread.o: thread.h ../common.h
ThreadPool.o: ThreadPool.h ../common.h
#ThreadPoolUnitTest.o: ThreadPoolUnitTest.h ../common.h

.PHONY:clean
clean:
	-rm test *.o