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

char	*ft_getenv(char *name)
{
	char	*ret_val;
	char	*tmp;
	int		i;

	tmp = ft_strjoin(name, "=");
	i = -1;
	ret_val = NULL;
	while (g_env[++i])
	{
		if (!ft_strncmp(tmp, g_env[i], ft_strlen(tmp)))
		{
			ret_val = ft_substr(g_env[i], ft_strlen(tmp), ft_strlen(g_env[i]));
			break ;
		}
	}
	free(tmp);
	return (ret_val);
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

	if (!arg)
		arg = ft_getenv("HOME");
	ret = chdir(arg);
	if (ret == -1)
	{
		err_mess = ft_strjoin("-minishell: cd: ", arg);
		perror(err_mess);
		free(err_mess);
		return (1);
	}
	return (0);
}
