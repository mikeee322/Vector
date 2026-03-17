CXXFLAGS += -Wall -Wextra -std=c++14 -Weffc++ -MMD

-include main.d

top-vect: main.o
	g++ -o $@ $^

clean:
	rm -rf *.o top-vect

