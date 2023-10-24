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
	return (!ft_strmcmp(command, "echo") || !ft_strmcmp(command, "cd")
		|| !ft_strmcmp(command, "pwd") || !ft_strmcmp(command, "export")
		|| !ft_strmcmp(command, "unset") || !ft_strmcmp(command, "env")
		|| !ft_strmcmp(command, "exit"));
}

int	redir_present(t_data *command)
{
	return (command->output != NULL || command->input != NULL);
}

int	exec_builtin(t_local *local, char **str, t_data *line)
{
	int	len;

	len = ft_strlen(line->command);
	if (!ft_strmcmp(line->command, "echo"))
		return (ft_echo(line->arg));
	else if (!ft_strmcmp(line->command, "cd"))
		return (ft_cd(local, str));
	else if (!ft_strmcmp(line->command, "pwd"))
		return (ft_pwd());
	else if (!ft_strmcmp(line->command, "export"))
		return (ft_export(local, str));
	else if (!ft_strmcmp(line->command, "unset"))
		return (ft_unset(local, str));
	else if (!ft_strmcmp(line->command, "env"))
		return (print_env(local, str));
	else if (!ft_strmcmp(line->command, "exit"))
	{
		freetab(str);
		ft_exit(local);
	}
	return (-1);
}
