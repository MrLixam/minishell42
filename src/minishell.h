/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:59:09 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/17 20:30:28 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../libft/printf.h"
# include "../libft/list.h"
# include "../libft/get_next_line.h"

typedef struct s_data
{
	char	*input;
	char	*output;
	char	*command;
	char	*option;
	t_list	**arg;
	struct s_data	*next;
}	t_data;
/*			prototype			*/
void	freetab(char **tab);
/*			data			*/
void	clear_data(t_data *data);
t_data	*new_data(void);
t_data	*parser(char **lexer);
#endif
