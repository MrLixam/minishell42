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

int	ft_strmcmp(char *s1, char *s2)
{
	int len[2];

	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	if (len[0] >= len[1])
		return (ft_strncmp(s1, s2, len[0]));
	else
		return (ft_strncmp(s1, s2, len[1]));
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("minishell: pwd:");
		return (1);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}

int	ft_cd(char **arg)
{
	int		ret;
	//char	*pwd;
	//char	*oldpwd;

	if (ft_tabstrlen(arg) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	arg++;
	if (!*arg)
		*arg = ft_getenv("HOME");
	//oldpwd = getcwd(NULL, 0);
	ret = chdir(*arg);
	if (ret == -1)
	{
		perror_filename("minishell: cd: ", *arg);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	export_env("OLDPWD", oldpwd, g_env);
	export_env("PWD", pwd, g_env);
	return (0);
}