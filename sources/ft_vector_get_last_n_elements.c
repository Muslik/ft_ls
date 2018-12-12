/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_get_last_n_elements.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 11:04:46 by narchiba          #+#    #+#             */
/*   Updated: 2018/11/29 08:37:25 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	*ft_vector_get_last_n_elements(void *ft_vector, size_t elem_count)
{
	size_t	*arr;
	size_t	*tmp;
	size_t	n;

	arr = (size_t *)ft_vector;
	n = (arr[2] > elem_count ? elem_count : arr[2]) * arr[0];
	arr = (size_t*)((char *)(arr + 3) + arr[2] * arr[0] - n);
	if (!(tmp = (size_t *)malloc(n)))
		return (NULL);
	ft_memmove((void *)tmp, (void *)arr, n);
	return ((void *)tmp);
}
