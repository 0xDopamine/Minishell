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

typedef struct s_env_p
{
	char			*name;
	char			*path;
	struct s_env_p	*next;
}				t_env_p;

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
int		ft_isalpha(int c);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*join_chars(char *curr, char *next);
int		get_token(char **ps, char **q);
int		is_whitespace(char *str, char *es);
char	*ft_strrchr(char *s, int c);
int		ft_strchr(char s, char *buf);
t_cmd   *execcmd(int words);
t_cmd   *redircmd(t_cmd *cmd, char *q, int mode, int fd);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
int		is_symbol(char *str, char *es);
t_cmd	*parseexec(char **ps, t_env_p *env_list);
t_cmd	*parseredir(t_cmd *cmd, char **ps);
t_cmd	*parsepipe(char **ps, t_env_p *env_list);
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
void	rl_replace_line(const char *str, int mod);
char	*ft_handle_quotes(char *q, t_env_p *env_list);
// char	*null_terminate(char *q);
char	*ft_assign_env(char *s, t_env_p *env_list);
char	*ft_string_examiner(char *s, t_env_p *env_list);
void	null_terminate(char **s);

#endif