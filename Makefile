GCC = g++
FLAGS = -Wall --pedantic -g
EXECUTABLE = manejadordeversiones

manejadordeversiones: ManejadorDeVersiones.o main.o
	$(GCC) ManejadorDeVersiones.o main.o -o $(EXECUTABLE)

ManejadorDeVersiones.o: ManejadorDeVersiones.cpp ManejadorDeVersiones.h constantes.h
	$(GCC) $(FLAGS) -c ManejadorDeVersiones.cpp

main.o: main.cpp ManejadorDeVersiones.h constantes.h
	$(GCC) $(FLAGS) -c main.cpp

clean:
	rm $(EXECUTABLE) *.o

