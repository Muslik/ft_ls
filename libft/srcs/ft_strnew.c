/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:07:21 by dmorgil           #+#    #+#             */
/*   Updated: 2018/11/29 13:29:35 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	if (!(++size))
		return (0);
	str = ft_memalloc(size);
	if (str == NULL)
		return (NULL);
	str = ft_memset(str, '\0', size);
	return (str);
}
