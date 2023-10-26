/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:11:44 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/26 17:10:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_env(t_local *local, char *unset)
{
	char	**new_env;
	int		i;
	int		j;
	char	*tmp;

	if (!unset)
		return (0);
	tmp = ft_getenv(local, unset);
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		return (0);
	}
	new_env = ft_calloc(ft_tabstrlen(local->env), sizeof(char *));
	if (!new_env)
		return (1);
	i = -1;
	j = -1;
	while (new_env != NULL && local->env[++i])
		if (ft_strncmp(local->env[i], unset, ft_strlen(local->env[i]) \
			- ft_strlen(ft_strchr(local->env[i], '='))))
			new_env[++j] = ft_strdup(local->env[i]);
	freetab(local->env);
	local->env = new_env;
	return (0);
}

int	create_env(t_local *local, char **envp)
{
	int	i;

	local->env = ft_calloc(ft_tabstrlen(envp) + 1, sizeof(char *));
	if (local->env == NULL)
		return (1);
	i = -1;
	while (envp[++i])
	{
		local->env[i] = ft_strdup(envp[i]);
		if (local->env[i] == NULL)
		{
			freetab(local->env);
			return (1);
		}
	}
	return (0);
}

char	*ft_getenv(t_local *local, char *name)
{
	char	*ret_val;
	char	*tmp;
	int		i;

	tmp = ft_strjoin(name, "=");
	i = -1;
	ret_val = NULL;
	if (!local->env)
		return (NULL);
	while (local->env[++i])
	{
		if (!ft_strncmp(tmp, local->env[i], ft_strlen(tmp)))
		{
			ret_val = ft_substr(local->env[i], ft_strlen(tmp), \
						ft_strlen(local->env[i]));
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

int	print_env(t_local *local, char **arg)
{
	int	i;

	i = -1;
	if (arg != NULL && ft_tabstrlen(arg) > 1)
	{
		ft_putendl_fd("minishell: env: too many arguments", STDERR_FILENO);
		return (7);
	}
	while (local->env[++i])
	{
		if (ft_strchr(local->env[i], '='))
			ft_putendl_fd(local->env[i], STDOUT_FILENO);
	}
	return (0);
}
