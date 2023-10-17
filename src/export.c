/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:51:06 by marvin            #+#    #+#             */
/*   Updated: 2023/10/17 13:33:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_env(char *find)
{
	int	i;

	i = -1;
	while (g_env[++i])
	{
		if (!ft_strncmp(g_env[i], find, ft_strlen(find) - ft_strlen(ft_strchr(find, '=') + 1)))
			return (1);
	}
	return (0);
}

static int	update_env(char *add)
{
	char	**new_env;
	int		i;

	if (!add || !ft_strchr(add, '='))
		return (1);
	new_env = ft_calloc(ft_tabstrlen(g_env) + 1, sizeof(char *));
	i = -1;
	while (new_env != NULL && g_env[++i])
	{
		if (!ft_strncmp(g_env[i], add, ft_strlen(add) - ft_strlen(ft_strchr(add, '=') + 1)))
			new_env[i] = ft_strdup(add);
		else
			new_env[i] = ft_strdup(g_env[i]);
		if (new_env == NULL)
		{
			freetab(g_env);
			freetab(new_env);
			return (1);
		}
	}
	freetab(g_env);
	g_env = new_env;
	return (0);
}

static int	add_env(char *add)
{
	char	**new_env;
	int		i;

	if (!add || !ft_strchr(add, '='))
		return (0);
	new_env = ft_calloc(ft_tabstrlen(g_env) + 2, sizeof(char *));
	if (new_env == NULL)
	{
		freetab(g_env);
		return (1);
	}
	i = -1;
	while (g_env[++i])
	{
		new_env[i] = ft_strdup(g_env[i]);
		if (new_env == NULL)
		{
			freetab(g_env);
			freetab(new_env);
			return (1);
		}
	}
	freetab(g_env);
	new_env[i] = ft_strdup(add);
	if (new_env == NULL)
	{
		freetab(new_env);
		return (1);
	}
	g_env = new_env;
	return (0);
}

int	export_env(char *env)
{
	if (check_env(env))
		if (update_env(env))
			return (1);
	if (add_env(env))
		return (1);
	return (0);
}
