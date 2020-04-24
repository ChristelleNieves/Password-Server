all: proj5.x

proj5.x: proj5.o passserver.o
	g++ -o proj5.x proj5.o passserver.o -lcrypt

proj5.o: proj5.cpp
	g++ -c -std=c++11 proj5.cpp -lcrypt

passserver.o: passserver.h passserver.cpp hashtable.h hashtable.hpp
	g++ -c -std=c++11 -lcrypt passserver.cpp

clean: -rm *.o
