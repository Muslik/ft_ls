/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_pop_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:12:53 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/03 09:44:23 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

int		ft_vector_pop_back(void **ft_vector)
{
	size_t	*arr;
	size_t	*tmp;
	size_t	size;

	arr = (size_t *)(*ft_vector);
	if (arr[2] - 1 < ft_ceill(arr[1] / A / A) && arr[1] != ARR_SIZE
		&& arr[1] != ft_floorl(ARR_SIZE * A))
	{
		size = ft_ceill(arr[1] / A);
		if (!(tmp = (size_t *)malloc(sizeof(size_t) * 3 + size * arr[0])))
			return (0);
		ft_memmove((void *)tmp, (void *)arr, arr[0] * arr[2] +
				sizeof(size_t) * 3);
		tmp[1] = size;
		ft_vector_free(ft_vector);
		arr = tmp;
		*ft_vector = arr;
	}
	arr[2]--;
	return (1);
}
