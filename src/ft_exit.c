/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:58:14 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/27 09:03:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atol(char *str, int *err)
{
	int			i;
	int			sign;
	long long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	*err = 0;
	if (!ft_strmcmp(str, "-9223372036854775808"))
		return (LLONG_MIN);
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb > (LLONG_MAX - (str[i] - '0')) / 10)
			*err = 1;
		nb = nb * 10 + (str[i++] - 48);
	}
	if (str[i] != '\0')
		*err = 1;
	return (nb * sign);
}

static int	check_numeric(t_list *arg)
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
			return (1);
	}
	free(tmp);
	return (0);
}

void	ft_exit_error(void)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putendl_fd("numeric argument required", 2);
}

void	ft_exit(t_local *local, t_data *curr, char **tab)
{
	long long	exit_code;
	int			err2;

	exit_code = 0;
	if (curr->arg)
	{
		exit_code = ft_atol(curr->arg->content, &err2);
		if ((check_numeric(curr->arg) || err2))
		{
			ft_exit_error();
			freetab(tab);
			exit(clear_local(local, 2));
		}
		if (ft_lstsize(curr->arg) > 1)
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return ;
		}
		exit_code = exit_code % 256;
	}
	freetab(tab);
	if (data_len(local->data) == 1)
		ft_putendl_fd("exit", 2);
	exit(clear_local(local, exit_code));
}
