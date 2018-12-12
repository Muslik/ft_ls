/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 19:15:41 by dmorgil           #+#    #+#             */
/*   Updated: 2018/11/23 20:31:01 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && i != j)
		i++;
	while ((s[j] == ' ' || s[j] == '\t' || s[j] == '\n') && j != i)
		j--;
	if (i == j)
		return (ft_strnew(0));
	newstr = ft_strsub(s, i, (j - i + 1));
	if (!newstr)
		return (NULL);
	return (newstr);
}
