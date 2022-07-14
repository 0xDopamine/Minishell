/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:24:01 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/09 01:24:01 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char   *name;
    char    **args;
    int     fd[2]; 
} simpleCommands;

typedef struct {
    int numberofCmds;
    simpleCommands **simpleCommand;
} Command ;

void	ft_bzero(void *s, size_t n);
void    *ft_calloc (size_t count, size_t size);

#endif