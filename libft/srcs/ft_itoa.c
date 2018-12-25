/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 21:36:40 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/25 21:14:55 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_itoaneg(long long int *n, long long int *is_neg)
{
	if (*n < 0)
	{
		*n *= -1;
		*is_neg = 1;
	}
}

char		*ft_itoa(long long int n)
{
	long long int	len;
	long long int	is_neg;
	long long int	ntmp;
	char	*str;

	len = 2;
	ntmp = n;
	is_neg = 0;
	ft_itoaneg(&n, &is_neg);
	while (ntmp /= 10)
		len++;
	len += is_neg;
	if ((str = (char *)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	ft_memset(str, 0, len);
	str[--len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	if (is_neg)
		str[0] = '-';
	return (str);
}
