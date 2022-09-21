/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:48:26 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:22:17 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# define TRUE 1
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
	int	here_sig;
}	t_global;

extern t_global	g_var;

typedef struct s_env
{
	char			*name;
	char			*path;
	struct s_env	*next;
}				t_env;

typedef struct s_write
{
	char	*line;
	char	*ret;
	char	*str;
	int		index;
}				t_write;

typedef struct s_here
{
	int		fd_creat;
	int		fd_read;
	char	*file_path;
	char	*delimiter;
	t_cmd	*cmd;
}				t_here;

typedef struct s_red
{
	int	in_fd;
	int	out_fd;
}				t_red;

typedef struct s_mini {
	t_exec	*cmd;
	t_cmd	*ret;
	t_parse	*parse;
}				t_mini;

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
int		ft_echo(t_exec *line, int fd);
int		ft_pwd(void);
int		ft_export(t_env **env, t_exec *line);
int		ft_env(t_env *env_list, char c);
int		ft_exit(char **argv);
void	ft_exec(t_exec *line, t_env **env_list);
void	ft_exec_nofork(t_exec *line, t_env **env_list);
void	ft_exec_mybuiltin(t_exec *line, char **env);
void	ft_sig_handler(int sig);
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
int		echo_case1(char *str, int fd);
int		echo_path(char **av, int i, t_env *env_list, int ifnl);
void	echo_str_nl(char **av, int i);
void	echo_str_nonl(char **av, int i);
int		export_checkname(char *str);
int		export_checkpathname(char *str);
int		export_checkpath(char *str);
int		export_ifnotreplace(char *str, t_env *env_list);
void	export_addvar(char **av, t_env **env);
int		export_ifexists(char *name, char *path, t_env **env);
int		export_checkav(char *str, char **ptr, int n);
int		export_checkop(char *str);
int		export_checknbr(char ch);
char	**export_sortnames(t_env *env_list);
char	**export_swap(t_env *head, char **names);
int		unset_checkstr(char *str);
void	unset_loop(t_env *env, t_env *prev, char **args);
char	**unset_copyargs(char **av, char **args);
void	env_printloop(t_env *list, char **names, int i);
char	**ft_find_path(void);
void	ft_get_env(char **env, t_env **env_list);
int		ft_envcmp(char *s1, char *s2);
char	**ft_myenv(t_env *env);
char	*ft_assign_env(char *s, t_env *env_list);
void	ft_check_cmd(t_cmd *cmd, t_env **env_list);
int		ft_redirect(t_redir *redir, t_env **env_list);
int		ft_redirect_input(t_redir *redir, t_red *red);
int		ft_redirect_output(t_redir *redir, t_red *red);
int		redir_isdir(char *cmd);
int		ft_builtins(char *cmd, t_exec *line, t_env **env_list);
int		ft_ifmybuiltin(char *cmd, t_exec *line, t_env **env_list);
int		ft_ifmybuiltin_up(char *cmd, t_exec *line, t_env **env_list);
int		ft_strlen_char(char *str, char ch);
void	ft_pipes(t_pipe *pipes, t_env **env_list);
int		pipes_fork_right(t_pipe *pipes, int *fds, t_env **env_list);
int		pipes_fork_left(t_pipe *pipes, int *fds, t_env **env_list);
void	pipes_access(t_exec *line);
char	**ft_split_namecont(char *str);
void	ft_copy(char **ret, char *str, int sublen, int len);
void	ft_putstr_fd(char *str, char *str2, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_atoi(char *str);
char	*ft_itoa(int n);
void	ft_free_doubleptr(char **ptr);
int		ft_heredoc(t_here *here, t_redir *redir, t_env **env_list);
int		heredoc_create(char *file_path);
void	heredoc_writefile(char *delimiter, int fd, t_env **env_list);
int		heredoc_open(char *file_path, t_cmd *cmd, t_env **env_list);
void	heredoc_specialcase(t_write *w, t_env **env_list);
char	*heredoc_getstr(char *str);
char	*heredoc_gen_name(int i);
int		heredoc_findsign(char *str);
char	*ft_handle_quotes(char *q);
char	*ft_string_examiner(char *s, t_env *env_list);
t_cmd	*parsepipe(char **ps, t_env *env_list);
t_cmd	*parseexec(char **ps, t_env *env_list);
t_redir	*redircmd_test(t_cmd *cmd, char *q, int mode, int fd);
t_cmd	*parseredir(t_cmd *cmd, char **ps);
char	*ft_ultimate_string_handler(char **ps, t_env *env_list);
void	ft_putnbr_fd(int nb, int fd);
char	*get_next_line(int fd);
char	*ft_search_for_env(char *s, t_env *env_list);
char	*ft_assign_env(char *s, t_env *env_list);
void	ft_append_command(t_exec *cmd, t_parse *parse, t_env *env_list);
int		ft_here_signal(int infd);
void	ft_sig_here(int signal);
int		start_heredoc(t_here *here, t_redir *redir, int infd_dup, t_env **env_list);
int		start_redir(t_redir *redir, t_red *red);

#endif