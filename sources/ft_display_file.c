/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:31:17 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/18 21:45:41 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_files(size_t *vector, size_t len, int *flags)
{
	// CHOOSE OPTION OF PRINT
	size_t	i;
	t_file_info *tmp;

	(void)flags;
	/* (void)vector; */
	/* (void)tmp; */
	i = -1;
	while (++i < len)
	{
		tmp = (t_file_info *)vector[i];
		printf("%s\n", tmp->name);
	}
}

void	ft_rec_dirs(size_t len, size_t **vector, char *str, int *flags)
{
	size_t i;
	char *str_tmp;
	t_file_info *tmp;

	i = -1;
	ft_vector_to_array((void **)vector);
	//Choose sort и отсортить
	print_files(*vector, len, flags);
	while (++i < len)
	{
		tmp = (t_file_info *)(*vector)[i];
		if (ft_strncmp(".", tmp->name, 1))
		{
			str_tmp = ft_strjoin(str, "/", 0);
			str_tmp = ft_strjoin(str_tmp, tmp->name, 1);
			ft_open_dirs(str_tmp, flags);
		}
	}
	free(str);
	free(*vector);
}

static	t_file_info *ft_add_file(//char path[PATH_MAX],
		char *name)
{
struct stat *stat;
	t_file_info *file;

if (!(stat = (struct stat *)malloc(sizeof(struct stat))))
		exit(0);
	lstat(name, stat);
	if (!(file = (t_file_info *)malloc(sizeof(t_file_info)))
			|| (!(file->name = ft_strdup(name))))
		exit(0);
	file->mode = stat->st_mode;
	file->st_nlink = stat->st_nlink;
	file->st_uid = stat->st_uid;
	file->st_gid = stat->st_gid;
	file->st_size = stat->st_size;
	file->st_rdev = stat->st_rdev;
	file->ftime = stat->st_mtimespec.tv_sec;
	file->ntime = stat->st_mtimespec.tv_nsec;
	file->st_blocks = stat->st_blocks;
	file->file_len = ft_strlen(file->name);
	/* realpath(path, file->full_path); */
	realpath(name, file->full_path);
	return (file);
}

void	ft_open_dirs(char *str, int *flags)
{
	DIR				*dir;
	/* char			*err; */
	size_t			*vector;
	struct dirent	*pDirent;
	t_file_info		*tmp;

	if(!(dir = opendir(str)))
	{
		/* ERROR HANDLE */
		/* perror(str); */
		return ;
	}
	vector = ft_vector_create(sizeof(size_t *));
	int i = 3;
	while ((pDirent = readdir(dir)) != NULL)
	{
		tmp = ft_add_file(pDirent->d_name);
		ft_vector_push_back((void **)&vector, &tmp);
		tmp = (t_file_info *)(*(vector + i++));
		/* ERROR HANDLE */
	}
	ft_rec_dirs(ft_vector_get_len(vector), &vector, str, flags);
	closedir(dir);
}
