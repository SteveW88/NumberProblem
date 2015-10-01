CPP=g++
FLAGS=-g -std=c++11

OUT_EXEC = main
objects  = numbers.o main.o

numbers_hpp = numbers.hpp

$(OUT_EXEC) : $(objects)
	$(CPP) -c main.cpp $(FLAGS)
	$(CPP) $^ -o $@ $(FLAGS)

numbers.o : numbers.cpp $(numbers_hpp)
	$(CPP) -c $< $(FLAGS)

main.o : main.cpp $(numbers_hpp)
	$(CPP) -c $< $(FLAGS)


clean : 
	rm -f $(objects)
	rm -f $(OUT_EXEC)
