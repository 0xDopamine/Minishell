/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/22 03:33:52 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <readline/readline.h>

t_token *init_token(char *value, int type)
{
	t_token *token = ft_calloc(1, sizeof(t_token));
	token->value = value;
	token->type = type;
	return (token);
}

t_token	*append_token(char c, int type)
{
	char	*value;
	t_token	*tok;

	value = ft_calloc(2, sizeof(char));
	tok = malloc(sizeof(t_token));
	value[0] = c;
	tok = init_token(value, type);
	return(tok);
}

t_token	*ft_isgreat(char *str)
{
	int		i;
	t_token	*tok;
	char	*value;
	int		type;

	i = 0;
	tok = malloc(sizeof(t_token));
	value = NULL;
	type = 0;
	while (str[i] != ' ' && str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>') && str[i + 1])
		{
			value = ft_calloc(3, sizeof(char));
			value[0] = str[i];
			value[1] = str[i + 1];
			type = 3;
			break ;
		}
		else if ((str[i] == '>' && str[i + 1] != '>') && str[i + 1])
		{
			value = ft_calloc(2, sizeof(char));
			value[0] = str[i];
			type = 2;
			break ;
		}
		i++;
	}
	tok = init_token(value, type);
	return (tok);
}

t_token	*ft_isless(char *str)
{
	int		i;
	t_token	*tok;
	char	*value;
	int		type;

	i = 0;
	tok = malloc(sizeof(t_token));
	type = 0;
	value = NULL;
	while (str[i] != ' ' && str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 1])
		{
			value = ft_calloc(3, sizeof(char));
			value[0] = str[i];
			value[1] = str[i + 1];
			type = 3;
			break ;
		}
		else if (str[i] == '<' && str[i + 1] != '<' && str[i + 1])
		{
			value = ft_calloc(2, sizeof(char));
			value[0] = str[i];
			type = 2;
			break ;
		}
		i++;
	}
	tok = init_token(value, type);
	return (tok);
}

t_token	*append_string(char *value, int type)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	token->value = ft_strdup(value);
	token->type = type;
	return (token);
}

char	*init_value(char c)
{
	char	*value;
	
	value = malloc(sizeof(char) * 2);
	value[0] = c;
	value[1] = '\0';
	return (value);
}

t_list	*lexer(t_token *token, t_list *lst_tokens, char *line)
{
	int		i;
	int		cmd_count;

	i = 0;
	token = malloc(sizeof(t_token));
	cmd_count = 0;
	while (line[i])
	{
		if (ft_isalpha(line[i]))
			token = append_token(line[i], 6);
		else if (line[i] == '|')
			token = append_token(line[i], 0);
		else if (line[i] == ' ')
			token = append_token(line[i], 1);
		else if (line[i] == '>')
		{
			if (ft_strncmp(line + i, ">>", 3))
			{
				token = append_string(">>", 3);
				i++;
			}
			else
				token = append_token('>', 2);
		}
		else if (line[i] == '<')
		{
			if (ft_strncmp(line + i, "<<", 3))
			{
				token = append_string("<<", 5);
				i++;
			}
			else
				token = append_token('<', 4);
		}
		else if (line[i] == '\'')
			token = append_token(line[i], 7);
		else if (line[i] == '\"')
			token = append_token(line[i], 8);
		else if (line[i] == '-')
			token = append_token(line[i], 9);
		ft_lstadd_back(&lst_tokens, ft_lstnew(token->value, token->type));
		i++;
	}
	return (lst_tokens);
}

t_list	*process(char *line)
{
	t_token	*token;
	t_list	*lst_tokens;

	token = malloc(sizeof(t_token));
	lst_tokens = NULL;
	lst_tokens = lexer(token, lst_tokens, line);
	return (lst_tokens);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*lst_tokens;
	t_cmd	*simpleCommand;

	line = NULL;
	(void)argc;
	(void)argv;
	(void)env;
	lst_tokens = malloc(sizeof(t_list));
	simpleCommand = malloc(sizeof(t_cmd));
	while (1)
	{
		line = readline("$>");
		if (line)
			add_history(line);
		lst_tokens = process(line);
		print_list(lst_tokens);
		simpleCommand = command_table(lst_tokens);
	} 
	return 0;
}