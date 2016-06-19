all: 
	g++ -std=c++11 brvk.cpp graph.cpp Component.cpp -o brvk.exe

parallel:
	clang-omp++ -fopenmp -std=c++11 brvk_parallel.cpp graph.cpp Component.cpp -o prl.exe

clean:
	rm *.exe

g:
	g++ -g -std=c++11 brvk.cpp graph.cpp Component.cpp -o brvk.exe

gpar:
	clang-omp++ -g -fopenmp -std=c++11 brvk_parallel.cpp graph.cpp Component.cpp -o prl.exe	

vpar:
	valgrind --leak-check=full ./prl.exe < ../inputGenerator/$(TARGET)

v:
	valgrind --leak-check=full ./brvk.exe < ../inputGenerator/$(TARGET)

x:
	./brvk.exe < 1_test.txt

runpar:
	time ./prl.exe < ../inputGenerator/$(TARGET)

runser:
	time ./brvk.exe < ../inputGenerator/$(TARGET)

runkruskal:
	time ../kruskal/a.out < ../inputGenerator/$(TARGET)

runprim:
	time ../prim/a.out < ../inputGenerator/$(TARGET)