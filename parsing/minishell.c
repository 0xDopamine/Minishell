/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/14 02:16:04 by mbaioumy         ###   ########.fr       */
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

char	*ft_search_for_env(char *s, t_env *env_list)
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
	int		len;
	char	*temp;
	char	*es;

	len = 0;
	temp = q;
	es = eq;
	while (temp++ < es)
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
	if (*s == '\0')
	{
		**q = 1;
		ft_putstr_fd("Quotes error\n", NULL, STDERR_FILENO);
		return ;
	}
	*eq = s;
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
		if (ft_strchr(*s, "\'\"") || !ft_isalnum(*s))
			break ;
		s++;
	}
	*eq = s;
}

void	trim_string(char *q)
{
	int		i;
	char	*temp;

	i = 0;
	temp = q;
	while (temp[i])
	{
		if (ft_strchr(temp[i], "\'\""))
			break ;
		i++;		
	}
	q[i] = '\0';
}

int		ft_count_dollars(char *q)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (q[i])
	{
		while (q[i] == '$' && q[i])
		{
			i++;
			count++;
			if (q[i] != '$')
				return(count);
		}
		i++;
	}
	return (count);
}

void	ft_check_envs(char **q)
{
	int		count;
	char	*s;

	s = *q;	
	count = ft_count_dollars(s);
	if (count % 2 == 0)
		while (*s && *s == '$')
			s++;
	else if (count % 2 != 0)
		while (*s && *(s + 1) == '$')
			s++;
	*q = s;
}

char	*ft_ultimate_string_handler(char **ps, t_env *env_list, int *state)
{
	char	*q;
	char	*eq;
	char	*res;
	int		dollars;

	dollars = 0;
	eq = NULL;
	res = NULL;
	(void)state;
	if (ps)
	{
		q = *ps;
		while (q)
		{
			if (ft_strchr(*q, "\'\""))
			{
				fetch_quoted(&q, &eq);
				if (*q == 1)
					return NULL;
				if (*q == '$' && *eq != '\'')
				{					
					fetch_env(&q, &eq);
					if (*q == 1)
						return NULL;
					q = ft_join_string(q, eq);
					res = ft_strjoin(res, ft_assign_env(q, env_list));
					
				}
				else if (*q == '\'' && (*(q + 1) == '$') && *eq ==  '"')
					res = ft_strjoin(res, ft_search_for_env(q, env_list));
				else
					res = ft_strjoin(res, ft_join_string(q, eq));
				if (*eq + 1)
					q = eq + 1;
			}
			else if (ft_strchr(*q, "$"))
			{
				ft_check_envs(&q);
				if (*q == '$')
				{	
					fetch_env(&q, &eq);
					q = ft_join_string(q, eq);
					if (*q == '$' && *(q + 1) == '\0')
						res = ft_strjoin(res, "$");
					else
						res = ft_strjoin(res, ft_assign_env(q, env_list));
					q = eq;
				}			
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

char	*ft_assign_env(char *s, t_env *env_list)
{
	int	i;
	char	**split;
	char	*ret;
	t_env	*temp_list;
	int		flag;

	i = 0;
	flag = 0;
	if (*s == '$' && *(s + 1) == '\0')
		return (NULL);
	split = ft_split(s, '$');
	if (*split == NULL)
		return (NULL);
	ret = ft_strdup("\0");
	if (!ft_env_examiner(&s))
		return (s);
	if (**split == '?')
		return ("$?");
	while (split[i])
	{
		temp_list = env_list;
		while (temp_list != NULL)
		{
			if (ft_strcmp(split[i], temp_list->name) == 0)
			{
				ret = ft_strjoin(ret, temp_list->path);
				flag = 1;
				break ;
			}
			temp_list = temp_list->next;
		}
		i++;
	}
	if (ret != NULL)
		return (ret);
	return (NULL);
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

char	*ft_handle_quotes(char *q, t_env *env_list)
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
		rl_replace_line("", 0); /* comment all of this cuz we need to install brew and other things in goinfre */
		rl_redisplay();
		g.exit_status = 130;
		return ;
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_cmd	*simpleCommand;
	t_env 	*env_list;
	char	*temp;

	line = NULL;
	(void)argc;
	(void)argv;
	(void)env;
	simpleCommand = malloc(sizeof(t_cmd));
	ft_get_env(env, &env_list);
	printf("Two brothers minishell\n");
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		line = readline("TwoBrosShell➤ ");
		temp = line;
		if (!temp)
		{
			free(temp);
			ft_putstr_fd("\nexit\n", NULL, STDOUT_FILENO);
			exit(255); /* needs to be finished */
		}
		add_history(temp);
		temp = spaces(temp);
		simpleCommand = parsepipe(&temp, env_list);
		
		ft_check_cmd(simpleCommand, &env_list);
		
	}
	free(temp);
	freethis(&line);
	free(simpleCommand);
	return 0;
}