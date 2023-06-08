/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:14:44 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 13:25:33 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H
# include "libft.h"

typedef struct s_stack
{
	int				top;
	unsigned int	capacity;
	int				*array;
}					t_stack;

t_stack		*stk_construct(unsigned int capacity);
int			stk_full(t_stack *stack);
int			stk_empty(t_stack *stack);
int			stk_peek(t_stack *stack);
int			stk_pop(t_stack *stack);
void		stk_push(t_stack *stack, int item);
void		stk_swap(t_stack *stack);
void		stk_rotate(t_stack *stack);
void		stk_rev_rota(t_stack *stack);
void		stk_delete(t_stack *stack);

#endif
