/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 22:09:06 by dmorgil           #+#    #+#             */
/*   Updated: 2018/11/24 22:28:34 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*next;

	if (!(*alst) || !alst || !del)
		return ;
	while (*alst)
	{
		next = (*alst)->next;
		(*del)((*alst)->content, (*alst)->content_size);
		ft_memdel((void **)alst);
		*alst = next;
	}
}
