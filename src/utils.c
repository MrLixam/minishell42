/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:10:42 by marvin            #+#    #+#             */
/*   Updated: 2023/10/17 12:10:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_to_str(t_list *lst, char *command)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_calloc(ft_lstsize(lst) + 2, sizeof(char *));
	str[0] = ft_strdup(command);
	i++;
	while (lst)
	{
		str[i] = ft_strdup(lst->content);
		lst = lst->next;
		i++;
	}
	return (str);
}

int	file_access(char *path)
{
	return (access(path, F_OK & R_OK & W_OK & X_OK));
}

int	is_builtin(char *command)
{
	int	l;

	l = ft_strlen(command);
	return (!ft_strncmp(command, "echo", l) || !ft_strncmp(command, "cd", l)
		|| !ft_strncmp(command, "pwd", l) || !ft_strncmp(command, "export", l)
		|| !ft_strncmp(command, "unset", l) || !ft_strncmp(command, "env", l)
		|| !ft_strncmp(command, "exit", l));
}

int	redir_present(t_data *command)
{
	return (command->output != NULL || command->input != NULL);
}

int	exec_builtin(t_local *local, char **str, t_data *line)
{
	int	len;

	len = ft_strlen(line->command);
	if (!ft_strncmp(line->command, "echo", len))
		return (ft_echo(line->arg));
	else if (!ft_strncmp(line->command, "cd", len))
		return (ft_cd(local, str));
	else if (!ft_strncmp(line->command, "pwd", len))
		return (ft_pwd());
	else if (!ft_strncmp(line->command, "export", len))
		return (ft_export(local, str));
	else if (!ft_strncmp(line->command, "unset", len))
		return (ft_unset(local, str));
	else if (!ft_strncmp(line->command, "env", len))
		return (print_env(local, str));
	else if (!ft_strncmp(line->command, "exit", len))
		ft_exit(line);
	return (-1);
}
