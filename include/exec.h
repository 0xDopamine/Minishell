/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:48:26 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/02 12:53:49 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include "header.h"

typedef struct s_env
{
	char			*content;
	struct s_env	*next;   
}               t_env;

size_t  ft_strlen(char *str);
void	ft_exec(t_exec *cmd);
char    **ft_find_path(void);
void	ft_get_env(char **env, t_env **env_list);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(char *content);
void	ft_lstadd_front(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);

#endif