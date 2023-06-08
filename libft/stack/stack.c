/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:15:58 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 13:18:55 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../stack.h"

t_stack	*stk_construct(unsigned int capacity)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (stack == NULL)
		return (NULL);
	stack->capacity = capacity;
	stack->top = -1;
	stack->array = ft_calloc(capacity, sizeof(int));
	if (stack->array == NULL)
	{
		free(stack);
		return (NULL);
	}
	return (stack);
}

int	stk_full(t_stack *stack)
{
	return (stack->top == (int)stack->capacity - 1);
}

int	stk_empty(t_stack *stack)
{
	return (stack->top == -1);
}

int	stk_peek(t_stack *stack)
{
	if (stk_empty(stack))
		return (-2147483648);
	return (stack->array[stack->top]);
}

int	stk_pop(t_stack *stack)
{
	if (stk_empty(stack))
		return (-2147483648);
	return (stack->array[stack->top--]);
}
