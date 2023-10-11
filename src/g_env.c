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

int	check_env(char **c_env, char *find)
{
	int	i;

	i = -1;
	while (c_env[++i])
	{
		if (ft_strncmp(c_env, find, ft_strlen(find) - ft_strlen(ft_strchr(find, '=') + 1)))
			return (1);
	}
	return (0);
}

char	**update_env(char **c_env, char *add)
{
	char	**new_env;
	int		i;
	
	if (!add || !ft_strchr(add, '='))
		return (c_env);
	new_env = ft_calloc(ft_tabstrlen(c_env) + 1, 1);
	i = -1;
	while (new_env != NULL && c_env[++i])
	{
		if (!ft_strncmp(c_env, add, ft_strlen(add) - ft_strlen(ft_strchr(add, '=') + 1)))
			new_env[i] = ft_substr(add);
		else
			new_env[i] = ft_substr(c_env[i]);
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
		if (ft_strncmp(c_env, unset, ft_strlen(unset) - ft_strlen(ft_strchr(unset, '=') + 1)))
			new_env[i] = ft_substr(c_env[i]);
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

char	**add_env(char **c_env, char *add)
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
		new_env[i] = ft_substr(c_env[i]);
		if (new_env == NULL)
		{
			freetab(c_env);
			freetab(new_env);
			return (NULL);
		}
	}
	freetab(c_env);
	new_env[i] = ft_substr(add);
	if (new_env == NULL)
	{
		freetab(new_env);
		return (NULL);
	}
	return (new_env);
}
