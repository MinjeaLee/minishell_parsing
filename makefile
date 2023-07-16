NAME = parser

SRCS = remove_qoute.c second.c split_respect_quote.c util.c

OBJS = $(SRCS:.c=.o)

CC = gcc

%.o: %.c
	$(CC) -g -O0 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -g -O0 $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

