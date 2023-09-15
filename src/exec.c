/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:55 by lvincent          #+#    #+#             */
/*   Updated: 2023/09/09 14:50:22 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_bin(char *bin, char **args, char **envp)
{
	execve(bin, args, envp);
	exit(0);
}

int	file_access(char *path)
{
	return (access(path, F_OK & R_OK & W_OK & X_OK));
}

int pipe_exec(t_data *line)
{
	int pipes[2];
	int saves[2];
	pipes = pipe
}
