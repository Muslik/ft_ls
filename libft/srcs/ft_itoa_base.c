/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:50:17 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/10 16:10:53 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

static void		fill_str(size_t nbr, char *str, size_t base)
{
	char	s[16];

	s[0] = '0';
	s[1] = '1';
	s[2] = '2';
	s[3] = '3';
	s[4] = '4';
	s[5] = '5';
	s[6] = '6';
	s[7] = '7';
	s[8] = '8';
	s[9] = '9';
	s[10] = 'A';
	s[11] = 'B';
	s[12] = 'C';
	s[13] = 'D';
	s[14] = 'E';
	s[15] = 'F';
	if (nbr)
	{
		fill_str(nbr / base, (str - 1), base);
		*str = s[nbr % base];
	}
	return ;
}

static size_t	get_len(size_t nbr, size_t base)
{
	if (nbr)
		return (1 + get_len(nbr / base, base));
	return (0);
}

char			*ft_itoa_base(size_t n, size_t base, int is_signed)
{
	size_t	nbr;
	size_t	len;
	char	*str;

	nbr = (is_signed && n >> 63) ? (n * (-1)) : n;
	len = get_len(nbr, base);
	len += (nbr) ? 0 : 1;
	len += (is_signed && n >> 63) ? 1 : 0;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memset(str, '\0', len + 1);
	*str = (is_signed && n >> 63) ? '-' : '0';
	fill_str(nbr, str + len - 1, base);
	return (str);
}
