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

static int check_export(char *str)
{
	int i;

	i = 0;
	if (str[0] == '=' || ft_isdigit(str[0]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
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
	int err;

	i = 0;
	if (ft_tabstrlen(arg) == 1)
	{
		print_env(local, arg);
		return (0);
	}
	while (arg[++i])
	{
		err = 0;
		if (check_export(arg[i]) == 1)
			err = 1;
		else if (check_export(arg[i]) == 2)
			err = 0;
		else 
			err = export_env(local, arg[i]);
		if (err == 1)
		{
			ft_builtin_error("export", arg[i], "not a valid identifier");
			return (1);
		}
	}
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
