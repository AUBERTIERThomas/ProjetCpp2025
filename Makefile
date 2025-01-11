CC=g++
CCFLAGS= -Wall -Werror -std=c++11 -g
SRC= $(wildcard ../*.cc)
OBJ= $(SRC:.cc=.o)
TST= $(wildcard *.cc)
OBJ_TEST = $(filter-out ../main.o, $(OBJ)) $(TST:.cc=.o)

cestincroyable.out :
	$(CC) $(CCFLAGS) jeu_chiffres0.cc -o  cestincroyable.out -lsfml-graphics -lsfml-window -lsfml-system

jouer: cestincroyable.out
	./cestincroyable.out

#%.o: %.cc
#	$(CC) $(CCFLAGS) -I../ -o $@ -c $<

clean :
	rm -f $(OBJ_TEST) cestincroyable.out
