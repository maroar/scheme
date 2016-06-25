all: 
	g++ -std=c++11 brvk.cpp graph.cpp Component.cpp -o brvk.exe

p: 
	g++ -std=c++11 -pthread brvk_parallel.cpp graph.cpp Component.cpp -o brvkp.exe

gp:
	g++ -g -std=c++11 -pthread brvk_parallel.cpp graph.cpp Component.cpp -o brvkp.exe

rp: 
	time ./brvkp.exe < ../inputGenerator/$(TARGET)

vp: 
	valgrind --leak-check=full ./brvkp.exe < ../inputGenerator/$(TARGET)	

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
	time ./brvk.exe < ../inputGenerator/$(TARGET)

runpar:
	time ./prl.exe < ../inputGenerator/$(TARGET)

runser:
	time ./brvk.exe < ../inputGenerator/$(TARGET)

runkruskal:
	time ../kruskal/a.out < ../inputGenerator/$(TARGET)

runprim:
	time ../prim/a.out < ../inputGenerator/$(TARGET)