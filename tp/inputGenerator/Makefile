all: 
	g++ -std=c++11 genK.cpp -o genk.exe

g:
	g++ -g -std=c++11 inputGen.cpp -o inputgen.exe

k:
	g++ -std=c++11 genK.cpp -o genk.exe

x:
	./genk.exe $(TARGET)

v:
	valgrind ./inputgen.exe 10
