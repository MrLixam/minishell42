/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:11:44 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/18 16:11:25 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env;

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
		if (ft_strncmp(g_env[i], unset, ft_strlen(g_env[i]) - ft_strlen(ft_strchr(g_env[i], '='))))
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

int	create_env(char	**env, char **envp)
{
	int	i;

	env = ft_calloc(ft_tabstrlen(envp) + 1, sizeof(char *));
	if (env == NULL)
		return (1);
	i = -1;
	while (envp[++i])
	{
		env[i] = ft_strdup(envp[i]);
		if (env[i] == NULL)
		{
			freetab(env);
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

int	print_env(char **arg)
{
	int	i;

	i = -1;
	if (ft_tabstrlen(arg) > 1)
	{
		ft_putendl_fd("minishell: env: too many arguments", STDERR_FILENO);
		return (7);
	}
	while (g_env[++i])
		ft_putendl_fd(g_env[i], STDOUT_FILENO);
	return (0);
}
