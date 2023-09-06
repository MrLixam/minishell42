/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserv2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <gpouzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:28:26 by gpouzet           #+#    #+#             */
/*   Updated: 2023/09/06 17:16:34 by gpouzet          ###   ########.fr       */
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

char	*format_env_var(char *var)
{
	char	**split;
	char	*new;
	char	*tmp;
	int		i;

	i = 0;
	if (!ft_strncmp(var, "$", 1))
		i++;
	split = ft_split(var, '$');
	if (!split)
		return (0);
	if (i)
		new = ft_strdup(split[0]);
	else
		new = getenv(split[i++]);
	while (split[i])
	{
		tmp = getenv(split[i]);
		new = ft_realloc(new, ft_strlen(new) + ft_strlen(tmp));
		free (tmp);
		if (!new)
			return (0);
	}
	freetab(split);
	return (new);
}

int	swap_env_var(char **lex) 
{
	int		i;
	char	*tmp;

	i = 0;
	while (lex[i])
	{
		if (ft_strchr(lex[i], '$') != NULL)
		{
			tmp = format_env_var(lex[i]);
			if (!tmp)
				return (1);
			free(lex[i]);
			lex[i] = ft_strdup(tmp);
			if (!lex[i])
			{
				free(tmp);
				return (1);
			}
			free(tmp);
		}
	}
	return (0);
}
