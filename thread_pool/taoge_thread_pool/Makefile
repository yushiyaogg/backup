OBJ := Thread.o testT.o  Scheduler.o MidServer.o  CBuffer.o \
	MemAgent.o Epoll.o ListenAgent.o aio.o FileMap.o RequestMap.o
testT:$(OBJ)
	$(CXX) -g -pg -o testT $(OBJ) -lpthread
Thread.o:header.h Thread.h aio.h
	$(CXX) -g -pg -c Thread.cpp -lpthread
testT.o:header.h Thread.h Scheduler.h Queue.h
	$(CXX) -g -pg -c testT.cpp -lpthread
Scheduler.o:Scheduler.h Thread.h header.h MidServer.h
	$(CXX) -g -pg -c Scheduler.cpp -lpthread
MidServer.o:MidServer.h  Queue.h Thread.h header.h MemAgent.h
	$(CXX) -g -pg -c MidServer.cpp
CBuffer.o:CBuffer.h header.h
	$(CXX) -g -pg -c CBuffer.cpp
MemAgent.o:MemAgent.h Agent.h header.h Queue.h
	$(CXX) -g -pg -c MemAgent.cpp
Epoll.o:Epoll.h header.h Agent.h Queue.h
	$(CXX) -g -pg -c Epoll.cpp
ListenAgent.o:MemAgent.h ListenAgent.h header.h Epoll.h
	$(CXX) -g -pg -c ListenAgent.cpp
aio.o:aio.h header.h
	$(CXX) -g -pg -c aio.cpp
FileMap.o:FileMap.h header.h
	$(CXX) -g -pg -c FileMap.cpp
RequestMap.o:RequestMap.h Agent.h
	$(CXX) -g -pg -c RequestMap.cpp
.last:
	clean
clean:
	-rm *.o
