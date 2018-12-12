/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:01:48 by dmorgil           #+#    #+#             */
/*   Updated: 2018/11/21 14:24:07 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *elem;

	if (!(elem = (t_list *)ft_memalloc(sizeof(t_list))))
		return ((t_list *)0);
	if (!content || !content_size)
	{
		elem->content = (void *)0;
		elem->content_size = 0;
	}
	else
	{
		if (!(elem->content = ft_memalloc(content_size)))
		{
			free(elem);
			return ((t_list *)0);
		}
		elem->content_size = content_size;
		ft_memcpy(elem->content, content, content_size);
	}
	elem->next = (t_list *)0;
	return (elem);
}
