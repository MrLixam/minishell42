/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:51:06 by marvin            #+#    #+#             */
/*   Updated: 2023/10/31 02:05:15 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env(t_local *local, char *find)
{
	int	i;

	i = -1;
	if (!ft_strchr(find, '='))
	{
		while (local->env[++i])
			if (!ft_strncmp(local->env[i], find, ft_strlen(find)
					- ft_strlen(ft_strchr(find, '='))))
				return (2);
		return (0);
	}
	while (local->env[++i])
	{
		if (!ft_strncmp(local->env[i], find, ft_strlen(find) \
					- ft_strlen(ft_strchr(find, '='))))
			return (1);
	}
	return (0);
}

int	new_env_len(char *add)
{
	if (!ft_strchr(add, '='))
		return (0);
	else
		return (ft_strlen(ft_strchr(add, '=')));
}

static int	update_env(t_local *local, char *add)
{
	char	**new_env;
	int		i;

	if (!add)
		return (1);
	new_env = ft_calloc(ft_tabstrlen(local->env) + 1, sizeof(char *));
	i = -1;
	while (new_env != NULL && local->env[++i])
	{
		if (!ft_strncmp(local->env[i], add, ft_strlen(add) - new_env_len(add)))
			new_env[i] = ft_strdup(add);
		else
			new_env[i] = ft_strdup(local->env[i]);
		if (new_env[i] == NULL)
		{
			freetab(new_env);
			break ;
		}
	}
	if (!new_env)
		return (1);
	freetab(local->env);
	local->env = new_env;
	return (0);
}

static int	add_env(t_local *local, char *add, int i)
{
	char	**new_env;

	if (!add)
		return (0);
	new_env = ft_calloc(ft_tabstrlen(local->env) + 2, sizeof(char *));
	while (new_env != NULL && local->env[++i])
	{
		new_env[i] = ft_strdup(local->env[i]);
		if (new_env[i] == NULL)
		{
			freetab(new_env);
			break ;
		}
	}
	if (!new_env)
		return (1);
	new_env[i] = ft_strdup(add);
	if (new_env[i] == NULL)
	{
		freetab(new_env);
		return (1);
	}
	freetab(local->env);
	local->env = new_env;
	return (0);
}

int	export_env(t_local *local, char *env)
{
	if (check_env(local, env) == 1)
	{
		if (update_env(local, env))
			return (1);
	}
	else if (check_env(local, env) == 0)
		if (add_env(local, env, -1))
			return (1);
	return (0);
}
