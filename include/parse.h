 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:24:01 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/08/25 03:46:13 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

enum {
	PIPE,
	REDIR,
	EXEC,
	HEREDOC
} ;

enum {
	QUOTED,
	NOT_QUOTED
}	;

enum {
	IS_VAR,
	NOT_VAR
}	;

typedef struct s_data {
	char	*res;
	char	*q;
	char	*eq;
	char	*temp;
}	t_data ;

typedef struct s_space {
	int		i;
	int		j;
	char	*str;
	size_t	len;
}	t_space ;

typedef struct s_handle {
	char	*q;
	char	*eq;
	char	*res;
}	t_handle;

typedef struct s_parse {
	int		tok;
	int		argc;
	int		*state;
	int		words;
	char	**split;
	char	*q;
}	t_parse;

typedef struct s_cmd {
	int	type;
}	t_cmd;

typedef struct s_split {
	int		i;
	int		j;
	int		k;
	int		len;
	int		tok;
}	t_split ;

typedef struct s_redir {
	int				type;
	t_cmd			*cmd;
	char			*file;
	int				mode;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_pipe {
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

typedef struct s_exec {
	int		type;
	char	**argv;
	pid_t	pid;
}	t_exec;

typedef struct s_env_p
{
	char			*name;
	char			*path;
	struct s_env_p	*next;
}	t_env_p;

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		**ft_split(char *s, char c);
void		freethis1(char **str);
int			wdlen(char *s, char c);
int			wdcount(char *s, char c);
void		splitting(char *s, char c, int len, char **str);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
void		freethis(char **str);
char		*ft_strdup(char *src);
size_t		ft_strlen(char *str);
char		*findthewae(char **str);
char		*ft_strjoin(char *s1, char *s2);
int			ft_isalpha(int c);
int			ft_strcmp(char *s1, char *s2);
char		*join_chars(char *curr, char *next);
int			get_token(char **ps, char **q);
int			is_whitespace(char *str);
char		*ft_strrchr(char *s, int c);
int			ft_strchr(char s, char *buf);
t_cmd		*execcmd(int words);
t_redir		*redircmd(t_cmd *cmd, char *q, int mode, int fd);
t_cmd		*pipecmd(t_cmd *left, t_cmd *right);
int			is_symbol(char *str);
t_cmd		*parsecmd(char *s);
int			next(char **ps, char *toks);
int			wdcount_q(char *s, char c);
int			wdlen_q(char *s, char c);
char		**splitting_quotes(char *s, char c, int len, char **str);
char		**ft_split_quotes(char *s, char c);
char		*spaces(char *line);
char		*handle_spaces(char *line);
int			check(char before, char after);
char		*add_spaces(char *line, int count);
void		rl_replace_line(const char *str, int mod);
void		null_terminate(char **s);
int			ft_is_heredoc(char **ps);
int			ft_isalnum(int arg);
int			count_words(char *str, char c);
void		fetch_quoted(char **q, char **eq);
char		*ft_join_string(char *q, char *eq);
int			check_state(int *state);
void		ft_lstadd_redir(t_redir **lst, t_redir *new);
int			ft_strlen_q(char *q, char *eq);
char		**ft_split_q(char *str, char sep);
char		*ft_join_string(char *q, char *eq);
void		fetch_string(char **q, char **eq);
void		fetch_env(char **q, char **eq);
void		trim_string(char *q);
int			ft_count_dollars(char *q);
int			ft_strlen_q(char *q, char *eq);
void		fetch_quoted(char **q, char **eq);
int			ft_check_quotes(char *s);
int			ft_env_examiner(char **s);
void		ft_check_envs(char **q);
int			*check_var(char *str);
int			num_words(char *str, int quote_flag);
void		ft_append_redir_list(t_redir **head, t_parse *parse, t_cmd *cmd);
char		**ft_split_argv(t_parse *parse);
int			ft_init_words(char	**ps);
char		*loop_spaces(t_space space, char *line);
int			check_state(int *state);
int			*check_var(char *str);
void		ft_lstadd_redir(t_redir **lst, t_redir *new);
char		**ft_split(char *s, char c);
char		**ft_split_q(char *str, char sep);
int			ft_strchr(char s, char *buf);
t_redir		*redircmd(t_cmd *cmd, char *q, int mode, int fd);
char		*set_free(char *ptr, char *ptr2, char **dptr, char *return_value);

#endif