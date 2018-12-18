/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:53:18 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/18 21:17:05 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* usage: ls [-] [file ...] */
#include "ft_ls.h"

/* int main(int argc, char *argv[]) */
/* { */
/* 	t_flags flags; */
/* 	char *str_tmp; */

/* 	ft_init_flags(&flags); */
/* 	if (argc == 1) */
/* 		str_tmp = ft_strdup("."); */
/* 	else */
/* 	{ */
/* 		str_tmp = ft_strdup(argv[argc - 1]); */
/* 		ft_get_flags(&flags, argc, argv); */
/* 	} */
/* 	printf("R: %d\n", flags.R); */
/* 	printf("l: %d\n", flags.l); */
/* 	printf("a: %d\n", flags.a); */
/* 	printf("r: %d\n", flags.r); */
/* 	printf("t: %d\n", flags.t); */
/* 	ft_open_dirs(str_tmp, &flags); */

/* 	return (0); */
/* } */

int main(int argc, char **argv)
{
	int i;
	int flags;

	flags = 0;
	i = ft_get_flags(argc, argv, &flags);
	/* argc -= i; */
	/* argv += i; */
	fflush(stdout);
	while (i < argc)
	{
		char *s = ft_strdup(argv[i++]);
		ft_open_dirs(s, &flags);
	}
	return (0);
}
