all:
	g++ -ggdb -O -o program heap.cpp graph.cpp main.cpp  -std=c++11
clean: 
	$(RM) program 
