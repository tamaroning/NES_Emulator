CC := g++

main : main.o emulator_function.o instruction.o

main.o : emulator_function.o instruction.o


clean :
	$(RM) -f *.o
	$(RM) -f main