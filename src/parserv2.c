/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserv2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:28:26 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/26 16:53:32 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	elem_exit(t_local *local, char **new)
{
	char	*tmp;

	tmp = ft_itoa(local->exit_code);
	if (!tmp)
		return (1);
	*new = ft_strmerge(*new, tmp);
	if (!*new)
		return (1);
	return (0);
}

static int	elem_add(t_local *local, char **split, char **new, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_substr(split[i], 1, ft_strlen(split[i]) + 1);
	tmp = ft_getenv(local, tmp2);
	free (tmp2);
	if (!tmp)
	{
		freetab(split);
		free(new);
		return (1);
	}
	*new = ft_strmerge(*new, tmp);
	if (!*new)
	{
		freetab(split);
		return (1);
	}
	return (0);
}

static char	*elem_first(t_local *local, char **split, int *i)
{
	char	*tmp;
	char	*new;

	if (*i)
	{
		new = ft_strdup(split[0]);
		*i -= 1;
	}
	else if (!ft_strncmp(split[*i], "$", 2))
		new = ft_strdup("$");
	else if (!ft_strncmp(split[*i], "$?", 2))
		new = ft_itoa(local->exit_code);
	else
	{
		tmp = ft_substr(split[*i], 1, ft_strlen(split[*i]) + 1);
		new = ft_getenv(local, tmp);
		free(tmp);
	}
	if (!new)
	{
		freetab(split);
		return (NULL);
	}
	return (new);
}

static char	*format_env_var(t_local *local, char *var, int i)
{
	char	**split;
	char	*new;

	i = 0 + (ft_strncmp(var, "$", 1) != 0);
	split = env_sep(var);
	if (!split)
		return (NULL);
	new = elem_first(local, split, &i);
	while (split[++i])
	{
		if (!new)
			return (NULL);
		if (!ft_strncmp(split[i], "$?", 2))
			if (elem_exit(local, &new))
				return (NULL);
		if (ft_strncmp(split[i], "$?", 2) && split[i][0] == '$'
				&& ft_strncmp(split[i], "$", 2))
			if (elem_add(local, split, &new, i))
				return (NULL);
		if (ft_strncmp(split[i], "$?", 2) && (split[i][0] != '$'
			|| !ft_strncmp(split[i], "$", 2)))
			new = ft_strmerge(new, ft_strdup(split[i]));
	}
	freetab(split);
	return (new);
}

int	swap_env_var(t_local *local, char **lex)
{
	int		i;
	char	*tmp;

	i = -1;
	while (lex[++i])
	{
		if (ft_strchr(lex[i], '$') != NULL)
		{
			tmp = format_env_var(local, lex[i], 0);
			if (!tmp)
				return (1);
			free(lex[i]);
			lex[i] = ft_strdup(tmp);
			free(tmp);
			if (!lex[i])
			{
				freetab(lex);
				return (1);
			}
		}
	}
	return (0);
}
