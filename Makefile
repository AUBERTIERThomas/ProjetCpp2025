CC=g++
CCFLAGS= -Wall -Werror -std=c++11 -g

cestincroyable.out :
	$(CC) $(CCFLAGS) jeu_chiffres0.cc -o  cestincroyable.out -lsfml-graphics -lsfml-window -lsfml-system

jouer: cestincroyable.out
	./cestincroyable.out

test : 
	$(CC) $(CCFLAGS) Tests_Unitaires.cc -o  tu.out -lsfml-graphics -lsfml-window -lsfml-system
	./tu.out

clean :
	rm -f *.o *.out
