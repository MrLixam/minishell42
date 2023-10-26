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

char	*ft_strcut(char *str, char *set)
{
	if (!ft_strncmp(str, set, ft_strlen(set)))
		return (ft_substr(str, ft_strlen(set), ft_strlen(str)));
	return (ft_strdup(str));
}

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

int	is_builtin(char *command)
{
	return (!ft_strmcmp(command, "echo") || !ft_strmcmp(command, "cd")
		|| !ft_strmcmp(command, "pwd") || !ft_strmcmp(command, "export")
		|| !ft_strmcmp(command, "unset") || !ft_strmcmp(command, "env")
		|| !ft_strmcmp(command, "exit"));
}

int	redir_present(t_data *command)
{
	return (command->redir != NULL);
}

int	exec_builtin(t_local *local, char **str, t_data *line, int save[2])
{
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
		if (save)
			fix_fd(save);
		ft_exit(local, str);
		return (1);
	}
	return (-1);
}
