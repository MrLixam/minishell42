/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:46:33 by marvin            #+#    #+#             */
/*   Updated: 2023/10/27 03:05:10 by gpouzet          ###   ########.fr       */
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

static int	set_cd_env(t_local *local, char *oldpwd)
{
	char	*pwd;
	int		ret;

	ret = 0;
	if (!oldpwd)
		ret = 1;
	else
	{
		export_env(local, oldpwd);
		free(oldpwd);
	}
	pwd = ft_strmerge(ft_strdup("PWD="), getcwd(NULL, 0));
	if (!pwd)
		ret = 1;
	else
	{
		export_env(local, pwd);
		free(pwd);
	}
	return (ret);
}

int	ft_cd(t_local *local, char **arg)
{
	char	*oldpwd;
	char	*ag;

	if (ft_tabstrlen(arg) > 2)
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
	if (ft_tabstrlen(arg) > 2)
		return (1);
	if (ft_tabstrlen(arg) < 2)
		ag = ft_getenv(local, "HOME");
	else
		ag = ft_strdup(arg[1]);
	if (!ag)
		return (1);
	oldpwd = ft_strmerge(ft_strdup("OLDPWD="), getcwd(NULL, 0));
	if (chdir(ag))
	{
		perror_filename("minishell: cd: ", ag);
		free(ag);
		if (oldpwd)
			free(oldpwd);
		return (1);
	}
	free(ag);
	return (set_cd_env(local, oldpwd));
}

int	ft_unset(t_local *local, char **arg)
{
	int	i;

	i = 0;
	while (arg[++i])
		unset_env(local, arg[i]);
	return (0);
}
