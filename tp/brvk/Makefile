all: 
	g++ -std=c++11 brvk.cpp graph.cpp Component.cpp -o brvk.exe

clean:
	rm *.o brvk.exe

g:
	g++ -g -std=c++11 brvk.cpp graph.cpp Component.cpp -o brvk.exe

v:
	valgrind --leak-check=full ./brvk.exe < 1_test.txt

x:
	./brvk.exe < 1_test.txt