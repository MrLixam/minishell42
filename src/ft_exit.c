/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:58:14 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/27 00:34:40 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_numeric(t_list *arg)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strdup(arg->content);
	if (tmp[0] == '-' || tmp[0] == '+')
		i++;
	while (tmp[++i])
	{
		if (!ft_isdigit(tmp[i]))
			return (ft_strmerge(tmp, ft_strdup(": numeric argument required")));
	}
	free(tmp);
	return (NULL);
}

void	ft_exit_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putendl_fd(str, 2);
	free(str);
}

void	ft_exit(t_local *local, t_data *curr, char **tab)
{
	int		exit_code;
	char	*str;

	exit_code = 0;
	if (curr->arg)
	{
		str = check_numeric(curr->arg);
		if (str != NULL)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putendl_fd(str, 2);
			freetab(tab);
			exit(clear_local(local, 2));
		}
		if (ft_lstsize(curr->arg) > 1)
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return ;
		}
		exit_code = ft_atoi(curr->arg->content);
		if (exit_code < 0)
			exit_code = 256 + exit_code;
	}
	freetab(tab);
	exit(clear_local(local, exit_code));
}
