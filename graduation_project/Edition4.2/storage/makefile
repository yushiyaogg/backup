OBJ :=main.o Buffermanager.o Epoll.o S_Manager_Agent.o S_Agent.o ReadAgent.o WriteAgent.o

storage:$(OBJ)
	g++ $(OBJ) -o storage -g

main.o : main.cpp
	g++ -c -g main.cpp
Buffermanager.o:Buffermanager.cpp
	g++ -c -g Buffermanager.cpp
Epoll.o:Epoll.cpp
	g++ -c -g Epoll.cpp
WriteAgent.o:WriteAgent.cpp
	g++ -c -g WriteAgent.cpp 
S_Manager_Agent.o:S_Manager_Agent.cpp
	g++ -c -g S_Manager_Agent.cpp
S_Agent.o:S_Agent.cpp
	g++ -c -g S_Agent.cpp
ReadAgent.o:ReadAgent.cpp
	g++ -c -g ReadAgent.cpp
clean:
	rm *.o

