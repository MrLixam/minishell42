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

int	ft_cd(char *arg, char **envp)
{
	int		ret;
	char	*err_mess;
	char	*pwd;
	char	*oldpwd;

	if (!arg)
		arg = ft_getenv("HOME");
	oldpwd = getcwd(NULL, 0);
	ret = chdir(arg);
	if (ret == -1)
	{
		err_mess = ft_strjoin("-minishell: cd: ", arg);
		perror(err_mess);
		free(err_mess);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	ft_setenv("OLDPWD", oldpwd, envp);
	ft_setenv("PWD", pwd, envp);
	return (0);
}
