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
#include <errno.h>

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd: error retrieving directory");
		return (1);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}

int ft_cd(char *arg, char **envp)
{
	int ret;
	char *err_mess;

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

int main(int argc, char **argv)
{
	ft_cd(argv[1]);
	ft_pwd();
	return (0);
}