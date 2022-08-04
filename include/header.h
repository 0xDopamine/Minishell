/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:24:01 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/08/04 05:11:43 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

enum e_define {
	PIPE,
	REDIR,
	EXEC
} ;

typedef struct s_cmd {
	int	type;
}	t_cmd ;

typedef struct s_redir {
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		mode;
	int		fd;
} t_redir ;

typedef struct s_pipe {
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe ;

typedef struct s_exec {
	int		type;
	char	**argv;
}	t_exec ;

void	ft_bzero(void *s, size_t n);
void	*ft_calloc (size_t count, size_t size);
char	**ft_split(char *s, char c);
void	freethis1(char **str);
int		wdlen(char *s, char c);
int		wdcount(char *s, char c);
char	**splitting(char *s, char c, int len, char **str);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
void	freethis(char **str);
char	*ft_strdup(char *src);
size_t	ft_strlen(char *str);
char	*findthewae(char **str);
char	*ft_strjoin(char *s1, char *s2);
// void	handle_pipes(char **env, char **token, t_list *cmd);
// void	child_process(char **env, t_list *cmd);
// void	execute(char **env, t_list *cmd);
// t_list	*lexer(t_token *token, t_list *lst_tokens, char *line);
// void	*parse(char **env, char *line);
// int		ft_lstsize(t_list *lst);
// t_list	*ft_lstnew(char *content, int type);
// void	ft_lstadd_front(t_list **lst, t_list *new);
// void	t_lstclear(t_list **lst);
// void	ft_lstadd_back(t_list **lst, t_list *new);
// t_list	*ft_lstlast(t_list *lst);
// int		ft_lstsize(t_list *lst);
// void	ft_lstdelone(t_list *lst, void (*del)(void *));
// void	ft_lstiter(t_list *lst, void (*f)(void *));
// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *));
// int		*copytoarray(t_list *stack);
// void	print_arr(int *arr, int size);
// void	print_list(t_list *stack);
int		ft_isalpha(int c);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
// t_cmd	*command_table(t_list *tokens);
char	*join_chars(char *curr, char *next);
int		get_token(char **ps, char **es, char **q);
int		is_whitespace(char *str, char *es);
char	*ft_strrchr(char *s, int c);
int		ft_strchr(char s, char *buf);
t_cmd   *execcmd(int words);
t_cmd   *redircmd(t_cmd *cmd, char *q, int mode, int fd);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
int		is_symbol(char *str, char *es);
t_cmd	*parseexec(char **ps);
t_cmd	*parseredir(t_cmd *cmd, char **ps);
t_cmd	*parsepipe(char **ps);
t_cmd	*parsecmd(char *s);
int		next(char **ps, char *toks);
int		wdcount_q(char *s, char c);
int		wdlen_q(char *s, char c);
char	**splitting_quotes(char *s, char c, int len, char **str);
char	**ft_split_quotes(char *s, char c);
char	*spaces(char *line);
char	*handle_spaces(char *line);
int		check(char before, char after);
char	*add_spaces(char *line, int count);

#endif