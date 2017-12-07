NAME=semting

all: $(NAME).o
	gcc -o $(NAME).out $(NAME).o

$(NAME).o: $(NAME).c
	gcc -c $(NAME).c


run: all
	./$(NAME).out

clean:
	rm -f ./$(NAME).out
	rm -f ./$(NAME).o
