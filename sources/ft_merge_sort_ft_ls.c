/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort_ft_ls.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 11:25:12 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/13 11:54:47 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

static void	merge_arrays(t_ft_merge_info_ft_ls info, size_t left,
		size_t middle, size_t right)
{
	size_t	i;
	size_t	j;
	size_t	tmp;

	i = left;
	j = middle + 1;
	tmp = 0;
	while (i <= middle && j <= right)
	{
		if (info.cmp((void *)(info.to_sort[i]), (void *)(info.to_sort[j])) < 0)
			info.buf[tmp++] = info.to_sort[i++];
		else
			info.buf[tmp++] = info.to_sort[j++];
	}
	while (i <= middle)
		info.buf[tmp++] = info.to_sort[i++];
	while (j <= right)
		info.buf[tmp++] = info.to_sort[j++];
	tmp = -1;
	while (++tmp < right - left + 1)
		info.to_sort[left + tmp] = info.buf[tmp];
}

static void	divide_and_rull(t_ft_merge_info_ft_ls info, size_t left, size_t right)
{
	size_t	middle;

	if (left < right)
	{
		middle = (left + right) / 2;
		divide_and_rull(info, left, middle);
		divide_and_rull(info, middle + 1, right);
		merge_arrays(info, left, middle, right);
	}
}

int			ft_merge_sort_ft_ls(size_t *to_sort, size_t left, size_t right, int (*cmp)(void *data1, void *data2))
{
	t_ft_merge_info_ft_ls info;

	if (!(info.buf = (size_t *)malloc(sizeof(size_t) * (right - left + 1))))
		return (0);
	info.to_sort = to_sort;
	info.cmp = cmp;
	divide_and_rull(info, left, right);
	free(info.buf);
	return (1);
}
