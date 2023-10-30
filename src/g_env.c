/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:11:44 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/30 18:17:35 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_env(t_local *local, char *unset)
{
	char	**new_env;
	int		ij[2];
	char	*tmp;

	if (!unset)
		return (0);
	tmp = ft_getenv(local, unset);
	if (!tmp)
		return (1);
	ij[0] = ft_strlen(tmp);
	free(tmp);
	new_env = ft_calloc(ft_tabstrlen(local->env), sizeof(char *));
	if (!new_env)
		return (1);
	ij[0] = -1;
	ij[1] = -1;
	while (new_env != NULL && local->env[++ij[0]])
		if (ft_strncmp(local->env[ij[0]], unset, ft_strlen(local->env[ij[0]])
				- ft_strlen(ft_strchr(local->env[ij[0]], '='))))
			new_env[++ij[1]] = ft_strdup(local->env[ij[0]]);
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

static char	*empty_env(char *ret_val)
{
	if (ret_val == NULL)
		ret_val = ft_calloc(1, 1);
	if (ft_strlen(ret_val) == 0)
	{
		free(ret_val);
		return (ft_strdup("\"\""));
	}
	ret_val = add_quote(ret_val, 1, 1, 0);
	return (ret_val);
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
	return (empty_env(ret_val));
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
