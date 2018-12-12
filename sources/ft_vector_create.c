/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:12:08 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/12 19:54:46 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "ft_ls.h"

void	*ft_vector_create(size_t elem_byte_size)
{
	size_t	*arr;

	if (!(arr = (size_t *)malloc(sizeof(size_t) * 3 +
					elem_byte_size * ARR_SIZE)))
		return (NULL);
	arr[0] = elem_byte_size;
	arr[1] = ARR_SIZE;
	arr[2] = 0;
	return ((void *)arr);
}
