/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_push_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:13:07 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/12 20:04:17 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "ft_ls.h"

int		ft_vector_push_back(void **ft_vector, const void *data)
{
	size_t	*arr;
	size_t	*tmp;
	size_t	n;

	arr = (size_t *)(*ft_vector);
	if (arr[1] == arr[2])
	{
		if (!(tmp = (size_t *)malloc(sizeof(size_t) * 3 +
						arr[0] * ft_floorl(arr[1] * A))))
			return (0);
		ft_memmove((void *)tmp, (void *)arr, arr[0] * arr[2] +
				sizeof(size_t) * 3);
		tmp[1] = ft_floorl(tmp[1] * A);
		ft_vector_free(ft_vector);
		arr = tmp;
		*ft_vector = arr;
	}
	arr[2]++;
	n = arr[0];
	arr = (size_t *)((char *)(arr + 3) + arr[0] * (arr[2] - 1));
	ft_memmove((void *)arr, data, n);
	return (1);
}
