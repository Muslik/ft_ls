/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 15:59:25 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/24 16:07:01 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			fill_file(struct stat *stat, t_file_info *file)
{
	if (flags & LS_L)
	{
		file->mode = stat->st_mode;
		file->st_size = stat->st_size;
		file->st_uid = stat->st_uid;
		file->st_gid = stat->st_gid;
		file->st_rdev = stat->st_rdev;
		file->st_nlink = stat->st_nlink;
		file->st_blocks = stat->st_blocks;
		file->ftime = stat->st_mtimespec.tv_sec;
		file->ftime = (flags & LS_U) ? stat->st_atimespec.tv_sec : file->ftime;
		file->ftime = (flags & LS_UU) ? stat->st_birthtimespec.tv_sec : file->ftime;
		file->ftime = (flags & LS_C) ? stat->st_ctimespec.tv_sec : file->ftime;
	}
	else if (flags & LS_SS)
		file->st_size = stat->st_size;
	else if (flags & (LS_U | LS_UU | LS_C | LS_T))
	{
		file->ftime = stat->st_mtimespec.tv_sec;
		file->ftime = (flags & LS_U) ? stat->st_atimespec.tv_sec : file->ftime;
		file->ftime = (flags & LS_UU) ? stat->st_birthtimespec.tv_sec : file->ftime;
		file->ftime = (flags & LS_C) ? stat->st_ctimespec.tv_sec : file->ftime;
	}
}

t_file_info	*ft_add_file(char *path, struct dirent	*pDirent)
{
	t_file_info		*file;
	struct stat		*stat;

	if (!(file = (t_file_info *)malloc(sizeof(t_file_info))))
		exit(EXIT_FAILURE);
	ft_memset(file, 0, sizeof(t_file_info));
	if (!(file->name = ft_strdup(pDirent->d_name)))
		exit(EXIT_FAILURE);
	if (path[0] == '/' && path[1] == '\0')
		file->rel_path = ft_strjoin(path, "", 0);
	else
		file->rel_path = ft_strjoin(path, "/", 0);
	file->rel_path = ft_strjoin(file->rel_path, file->name, 1);
	file->type = pDirent->d_type;
	if (flags & (LS_T | LS_UU | LS_U | LS_SS | LS_C | LS_L))
	{
		if (!(stat = (struct stat *)malloc(sizeof(struct stat))))
			exit(EXIT_FAILURE);
		lstat(file->rel_path, stat);
		fill_file(stat, file);
		free(stat);
	}
	file->file_len = ft_strlen(file->name);
	realpath(file->name, file->full_path);
	return (file);
}
