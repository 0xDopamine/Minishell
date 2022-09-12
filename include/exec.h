/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:48:26 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/12 14:42:17 by abaioumy         ###   ########.fr       */
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
# define ENV 'a'
# define EXP 'e'
# define RED "\001\e[0;31m\002"
# define CYAN "\033[0;36m"
# define RESET   "\001\e[0m\002"
# define YELLOW "\033[0;33m"

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/wait.h>
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
	struct s_env	*next;
}				t_env;

typedef struct s_red
{
	int	in_fd;
	int	out_fd;
}				t_red;


size_t	ft_strlen(char *str);
t_env	*ft_lstnew(char *path, char *name);
void	ft_lstadd_back(t_env **lst, t_env *new);
void	ft_lstadd_front(t_env **lst, t_env *new);
void	ft_lstdelone(t_env *lst, void (*del)(char*));
t_env	*ft_lstlast(t_env *lst);
int		ft_lstsize(t_env *lst);
void	del(char *path);
int		ft_cd(t_exec *line, t_env **env_list);
int		ft_unset(t_env **env, t_exec *line);
int		ft_echo(t_exec *line);
int		ft_pwd(void);
int		ft_export(t_env **env, t_exec *line);
int		ft_env(t_env *env_list, char c);
int		ft_exit(char **argv);
void	ft_exec(t_exec *line, t_env **env_list);
void	ft_exec_nofork(t_exec *line, t_env **env_list);
void	ft_exec_mybuiltin(t_exec *line, char **env);
char	*exec_ifaccess(char *cmd);
int		exec_isdir(char *cmd);
int		exec_checkcmd_fork(char *cmd, char **av, char **env);
int		exec_checkcmd(char *cmd);
int		exec_cmdpath(char *cmd, char **env, char **av);
void	execnofork_loop(char *cmd, char **av, char **env);
int		cd_errors(void);
int		cd_ifoldpwd(char *str, t_env **env_list);
int		cd_home(void);
int		cd_oldpwd(t_env **env_list);
int		echo_case1(char *str);
int		echo_path(char **av, int i, t_env *env_list, int ifnl);
int		export_checkname(char *str);
int		export_checkpathname(char *str);
int		export_checkpath(char *str);
int		export_ifnotreplace(char *str, t_env *env_list);
char	**export_sortnames(t_env *env_list);
char	**export_swap(t_env *head, char **names);
int		unset_checkstr(char *str);
void	unset_loop(t_env *env, t_env *temp, t_env *prev, char **args);
char	**unset_copyargs(char **av, char **args);
void	env_printloop(t_env *list, char **names, int i);
char	**ft_find_path(void);
void	ft_get_env(char **env, t_env **env_list);
int		ft_envcmp(char *s1, char *s2);
char	**ft_myenv(t_env *env);
char	*ft_assign_env(char *s, t_env *env_list);
void	ft_check_cmd(t_cmd *cmd, t_env **env_list);
int		ft_redirect(t_redir *redir, t_env **env_list);
int		ft_builtins(char *cmd, t_exec *line, t_env **env_list);
int		ft_ifmybuiltin(char *cmd, char **mybuiltins,
t_exec *line, t_env **env_list);
void	ft_pipes(t_pipe *pipes, t_env **env_list);
int		pipes_fork_right(t_pipe *pipes, int *fds, t_env **env_list);
int		pipes_fork_left(t_pipe *pipes, int *fds, t_env **env_list);
void	pipes_access(t_exec *line);
char	**ft_split_namecont(char *str);
void	ft_copy(char **ret, char *str, int sublen, int len);
void	ft_putstr_fd(char *str, char *str2, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_atoi(char *str);
void	ft_free_doubleptr(char **ptr);
int		ft_heredoc(t_env **env_list, t_cmd *cmd, char *delimiter);
void    heredoc_writefile(char *delimiter, int fd, t_env **env_list);
char	*ft_handle_quotes(char *q, t_env *env_list);
char	*ft_string_examiner(char *s, t_env *env_list);
t_cmd	*parsepipe(char **ps, t_env *env_list);
t_cmd	*parseexec(char **ps, t_env *env_list);
t_cmd	*redircmd_test(t_cmd *right, t_cmd *left,char *q, int mode, int fd);
t_cmd	*parseredir_test(t_cmd *cmd, char **ps, t_env *env_list);
char	*ft_ultimate_string_handler(char **ps, t_env *env_list);

#endif