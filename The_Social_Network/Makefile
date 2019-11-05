all: social_network

social_network: FORCE network.o user.o
	g++ -g -Wall -std=c++11 network.o user.o social_network.cpp -o social_network

network.o: network.h network.cpp
	g++ -g -Wall -std=c++11 -c network.cpp -o network.o

user.o: user.h user.cpp
	g++ -g -Wall -std=c++11 -c user.cpp -o user.o

FORCE: ;

.phony: clean social_network

clean:
	-@rm -rf *.o	