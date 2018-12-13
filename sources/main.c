/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:53:18 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/13 09:15:32 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* usage: ls [-] [file ...] */
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_ls.h"
#include "libft/includes/libft.h"

void	ft_rec_dirs(size_t len, size_t **vector, char *str);
void	ft_open_dirs(char *str);

void	ft_init_flags(t_flags *to_fill)
{
	ft_memset(to_fill, 0, sizeof(t_flags));
}

void	ft_rec_dirs(size_t len, size_t **vector, char *str)
{
	size_t i;
	char *str_tmp;

	i = -1;
	ft_vector_to_array((void **)vector);
	while (++i < len)
		if (ft_strcmp(".", (char *)(*vector)[i]) && ft_strcmp("..", (char *)(*vector)[i]))
		{
			str_tmp = ft_strjoin(str, "/", 0);
			str_tmp = ft_strjoin(str_tmp, (char *)(*vector)[i], 1);
			ft_open_dirs(str_tmp);
		}
	free(str);
	free(*vector);
}

void	ft_open_dirs(char *str)
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
		if (ft_strcmp(pDirent->d_name, ".") == 0)
			printf("\n%s:\n", str);
		else
		{
			if (ft_strcmp(pDirent->d_name, ".."))
				printf("%s\n", pDirent->d_name);
		}
		a = (size_t)pDirent->d_name;
		ft_vector_push_back((void **)&vector, &a);
	}
	ft_rec_dirs(ft_vector_get_len(vector), &vector, str);
	closedir(dir);
}

int main(int argc, char *argv[])
{
	t_flags flags;
	char *str_tmp;

	str_tmp = ft_strdup(argv[argc - 1]);
	ft_init_flags(&flags);
	ft_open_dirs(str_tmp);

	return (0);
}
		/* if (ft_strcmp(".", pDirent->d_name) && ft_strcmp("..", pDirent->d_name)) */
		/* 	ft_open_dirs(pDirent->d_name); */
