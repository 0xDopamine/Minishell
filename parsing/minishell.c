/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/04 02:31:53 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"
#include <readline/readline.h>

t_global g = { 0 };

void	null_terminate(char **s)
{
	int		len;
	int		i;
	char	*q;

	i = -1;
	q = *s;
	len = ft_strlen(q);
	while (++i < len)
		q++; 
	*q = '\0';
}

char	*ft_search_for_env(char *s, t_env_p *env_list)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			s = ft_handle_quotes(s, env_list);
			res = ft_strjoin(res, "'");
			res = ft_strjoin(res, ft_assign_env(s + 1, env_list));
			res = ft_strjoin(res, "'");
			return (res);
		}
		else
			return (ft_strjoin(res, ft_assign_env(s + 1, env_list)));
		i++;
	}
	return (s);
}

char	*ft_string_examiner(char *s, t_env_p *env_list)
{
	int		i;
	char	*temp;
	char	*res;
	int		j;

	i = 0;
	temp = s;
	res = NULL;
	while (temp[i])
	{
		if (ft_strchr(temp[i], "\"\'") && temp[i] != 1)
		{	
			j = 0;
			res = ft_strdup(ft_handle_quotes(temp, env_list));			
			// printf("-----------res examiner %s\n", res);
			if (res[0] == '\'' && res[1] == '$' && temp[i] != '\'')
				return (ft_search_for_env(res, env_list));
			else if (res[0] == '$' && temp[i] == '"')
				return (ft_assign_env(res + 1, env_list));
			break ;
		}
		else if (temp[i] == '$' && temp[i] != 1)
		{
			res = ft_assign_env(temp + i + 1, env_list);
			// printf("res: %s\n", res);
			if (res[0] == 1)
				i++;
			else if (ft_strchr(res[0], "\"\'"))
				temp = res;
		}
		// printf("temp + %d: %s\n", i, temp + i);
		i++;
	}
	if (!res)
		return (s);
	return (res);
}

int	ft_env_examiner(char **s)
{
	char	*q;

	q = *s;
	while (*q)
	{
		if (*q == '$' && *q)
			q++;
		while (!ft_strchr(*q, "\'\"") && *q)
			q++;
		if (ft_strchr(*q, "\'\"") && *q)
		{
			q--;
			*q = 1;
			*s = q + 1;
			return (0);
		}
		if (!*q)
			break ;
		q++;
	}
	return (1);
}

char	*ft_assign_env(char *s, t_env_p *env_list)
{
	int	i;

	i = 0;
	if (!ft_env_examiner(&s))
		return (s);
	while (env_list->next != NULL)
	{
		if (ft_strcmp(s, env_list->name) == 0)
			return (env_list->path);
		env_list = env_list->next;
	}
	*s = '\0';
	return (s);
}

int	ft_check_quotes(char *s)
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
			if (s[j] == '\0')
			{
				perror("Quotes error");
				g.exit_status  = 256;
				return (0);
			}
			else
				i++;
		}
		else
			i++;
	}
	return (1);
}

char	*ft_handle_quotes(char *q, t_env_p *env_list)
{
	char	*s;
	char	*res;
	char	*temp;
	int		i;

	s = q;
	(void)env_list;
	res = malloc(sizeof(char) * 10000000000);
	res[0] = 0;
	i = 0;
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
				// printf("res %s\n", res);
				if (*(temp) != '\0')
					s = temp + 1;
				else
					return (res);
			}
			else
				s++;
			while (*temp == *s && *s)
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
	while (true)
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
		// system("leaks minishell");
		// ft_check_cmd(simpleCommand, env, &env_list);
		// demo(line);
	} 
	return 0;
}