/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:59:09 by lvincent          #+#    #+#             */
/*   Updated: 2023/09/15 16:27:24 by lvincent         ###   ########.fr       */
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
	char	*command;
	t_list	*redirection;
	t_list	*input;
	t_list	*output;
	t_list	*option;
	t_list	*arg;
	t_data	*next;
}	t_data;

/*			prototype		*/
void	freetab(char **tab);
/*			data			*/
t_data	*new_data(void);
int		data_len(t_data *line);
/*			parser			*/
int		swap_env_var(char **lex);
int		check_quote(char *readline);
char	**pre_parser(char *lexer);
char	**arg_sep(char const *s);
t_data	*parser(char **lexer);
#endif
