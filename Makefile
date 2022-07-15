CC = gcc

CFLAGS = -Wall -Werror -Wextra  #-fsanitize=address -g

SRCS = minishell.c lists_tools.c lists_tools_2.c utils.c utils_2.c utils_3.c

HEADER_H = header.h 

MINISHELL_A = minishell.a

NAME = minishell.a

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	rm -f $(BONUS)
	ar rc $(NAME) $(OBJS) $(MINISHELL_A) $(HEADER_H)
#$(CC) $(CFLAGS) $(SRCS) -w -DMEMWATCH -DMW_STDIO memwatch-2.71/memwatch.c  -o push_swap && rm -rf memwatch.log
	$(CC) $(CFLAGS) -lreadline $(NAME)  -o minishell

re: fclean all

clean:
	rm -f $(NAME)
	rm -f *.o 

fclean:	clean
	rm -f minishell

.PHONY: clean fclean re all