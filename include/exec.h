/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:48:26 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/13 15:45:49 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include "header.h"

typedef struct s_global
{
	int exit_status;
}	t_global;

extern t_global g;

typedef struct s_env
{
	char			*type;
	char			*content;
	struct s_env	*next;   
}               t_env;

size_t  ft_strlen(char *str);
void	ft_exec(t_exec *line, char **env, t_env **env_list);
char    **ft_find_path(void);
void	ft_get_env(char **env, t_env **env_list);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(char *content, char *type);
void	ft_lstadd_front(t_env **lst, t_env *new);
void	del(char *content);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstdelone(t_env *lst, void (*del)(char*));
void	ft_check_cmd(t_cmd *cmd, char **env, t_env **env_list);
int		ft_cd(t_exec *line, t_env **env_list);
int		ft_echo(t_exec *line, t_env *env_list);
int		ft_unset(t_env **env, t_exec *line);
int		ft_pwd(t_exec *line);
int		ft_envcmp(char *s1, char *s2);
void    ft_redirect(t_redir *redir, char **env, t_env **env_list);
void	ft_exec_mybuiltin(t_exec *line, char **env);
int		ft_ifmybuiltin(char *cmd, char **mybuiltins, t_exec *line, t_env **env_list);
int		ft_builtins(char *cmd, t_exec *line, t_env **env_list);
int		ft_export(t_env **env, t_exec *line);
void    ft_pipes(t_pipe *pipes, char **env, t_env **env_list);
void    ft_exec_nofork(t_exec *line, char **env, t_env **env_list);
char	**ft_split_typecont(char *str);
void	ft_copy(char **ret, char *str, int sublen, int len);
void	ft_putstr_fd(char *str, int fd);
int		export_checktype(char *str);
int		ft_exit(char **argv);
int		ft_atoi(char *str);
int		ft_env(t_env *env_list, char **av);

#endif