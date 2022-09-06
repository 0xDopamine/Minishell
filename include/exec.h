/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:48:26 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/06 11:06:58 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# define true 1
# define NAME 1
# define PATH 2
# define EXIT_NOTFOUND 127
# define FIND 3
# define EDIT 4

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <sys/stat.h>
# include "parse.h"

typedef struct s_global
{
	int	exit_status;
}	t_global;

extern t_global	g;

typedef struct s_env
{
	char			*name;
	char			*path;
	int				index;
	struct s_env	*next;
}				t_env;

typedef struct s_red
{
	int	in_fd;
	int	out_fd;
}				t_red;


size_t	ft_strlen(char *str);
void	ft_exec(t_exec *line, char **env, t_env **env_list);
char	**ft_find_path(void);
int		ft_strcmp(char *s1, char *s2);
void	ft_get_env(char **env, t_env **env_list);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(char *path, char *name, int index);
void	ft_lstadd_front(t_env **lst, t_env *new);
void	del(char *path);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstdelone(t_env *lst, void (*del)(char*));
void	ft_check_cmd(t_cmd *cmd, char **env, t_env **env_list);
int		ft_cd(t_exec *line, t_env **env_list);
int		ft_echo(t_exec *line);
int		ft_unset(t_env **env, t_exec *line);
int		ft_pwd(void);
int		ft_envcmp(char *s1, char *s2);
void	ft_redirect(t_redir *redir, char **env, t_env **env_list);
void	ft_exec_mybuiltin(t_exec *line, char **env);
int		ft_ifmybuiltin(char *cmd, char **mybuiltins,
t_exec *line, t_env **env_list);
int		ft_builtins(char *cmd, t_exec *line, t_env **env_list);
int		ft_export(t_env **env, t_exec *line);
void	ft_pipes(t_pipe *pipes, char **env, t_env **env_list);
void	ft_exec_nofork(t_exec *line, char **env, t_env **env_list);
char	**ft_split_namecont(char *str);
void	ft_copy(char **ret, char *str, int sublen, int len);
void	ft_putstr_fd(char *str, char *str2, int fd);
void	ft_putchar_fd(char c, int fd);
int		export_checkname(char *str);
int		ft_exit(char **argv);
int		ft_atoi(char *str);
int		ft_env(t_env *env_list, char c);
void	ft_free_doubleptr(char **ptr);
char	*exec_ifaccess(char *cmd);
int		cd_errors(void);
int		echo_case1(char *str);
int		echo_path(char **av, int i, t_env *env_list, int ifnl);
int		cd_ifoldpwd(char *str, t_env **env_list);
int		cd_home(void);
int		cd_oldpwd(t_env **env_list);
int		export_checkpathname(char *str);
int		export_checkpath(char *str);
int		exec_checkcmd(char *cmd);
int		export_ifnotreplace(char *str, t_env *env_list);
void	pipes_fork_right(t_pipe *pipes, int *fds, char **env, t_env **env_list);
void	pipes_fork_left(t_pipe *pipes, int *fds, char **env, t_env **env_list);
void	pipes_access(t_exec *line);
void	ft_heredoc(t_env **env_list, t_cmd *cmd, char **env, char *delimiter);
void	execnofork_loop(char *cmd, char **av, char **env);

#endif