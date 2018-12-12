/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:45:31 by dmorgil           #+#    #+#             */
/*   Updated: 2018/11/22 19:03:27 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char u1;
	unsigned char u2;

	while (n--)
	{
		u1 = *(unsigned char *)str1;
		u2 = *(unsigned char *)str2;
		if (u1 != u2)
			return (u1 - u2);
		str1++;
		str2++;
	}
	return (0);
}
