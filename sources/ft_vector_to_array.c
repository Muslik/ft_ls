/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 07:59:22 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/12 20:00:13 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "ft_ls.h"

int		ft_vector_to_array(void **ft_vector)
{
	size_t	*arr;
	size_t	*tmp;
	size_t	n;

	arr = (size_t *)(*ft_vector);
	n = arr[2] * arr[0];
	if (!(tmp = (size_t *)malloc(n)))
		return (0);
	ft_memmove((void *)tmp, (void *)(arr + 3), n);
	ft_vector_free(ft_vector);
	*ft_vector = tmp;
	return (1);
}
