/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:26:16 by dmorgil           #+#    #+#             */
/*   Updated: 2018/11/29 11:04:50 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	unsigned char tmp;

	if (!fd)
		return ;
	tmp = (unsigned char)c;
	if (tmp <= 127)
		write(fd, &tmp, 1);
	else
	{
		tmp = 192 + ((unsigned char)c / 64);
		write(fd, &tmp, 1);
		tmp = 128 + ((unsigned char)c % 64);
		write(fd, &tmp, 1);
	}
}
