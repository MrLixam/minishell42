/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 03:17:36 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/31 03:27:56 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*empty_env(char *ret_val)
{
	if (ret_val == NULL)
		ret_val = ft_calloc(1, 1);
	if (ft_strlen(ret_val) == 0)
	{
		free(ret_val);
		return (ft_strdup("\"\""));
	}
	return (ret_val);
}

char	*getenv_pars(t_local *local, char *name)
{
	char	*ret_val;	
	int		i;

	i = -1;
	ret_val = NULL;
	if (!local->env)
		return (NULL);
	while (local->env[++i])
	{
		if (!ft_strncmp(local->env[i], name,
				ft_strlen(local->env[i]) - new_env_len(local->env[i])))
		{
			ret_val = ft_substr(local->env[i], ft_strlen(name)
					+ (new_env_len(local->env[i]) != 0),
					ft_strlen(local->env[i]));
			if (ret_val == NULL)
				return (NULL);
			break ;
		}
	}
	return (empty_env(ret_val));
}
