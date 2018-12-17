/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 13:39:24 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/14 14:16:54 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_get_flags(t_flags *flags, int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
	{
		ft_add_flags(flags, argv[i]);
		i++;
	}
	return (i);
}

void	ft_add_flags(t_flags *flags, char *str)
{
	int i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 'l')
			flags->l = 1;
		else if (str[i] == 'R')
			flags->R = 1;
		else if (str[i] == 'a')
			flags->a = 1;
		else if (str[i] == 'r')
			flags->r = 1;
		else if (str[i] == 't')
			flags->t = 1;
		else
			ft_handle_errors(&str[i]);
		i++;
	}
}

void	ft_handle_errors(char *str)
{
	ft_putstr("./ft_ls: illegal option -- ");
	ft_putchar(*str);
	ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
	exit(0);
}
