/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_get_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:25:06 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/12 09:31:15 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_vector_get_elem_n(void *ft_vector, size_t nbr)
{
	size_t	*arr;
	size_t	n;

	arr = (size_t *)ft_vector;
	n = (arr[2] > nbr) ? nbr : arr[2];
	arr = (size_t *)((char *)(arr + 3) + arr[0] * (n - 1));
	return ((void *)arr);
}

void	*ft_vector_get_last_elem(void *ft_vector)
{
	size_t	*arr;

	arr = (size_t *)ft_vector;
	arr = (size_t *)((char *)(arr + 3) + arr[0] * (arr[2] - 1));
	return ((void *)arr);
}

void	*ft_vector_get_first_elem(void *ft_vector)
{
	size_t	*arr;

	arr = (size_t *)ft_vector;
	return ((void *)(arr + 3));
}

size_t	ft_vector_get_len(void *ft_vector)
{
	size_t	*arr;

	arr = (size_t *)ft_vector;
	return (arr[2]);
}
