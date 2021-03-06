/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 21:22:27 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/01 21:22:29 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

/*
**	ft_gc
**
**	return garbage collector adresse
*/

t_mem	**ft_gc(void)
{
	static t_mem	*gc = NULL;

	return (&gc);
}
