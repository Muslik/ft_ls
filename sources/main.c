/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:53:18 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/16 22:44:10 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* usage: ls [-] [file ...] */
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_ls.h"
#include "libft.h"
#include <errno.h>


void	ft_open_dirs(char *str, t_flags *flags);
void	ft_rec_dirs(size_t len, size_t **vector, char *str, t_flags *flags);

void	ft_init_flags(t_flags *to_fill)
{
	ft_memset(to_fill, 0, sizeof(t_flags));
}

void	print_files(size_t *vector, size_t len, t_flags *flags)
{
	size_t	i;

	i = -1;
	flags++;
	while (++i < len)
		printf("%s\n", (char *)(vector[i]));
}

void	ft_rec_dirs(size_t len, size_t **vector, char *str, t_flags *flags)
{
	size_t i;
	char *str_tmp;

	i = -1;
	ft_vector_to_array((void **)vector);
	print_files(*vector, len, flags);
	while (++i < len)
		if (ft_strncmp(".", (char *)((*vector)[i]), 1))
		{
			str_tmp = ft_strjoin(str, "/", 0);
			str_tmp = ft_strjoin(str_tmp, (char *)(*vector)[i], 1);
			ft_open_dirs(str_tmp, flags);
		}
	free(str);
	free(*vector);
}

void	ft_open_dirs(char *str, t_flags *flags)
{
	DIR *dir;
	size_t	a;
	size_t	*vector;
	struct dirent *pDirent;

	if(!(dir = opendir(str)))
	{
		free(str);
		return ;
	}
	vector = ft_vector_create(sizeof(size_t *));
	while ((pDirent = readdir(dir)) != NULL) {
		a = (size_t)pDirent->d_name;
		ft_vector_push_back((void **)&vector, &a);
	}
	ft_rec_dirs(ft_vector_get_len(vector), &vector, str, flags);
	closedir(dir);
}


int main(int argc, char *argv[])
{
	t_flags flags;
	char *str_tmp;

	ft_init_flags(&flags);
	if (argc == 1)
		str_tmp = ft_strdup(".");
	else
	{
		str_tmp = ft_strdup(argv[argc - 1]);
		ft_get_flags(&flags, argc, argv);
	}
	printf("R: %d\n", flags.R);
	printf("l: %d\n", flags.l);
	printf("a: %d\n", flags.a);
	printf("r: %d\n", flags.r);
	printf("t: %d\n", flags.t);
	ft_open_dirs(str_tmp, &flags);

	return (0);
}
