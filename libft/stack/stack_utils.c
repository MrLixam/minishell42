/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:23:07 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 12:27:50 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../stack.h"

void	stk_delete(t_stack *stack)
{
	free(stack->array);
	free(stack);
}

void	stk_push(t_stack *stack, int item)
{
	if (stk_full(stack))
		return ;
	stack->array[++stack->top] = item;
}

void	stk_swap(t_stack *stack)
{
	int	tmp1;
	int	tmp2;

	if (stack->top > 0)
	{
		tmp1 = stk_pop(stack);
		tmp2 = stk_pop(stack);
		stk_push(stack, tmp1);
		stk_push(stack, tmp2);
	}
}

void	stk_rotate(t_stack *stack)
{
	int		tmp;
	t_stack	*stacktmp;

	if (stack->top > 0)
	{
		stacktmp = stk_construct(stack->capacity);
		if (stacktmp == NULL)
			return ;
		tmp = stk_pop(stack);
		while (stack->top > -1)
			stk_push(stacktmp, stk_pop(stack));
		stk_push(stack, tmp);
		while (!stk_empty(stacktmp))
			stk_push(stack, stk_pop(stacktmp));
		stk_delete(stacktmp);
	}
}

void	stk_rev_rota(t_stack *stack)
{
	int		tmp;
	t_stack	*stacktmp;

	if (stack->top > 0)
	{
		stacktmp = stk_construct(stack->capacity);
		if (stacktmp == NULL)
			return ;
		while (stack->top > -1)
			stk_push(stacktmp, stk_pop(stack));
		tmp = stk_pop(stacktmp);
		while (!stk_empty(stacktmp))
			stk_push(stack, stk_pop(stacktmp));
		stk_push(stack, tmp);
		stk_delete(stacktmp);
	}
}
