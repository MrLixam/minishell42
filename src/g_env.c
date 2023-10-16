/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:11:44 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/16 20:51:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_env(char *unset)
{
	char	**new_env;
	int		i;
	
	if (!unset)
		return (0);
	new_env = ft_calloc(ft_tabstrlen(g_env), sizeof(char *));
	i = -1;
	while (new_env != NULL && g_env[++i])
	{
		if (ft_strncmp(g_env[i], unset, ft_strlen(unset) - ft_strlen(ft_strchr(unset, '=') + 1)))
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

int	create_env(char **envp)
{
	int		i;
	
	g_env = ft_calloc(ft_tabstrlen(envp) + 1, sizeof(char *));
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

char	*ft_getenv(char *name)
{
	char	*ret_val;
	char	*tmp;
	int		i;
	

	tmp = ft_strjoin(name, "=");
	i = -1;
	ret_val = NULL;
	if (!g_env)
		return (NULL);
	while (g_env[++i])
	{
		if (!ft_strncmp(tmp, g_env[i], ft_strlen(tmp)))
		{
			ret_val = ft_substr(g_env[i], ft_strlen(tmp), ft_strlen(g_env[i]));
			if (ret_val == NULL)
				return (NULL);
			break ;
		}
	}
	free(tmp);
	if (ret_val == NULL)
		ret_val = ft_calloc(1, 1);
	return (ret_val);
}
