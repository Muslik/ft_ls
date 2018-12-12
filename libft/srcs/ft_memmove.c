/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 11:55:19 by dmorgil           #+#    #+#             */
/*   Updated: 2018/11/28 02:35:02 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	char		*cdest;
	const char	*csrc;

	cdest = (char *)destination;
	csrc = (const char*)source;
	if (destination == source)
		return (destination);
	if (cdest > csrc)
	{
		while (n)
		{
			cdest[n - 1] = csrc[n - 1];
			n--;
		}
	}
	while (n)
	{
		*cdest++ = *csrc++;
		n--;
	}
	return (destination);
}
