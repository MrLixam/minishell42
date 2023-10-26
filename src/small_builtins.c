/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:46:33 by marvin            #+#    #+#             */
/*   Updated: 2023/09/27 21:46:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("minishell: pwd:");
		return (errno);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}

int	ft_cd(t_local *local, char **arg)
{
	int		ret;
	char	*pwd;
	char	*oldpwd;

	if (ft_tabstrlen(arg) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	arg++;
	if (!*arg)
		*arg = ft_getenv(local, "HOME");
	oldpwd = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	ret = chdir(*arg);
	if (ret == -1)
	{
		perror_filename("minishell: cd: ", *arg);
		return (1);
	}
	pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	export_env(local, oldpwd);
	export_env(local, pwd);
	free(oldpwd);
	free(pwd);
	return (0);
}

int	ft_unset(t_local *local, char **arg)
{
	int	i;

	i = 0;
	while (arg[++i])
		unset_env(local, arg[i]);
	return (0);
}
