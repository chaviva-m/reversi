target: compileAll
	g++ -o reversi.out *.o 
	rm -f *.o

compileAll: include/*.h src/*.cpp
	g++ -Iinclude/ -c src/*.cpp

run:
	./reversi.out
