/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:53:18 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/21 10:37:10 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* usage: ls [-] [file ...] */
#include "ft_ls.h"

void	find_term_col_ammount(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	g_term_col = w.ws_col;
}

int main(int argc, char **argv)
{
	int i;

	flags = 0;
	i = ft_get_flags(argc, argv);
	find_term_col_ammount();
	/* argc -= i; */
	/* argv += i; */
	while (i < argc)
	{
		char *s = ft_strdup(argv[i++]);
		ft_open_dirs(s);
	}
	return (0);
}
