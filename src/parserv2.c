/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserv2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <gpouzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:28:26 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/11 16:53:05 by gpouzet          ###   ########.fr       */
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
	char	*tmp2;
	char	*tmp;
	int		i;

	i = 0 + ft_strncmp(var, "$", 1) != 0;
	split = env_sep(var);
	if (!split)
		return (0);
	if (i)
		new = ft_strdup(split[0]);
	else
	{
		tmp2 = ft_substr(split[i], 1, ft_strlen(split[i]) + 1);
		new = ft_getenv(tmp2);
		free (tmp2);
		i++;
	}
	if (!new)
	{
		freetab(split);
		return (0);
	}
	while (split[i])
	{
		if (!ft_strncmp(split[i], "$?", 2))
			ft_strlcat(new, "0", ft_strlen(new) + 2);
		else if (split[i][0] == '$')
		{
			tmp2 = ft_substr(split[i], 1, ft_strlen(split[i]) + 1);
			tmp = ft_getenv(tmp2);
			free (tmp2);
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
		else
			ft_strlcat(new, split[i], ft_strlen(new) + ft_strlen(split[i]) + 1);
		i++;
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
