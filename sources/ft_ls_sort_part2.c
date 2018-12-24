/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_part2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 16:13:01 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/24 16:13:26 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_alpha(void *data1, void *data2)
{
	return (ft_strcmp(((t_file_info *)data1)->name, ((t_file_info *)data2)->name));
}

int		rev_cmp_alpha(void *data1, void *data2)
{
	return (ft_strcmp(((t_file_info *)data2)->name, ((t_file_info *)data1)->name));
}
