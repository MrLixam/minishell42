/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:47:50 by marvin            #+#    #+#             */
/*   Updated: 2023/10/26 16:47:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_export(t_local *local)
{
	int	i;
	int	j;

	i = -1;
	while (local->env[++i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (local->env[i][j] != '='
			&& (ft_isalnum(local->env[i][j]) || local->env[i][j] == '_'))
			ft_putchar_fd(local->env[i][j++], 1);
		if (local->env[i][j] == '=')
		{
			ft_putchar_fd(local->env[i][j++], 1);
			ft_putchar_fd('"', 1);
			while (local->env[i][j])
				ft_putchar_fd(local->env[i][j++], 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
	}
	return (0);
}

static int check_export(char *str)
{
	int i;

	i = 0;
	if (str[0] == '=' || ft_isdigit(str[0]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] == '=')
		return (0);
	return (2);
}

int	ft_export(t_local *local, char **arg)
{
	int	i;
	int	err;

	i = 0;
	if (!arg[1])
		return (print_export(local));
	while (arg[++i])
	{
		err = 0;
		if (check_export(arg[i]) == 2)
			err = 0;
		if (check_export(arg[i]) == 1)
			err = 1;
		else
			err = export_env(local, arg[i]);
		if (err == 1)
			ft_builtin_error("export", arg[i], "not a valid identifier");
	}
	return (err);
}
