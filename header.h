/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:24:01 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/15 21:39:22 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_list {
	char			**content;
	struct s_list   *next;
}   t_list;

typedef struct s_cmd {
	int numberofCmds;
	t_list	*simpleCommand;
} t_cmd;

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
void	handle_pipes(char **env, char **token, t_list *cmd);
void	child_process(char **env, t_list *cmd);
void	execute(char **env, t_list *cmd);
int		lexer(char **env, char **token, t_list *cmd);
void	*parse(char **env, char *line);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(char **content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	t_lstclear(t_list **lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *));
int		*copytoarray(t_list *stack);
void	print_arr(int *arr, int size);
void	print_list(t_list *stack);
#endif