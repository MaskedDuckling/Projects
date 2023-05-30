NAME = PONG

CC = g++

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRC = main.cpp		\
	Paddle.cpp		\
	Ball.cpp		\
	Game.cpp

SRCS		= $(addprefix srcs/, $(SRC))

OBJS		= $(addprefix objs/, $(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 $(CFLAGS) -o $(NAME)

objs/%.o:	srcs/%.cpp
			$(CC) $(CFLAGS) -o $@ -c $<
.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

po: all clean

re: fclean all

.PHONY: all re clean fclean
