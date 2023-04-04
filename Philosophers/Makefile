NAME = philo

SRC = main.c control_input.c

CC = gcc

FLAGS = -Wall -Wextra -g

FLAGS_DATARACE = -fsanitize=thread -g

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

data races:
	$(CC) $(FLAGS_DATARACE) $(SRC) -o $(NAME)

clean:
	rm -fr $(NAME)
	rm -fr *.dSYM

re:
	clean all

.PHONY: all clean re