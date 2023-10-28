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

int	ft_duptab(char ***new, char **old)
{
	int	i;

	i = -1;
	*new = ft_calloc(ft_tabstrlen(old) + 1, sizeof(char *));
	while (old[++i])
	{
		(*new)[i] = ft_strdup(old[i]);
		if ((*new)[i] == NULL)
		{
			freetab(*new);
			return (1);
		}
	}
	return (0);
}

static char	**ft_sort_tab(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[j])
		{
			if (ft_strmcmp(tab[i], tab[j]) < 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (tab);
}

static int	print_export(t_local *local)
{
	int		i;
	char	**sorted;

	i = -1;
	if (ft_duptab(&sorted, local->env))
		return (1);
	sorted = ft_sort_tab(sorted);
	while (sorted[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr(sorted[i], '='))
		{
			write(1, sorted[i], ft_strchr(sorted[i], '=') - sorted[i] + 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(ft_strchr(sorted[i], '=') + 1, 1);
			ft_putchar_fd('"', 1);
		}
		else
			ft_putstr_fd(sorted[i], 1);
		ft_putchar_fd('\n', 1);
	}
	freetab(sorted);
	return (0);
}

static int	check_export(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=' || ft_isdigit(str[0]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
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
		if (check_export(arg[i]) == 1)
			err = 1;
		else
			err = export_env(local, arg[i]);
		if (err == 1)
			ft_builtin_error("export", arg[i], "not a valid identifier");
	}
	return (err);
}
