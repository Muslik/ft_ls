/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 19:07:35 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/13 08:31:00 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2, int free_opt)
{
	char	*newstr;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	newstr = ft_strnew(len1 + len2);
	if (!newstr)
		return (NULL);
	ft_memmove(newstr, s1, len1);
	ft_memmove(newstr + len1, s2, len2 + 1);
	if (free_opt == 1)
		free((char *)s1);
	if (free_opt == 2)
		free((char *)s2);
	if (free_opt == 3)
	{
		free((char *)s1);
		free((char *)s2);
	}
	return (newstr);

