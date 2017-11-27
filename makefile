# name: Chaviva Moshavi
# ID: 322082892

a.out: compileAll
	g++ *.o 
	rm -f *.o

compileAll: include/*.h src/*.cpp
	g++ -Iinclude/ -c src/*.cpp
