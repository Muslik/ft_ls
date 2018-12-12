/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_is_empty.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:12:40 by narchiba          #+#    #+#             */
/*   Updated: 2018/11/29 08:35:35 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int		ft_vector_is_empty(void *ft_vector)
{
	size_t	*arr;

	arr = (size_t *)ft_vector;
	if (arr[2] == 0)
		return (1);
	return (0);
}
