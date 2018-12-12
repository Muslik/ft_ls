/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 19:07:35 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/12 22:44:09 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2, int free_opt)
{
	char	*newstr;

	if (!s1 || !s2)
		return (NULL);
	newstr = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (!newstr)
		return (NULL);
	ft_memmove(newstr, s1, ft_strlen(s1));
	ft_memmove(newstr + ft_strlen(s1), s2, ft_strlen(s2) + 1);
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
}
