/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserv2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <gpouzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:28:26 by gpouzet           #+#    #+#             */
/*   Updated: 2023/09/13 11:16:15 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int check_quote(char *readline) 
{
	int	one;
	int	two; 
	int	i;
 
	i = -1;
	one = 1;
	two = 1; 

	while (readline[++i])
	{
		if (readline[i] == 39 && two > 0)
			one *= -1;
		else if (readline[i] == 34 && one > 0)
			two *= -1;
	}
	if (one < 0 || two < 0)
		return (1);
	return (0); 
}

char	*getenv_malloc(char *src)
{
	char	*env;
	char	*env_malloc;

	env = getenv(src);
	if (env)
	{
		env_malloc = ft_strdup(env);
		if (!env_malloc)
		{
			write(1, "malloc faild\n", 13);
			return (0);
		}
	}
	else
		env_malloc = ft_calloc(1, 1);
	return (env_malloc);
}

char	*ft_strmerge(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}

char	*format_env_var(char *var)
{
	char	**split;
	char	*new;
	char	*tmp;
	int		i;

	i = 0 + ft_strncmp(var, "$", 1) != 0;
	split = ft_split(var, '$');
	if (!split)
		return (0);
	if (i)
		new = ft_strdup(split[0]);
	else
		new = getenv_malloc(split[i++]);
	if (!new)
	{
		freetab(split);
		return (0);
	}
	while (split[i])
	{
		tmp = getenv_malloc(split[i++]);
		if (!tmp)
		{
			freetab(split);
			free(new);
			return (0);
		}
		new = ft_strmerge(new, tmp);
		if (!new)
		{
			freetab(split);
			return (0);
		}
	}
	freetab(split);
	return (new);
}

int	swap_env_var(char **lex) 
{
	int		i;
	char	*tmp;

	i = -1;
	while (lex[++i])
	{
		if (ft_strchr(lex[i], '$') != NULL)
		{
			tmp = format_env_var(lex[i]);
			if (!tmp)
				return (1);
			free(lex[i]);
			lex[i] = ft_strdup(tmp);
			free(tmp);
			if (!lex[i])
				return (1);
		}
	}
	return (0);
}
