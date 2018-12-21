/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:53:18 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/21 15:19:53 by dmorgil          ###   ########.fr       */
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

static void	ft_print_dir_name(int i, int argc, char **argv)
{
	char	*s;
	int		j;

	if (i == argc)
	{
		s = ft_strdup(".");
		ft_open_dirs(s, s);
	}
	if (i == argc - 1)
	{
		s = ft_strdup(argv[i++]);
		ft_open_dirs(s, s);
	}
	j = i;
	while (i < argc)
	{
		if (j != i)
			ft_putchar('\n');
		s = ft_strdup(argv[i++]);
		ft_putstr(s);
		ft_putstr(":\n");
		ft_open_dirs(s, s);
	}
}

int main(int argc, char **argv)
{
	int		i;

	flags = 0;
	i = ft_get_flags(argc, argv);
	int j = -1;
	while (++j < 32)
	{
		printf("%d", (flags >> (31 - j)) & 1);
		fflush(stdout);
	}
	write(1, "\n", 1);
	find_term_col_ammount();
	ft_print_dir_name(i, argc, argv);
	/* argc -= i; */
	/* argv += i; */
	return (0);
}
