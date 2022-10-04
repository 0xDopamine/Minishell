
#* TARGET *#
TARGET = minishell

#*SOURCE FILES *#
PARSING = utils_4.c tokenizer_tools.c parser_tools.c free.c split_quotes_test.c split_quotes_tools.c string_handler.c tokeniser.c evar.c string_handler_tools.c \
		env.c split_quotes.c quotes.c spaces_tools.c strings_tools.c strings_tools_2.c \
		minishell.c parser.c utils.c utils_2.c utils_3.c init_nodes.c  
EXEC = execute.c execute_specialcase.c start_execution.c mini_libft.c \
		path.c list.c redir.c pipes.c exec_utils2.c find_builtins.c \
		my_exit.c my_env.c my_export.c \
		my_echo.c my_cd.c my_pwd.c my_unset.c \
		free.c exec_utils.c my_cd_utils.c my_echo_utils.c \
		my_export_utils.c heredoc.c heredoc_utils.c \
		my_env_utils.c my_export_utils2.c my_unset_utils.c \
		 redir_utils.c heredoc_utils2.c itoa.c list_redir.c signals.c heredoc_utils3.c
SRC = $(addprefix parsing/, $(PARSING)) \
	  $(addprefix execution/, $(EXEC))

#* READLINE PATH *#
READLINE_DIR = $(addprefix $(shell brew --prefix readline), /)

#* OBJECT FILES *#
OBJS = $(SRC:%.c=%.o)

#* FLAGS *#
FLAGS = -g -fsanitize=address

#* parse FILES *#
INCLUDE = include/

#* DELETE *#
DEL = rm -rf

all: $(TARGET)
	

%.o: %.c
	cc $(FLAGS) -c -I $(INCLUDE) $< -o $@

$(TARGET): $(OBJS) $(INCLUDE)
	cc $(FLAGS) -I $(INCLUDE) -L $(addprefix $(READLINE_DIR), lib) -I $(addprefix $(READLINE_DIR), include) $(OBJS) -o $(TARGET) -lreadline

re: fclean all

clean:
	$(DEL) $(OBJS)

fclean:	clean
	$(DEL) $(TARGET)

.PHONY: clean fclean re all
