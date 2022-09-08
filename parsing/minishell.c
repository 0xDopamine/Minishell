/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/08 04:37:50 by mbaioumy         ###   ########.fr       */
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

int	ft_strlen_q(char *q, char *eq)
{
	int	len;

	len = 0;
	while (q++ < eq)
		len++;
	return (len);
}

char	*ft_join_string(char *q, char *eq)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(1) * ft_strlen_q(q, eq) + 1);
	while (q < eq)
	{
		res[i++] = *q;
		q++;	
	}
	res[i] = '\0';
	return(res);
}

void	fetch_quoted(char **q, char **eq)
{
	char	*s;
	int		tok;

	tok = **q;
	s = *q + 1;
	*q = s;
	while (*s != tok && *s)
		s++;
	*eq = s;
	printf("fetch quoted eq: %s\n", *eq);	
}

void	fetch_string(char **q, char **eq)
{
	char	*s;
	int		tok;

	tok = **q;
	s = *q;
	*q = s;
	while (!ft_strchr(*s, "\'\"") && *s)
		s++;
	*eq = s--;	
}

void	fetch_env(char **q, char **eq)
{
	char	*s;

	s = *q;
	while (*s)
	{
		if (ft_strchr(*s, "\'\""))
			break ;
		s++;
	}
	*eq = s;
	printf("fetch env q: %s\n", *q);
	printf("fetch env eq: %s\n", *eq);
}

void	trim_string(char *q, char *eq)
{
	int	index;

	index = ft_strlen_q(q, eq);
	q[index] = '\0';
}

char	*ft_ultimate_string_handler(char **ps, t_env_p *env_list)
{
	char	*q;
	char	*eq;
	char	*res;

	eq = NULL;
	res = NULL;
	if (ps)
	{
		q = *ps;
		while (q)
		{
			if (ft_strchr(*q, "\'\""))
			{	
				fetch_quoted(&q, &eq);
				res = ft_strjoin(res, ft_join_string(q, eq));
				if (*res == '\'' && *res + 1 == '$')
					res = ft_search_for_env(res, env_list);
				else if (*res == '$')
					res = ft_assign_env(res, env_list);
				if (*eq + 1)
					q = eq + 1;
			}
			else if (ft_strchr(*q, "$"))
			{
				fetch_env(&q, &eq);
				trim_string(q, eq);
				printf("before q: %s\neq: %s\n", q, eq);
				res = ft_strjoin(res, ft_assign_env(q, env_list));
				printf("res: %s\n", res);
				q = eq;
				printf("q: %s\neq: %s\n", q, eq);
			}
			else
			{
				fetch_string(&q, &eq);
				res = ft_strjoin(res, ft_join_string(q, eq));
				if (*eq == '\0')
					break ;
				else
					q = eq;
			}
		}
	}
	if (res)
		*ps = res;
	return (*ps);
}

char	*ft_string_examiner(char *s, t_env_p *env_list)
{
	int		i;
	char	*temp;
	char	*res;

	i = 0;
	temp = s;
	res = ft_strdup("");
	while (temp[i])
	{
		printf("temp: %s\n", temp + i);
		if (temp[i + 1] == '\0')
			break ;
		if (ft_strchr(temp[i], "\"\'") && temp[i + 1] != 1)
		{	
			res = ft_strdup(ft_handle_quotes(temp, env_list));
			printf("res: %s\n", res);
			if (temp[i] == '\'' && *res =='$')
			{	
				res = ft_search_for_env(temp, env_list);
				printf("res search for env: %s\n", res);
			}
			else if (*res == '$')
				temp = res;
		}
		if ((temp[i] == '$' && temp[i] != 1))
		{
			res = ft_strjoin(res, ft_assign_env(temp + i + 1, env_list));
			if (res[0] == 1)
				i++;
			else if (ft_strchr(res[0], "\"\'"))
				temp = res;
		}
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

// char	**ft_split_env(char *s)
// {
// 	char	**split;
// 	int		i;
// 	int		words;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	words = ft_count_env(s);
// 	split = malloc(sizeof(char **) * words + 1);
// 	while (s[i])
// 	{
// 		if (s[i] == '$')
// 		{
// 			split[j] = malloc(sizeof(char *) * ft_envlen(s) + 1);
// 			i++;
// 			while (s[i] != '$')
			
// 		}
// 	}
// }

char	*ft_assign_env(char *s, t_env_p *env_list)
{
	int	i;
	char	**split;
	char	*ret;

	i = 0;
	split = ft_split(s, '$');
	ret = ft_strdup("");
	if (!ft_env_examiner(&s))
		return (s);
	if (*s == '?')
		return ("$?");
	if (split[0])
	{
		while (env_list->next != NULL)
		{
			if (ft_strcmp(split[0], env_list->name) == 0)
			{
				ret = ft_strjoin(ret, env_list->path);
				break ;
			}
			env_list = env_list->next;
		}
		i++;
	}
	if (**(split + 1) != '\0')
		ret = ft_strjoin(ret, env_list->path);
	if (*ret != '\0')
		return (ret);
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
		rl_on_new_line();
		write(1, "\n", 1);
		// rl_replace_line("", 0); /* comment all of this cuz we need to install brew and other things in goinfre */
		rl_redisplay();
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
	char	*temp;

	line = NULL;
	(void)argc;
	(void)argv;
	(void)env;
	simpleCommand = malloc(sizeof(t_cmd));
	ft_get_env(env, &env_list);
	env_list_p = (t_env_p *)env_list;
	printf("Two brothers minishell\n");
	//don't use CTRL -C signal now
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, ft_sig_handler);
	while (true)
	{
		line = readline(CYAN"TwoBrosShell➜ " RESET);
		temp = line;
		if (!temp)
		{
			free(temp);
			ft_putstr_fd("\nexit\n", NULL, STDOUT_FILENO);
			exit(255); /* needs to be finished */
		}
		if (*temp)
			add_history(temp);
		temp = spaces(temp);
		
		simpleCommand = parsepipe(&line, env_list_p, env);
		// system("leaks minishell");
		ft_check_cmd(simpleCommand, env, &env_list);
		free(temp);
		// demo(line);
	}
	free(temp);
	freethis(&line);
	free(simpleCommand);
	return 0;
}