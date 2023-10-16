/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:11:44 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/11 16:50:42 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	check_env(char **c_env, char *find)
{
	int	i;

	i = -1;
	while (c_env[++i])
	{
		if (ft_strncmp(c_env[i], find, ft_strlen(find) - ft_strlen(ft_strchr(find, '=') + 1)))
			return (1);
	}
	return (0);
}

static char	**update_env(char **c_env, char *add)
{
	char	**new_env;
	int		i;
	
	if (!add || !ft_strchr(add, '='))
		return (c_env);
	new_env = ft_calloc(ft_tabstrlen(c_env) + 1, 1);
	i = -1;
	while (new_env != NULL && c_env[++i])
	{
		if (!ft_strncmp(c_env[i], add, ft_strlen(add) - ft_strlen(ft_strchr(add, '=') + 1)))
			new_env[i] = ft_strdup(add);
		else
			new_env[i] = ft_strdup(c_env[i]);
		if (new_env == NULL)
		{
			freetab(c_env);
			freetab(new_env);
			return (NULL);
		}
	}
	freetab(c_env);
	return (new_env);
}

static char	**add_env(char **c_env, char *add)
{
	char	**new_env;
	int		i;

	if (!add || !ft_strchr(add, '='))
		return (c_env);
	new_env = ft_calloc(ft_tabstrlen(c_env) + 2, 1);
	if (new_env == NULL)
	{
		freetab(c_env);
		return (NULL);
	}
	i = -1;
	while (c_env[++i])
	{
		new_env[i] = ft_strdup(c_env[i]);
		if (new_env == NULL)
		{
			freetab(c_env);
			freetab(new_env);
			return (NULL);
		}
	}
	freetab(c_env);
	new_env[i] = ft_strdup(add);
	if (new_env == NULL)
	{
		freetab(new_env);
		return (NULL);
	}
	return (new_env);
}

char	**export_env(char **c_env, char *env)
{
	if (check_env (c_env, env))
		return (update_env(c_env, env));
	return (add_env(c_env, env));
}

char	**unset_env(char **c_env, char *unset)
{
	char	**new_env;
	int		i;
	
	if (!unset)
		return (c_env);
	new_env = ft_calloc(ft_tabstrlen(c_env), 1);
	i = -1;
	while (new_env != NULL && c_env[++i])
	{
		if (ft_strncmp(c_env[i], unset, ft_strlen(unset) - ft_strlen(ft_strchr(unset, '=') + 1)))
			new_env[i] = ft_strdup(c_env[i]);
		if (new_env == NULL)
		{
			freetab(c_env);
			freetab(new_env);
			return (NULL);
		}
	}
	freetab(c_env);
	return (new_env);
}

int	create_env(char **envp)
{
	int		i;
	
	g_env = ft_calloc(ft_tabstrlen(envp) + 1, 1);
	if (g_env == NULL)
		return (1);
	i = -1;
	while (envp[++i])
	{
		g_env[i] = ft_strdup(envp[i]);
		if (g_env[i] == NULL)
		{
			freetab(g_env);
			return (1);
		}
	}
	return (0);
}
