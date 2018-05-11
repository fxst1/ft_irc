/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:20:18 by fjacquem          #+#    #+#             */
/*   Updated: 2018/05/09 23:41:30 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_end(t_list **l, t_list *new)
{
	t_list	*lst;

	if (*l)
	{
		lst = *l;
		while (lst->next)
		{
			lst = lst->next;
		}
		lst->next = new;
	}
	else
		*l = new;
}
