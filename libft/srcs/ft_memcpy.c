/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:57:54 by dmorgil           #+#    #+#             */
/*   Updated: 2018/11/25 22:24:23 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*cdest;
	const char	*csrc;

	cdest = (char *)dst;
	csrc = (char *)src;
	if (src == dst)
		return (dst);
	while (n--)
		*cdest++ = *csrc++;
	return (dst);
}
