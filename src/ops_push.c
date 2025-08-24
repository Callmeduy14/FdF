/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:51:15 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 18:51:16 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	push(t_stack *to, t_stack *from)
{
	t_node	*n;

	n = stack_pop_top(from);
	if (!n)
		return ;
	stack_push_top(to, n);
}

void	op_pa(t_stack *a, t_stack *b)
{
	push(a, b);
	ps_puts("pa\n");
}

void	op_pb(t_stack *a, t_stack *b)
{
	push(b, a);
	ps_puts("pb\n");
}
