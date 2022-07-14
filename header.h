/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:24:01 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/14 22:13:30 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_simple_cmd {
    char   *name;
    char    **args;
    int     fd[2]; 
} t_simple_cmd;

typedef struct s_cmd {
    int numberofCmds;
    t_simple_cmd *simpleCommand;
} t_cmd;

void	        ft_bzero(void *s, size_t n);
void            *ft_calloc (size_t count, size_t size);
char	        **ft_split(char *s, char c);
void	        freethis1(char **str);
int             wdlen(char *s, char c);
int	            wdcount(char *s, char c);
char	        **splitting(char *s, char c, int len, char **str);
int	            ft_strncmp(char *s1, char *s2, unsigned int n);
void	        freethis(char **str);
char	        *ft_strdup(char *src);
size_t	        ft_strlen(char *str);
char	        *findthewae(char **str);
char	        *ft_strjoin(char *s1, char *s2);
void	        handle_pipes(char **env, char **token, t_simple_cmd *cmd);
void	        child_process(char **env, t_simple_cmd *cmd);
void	        execute(char **env, t_simple_cmd *cmd);
int	            lexer(char **env, char **token, t_simple_cmd *cmd);
void	        *parse(char **env, char *line);

#endif