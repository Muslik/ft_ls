/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:05:30 by dmorgil           #+#    #+#             */
/*   Updated: 2018/11/22 19:01:45 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = dest;
	while (*tmp)
		tmp++;
	while (src[i] && n--)
		*tmp++ = src[i++];
	*tmp = '\0';
	return (dest);
}
