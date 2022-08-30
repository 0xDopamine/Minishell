/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/08/30 19:45:10 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"
#include <readline/readline.h>

t_global g = { 0 };

char	*ft_string_examiner(char *s, t_env_p *env_list)
{
	int		i;
	char	*temp;
	char	*res;

	i = 0;
	temp = s;
	res = NULL;
	// printf("inside func: %s\n", s);
	while (temp[i])
	{
		if (ft_strchr(temp[i], "\"\'"))
		{	
			res = ft_strdup(ft_handle_quotes(temp, env_list));
			break ;
		}
		else if (temp[i] == '$')
		{
			res = ft_assign_env(temp + i, env_list);
			break ;
		}
		// printf("res = %s\n", res);
		i++;
	}
	if (!res)
		return (s);
	return (res);
}

char	*ft_assign_env(char *s, t_env_p *env_list)
{
	int	i;

	i = 0;
	// printf("string %s\n", s);
	// while (s[i])
	// {
	// 	if (s[i] == '$')
	// 	{
	// 		printf("here %s\n", s + i + 1);
	// 		return (ft_assign_env(s + i + 1, env_list));
	// 	}	
	// 	i++;
	// }
	while (env_list->next != NULL)
	{
		if (ft_strcmp(s, env_list->name) == 0)
			return (env_list->path);
		env_list = env_list->next;
	}
	*s = '\n';
	return (s);
}

void	ft_check_quotes(char *s)
{
	int		i;
	int		j;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(s[i], "\'\""))
		{
			j = i + 1;
			while (s[j] != s[i] && s[j])
				j++;
		}
		if (s[j + 1])
			i;
		else
		{
			perror("Quotes error");
			g.exit_status  = 256;
			return ;
		}
		i++;
	}
	return ;
}

char	*ft_handle_quotes(char *q, t_env_p *env_list)
{
	char	*s;
	char	*res;
	char	*temp;
	int		i;

	s = q;
	res = malloc(sizeof(char) * 10000000000);
	res[0] = 0;
	i = 0;
	// ft_check_quotes(s);
	while (s)
	{	
		if (*s && ft_strchr(*s, "\"\'"))
		{
			temp = s + 1;
			if (*temp != '\0' && *temp != *s)
			{
				while ((*temp != *s || !ft_strchr(*temp, "\'\"")) && *temp)
					res[i++] = *temp++;
				res[i] = '\0';
				if (res[0] == '$' && *s == '"')
					res = ft_assign_env(res + 1, env_list);
				if (res[0] == '\n')
					i = 0;
				if (*temp != '\0')
					s = temp + 1;
				else
					return (res);
			}
			else
				s++;
		}
		else if (!ft_strchr(*s, "\"\'"))
		{
			temp = s;
			while (!ft_strchr(*temp, "\'\"") && *temp)
					res[i++] = *temp++;
			res[i] = '\0';
			if (*temp != '\0')
					s = temp;
			else
				return (res);
		}
		else
			s++;	
	}
	return(res);
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		// rl_on_new_line();
		// write(1, "\n", 1);
		// rl_replace_line("", 0); /* comment all of this cuz we need to install brew and other things in goinfre */
		// rl_redisplay();
		g.exit_status = 130;
		return ;
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
		g.exit_status = 0;
		return ;
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_cmd	*simpleCommand;
	t_env 	*env_list;
	t_env_p	*env_list_p;

	line = NULL;
	(void)argc;
	(void)argv;
	simpleCommand = malloc(sizeof(t_cmd));
	ft_get_env(env, &env_list);
	env_list_p = (t_env_p *)env_list;
	printf("Two brothers minishell\n");
	//don't use CTRL -C signal now
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, ft_sig_handler);
	while (1)
	{
		line = readline("$> ");
		if (!line)
		{
			ft_putstr_fd("\nexit\n", NULL, STDOUT_FILENO);
			exit(255); /* needs to be finished */
		}
		if (*line)
			add_history(line);
		line = ft_strdup(spaces(line));
		simpleCommand = parsepipe(&line, env_list_p);
		ft_check_cmd(simpleCommand, env, &env_list);
		// system("leaks minishell");
		// demo(line);
	} 
	return 0;
}