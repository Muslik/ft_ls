/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_get_first_n_elements.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 11:02:38 by narchiba          #+#    #+#             */
/*   Updated: 2018/11/29 08:36:53 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	*ft_vector_get_first_n_elements(void *ft_vector, size_t elem_count)
{
	size_t	*arr;
	size_t	*tmp;
	size_t	n;

	arr = (size_t *)ft_vector;
	n = (arr[2] > elem_count ? elem_count : arr[2]) * arr[0];
	if (!(tmp = (size_t *)malloc(n)))
		return (NULL);
	ft_memmove((void *)tmp, (void *)(arr + 3), n);
	return ((void *)tmp);
}
