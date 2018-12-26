/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:31:17 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/26 11:20:24 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_rec_dirs(t_dir_info *dir_info, size_t **vector)
{
	size_t		i;
	t_file_info *tmp;

	i = -1;
	ft_vector_to_array((void **)vector);
	if (dir_info->files_ammount > 1)
		ft_ls_sort(*vector, dir_info->files_ammount);
	if (dir_info->files_ammount > 0)
		ft_print_files(*vector, dir_info, 1);
	if (g_flags & LS_RR)
	{
		while (++i < dir_info->files_ammount)
		{
			tmp = (t_file_info *)(*vector)[i];
			if (g_flags & LS_A)
				if (tmp->name[0] == '.' && (tmp->name[1] == '\0' ||
							(tmp->name[1] == '.' && tmp->name[2] == '\0')))
					continue;
			if (tmp->type != DT_DIR)
				continue;
			ft_open_dirs(tmp->rel_path, tmp->name, 1);
		}
	}
	ft_free_vec_of_files(dir_info->files_ammount, *vector);
}

void	ft_print_dir(char *path, size_t check)
{
	size_t	len;
	char	*buf;

	if (check)
	{
		len = ft_strlen(path);
		if (!(buf = malloc(len + 3)))
			exit(EXIT_FAILURE);
		ft_memmove(buf, "\n", 1);
		ft_memmove(buf + 1, path, len);
		ft_memmove(buf + len + 1, ":\n", 2);
		write(1, buf, len + 3);
		free(buf);
	}
}

void	ft_fill_dir_info(t_dir_info *dir_info, t_file_info *tmp)
{
	dir_info->file_max_len = dir_info->file_max_len < tmp->file_len ?
		tmp->file_len : dir_info->file_max_len;
	dir_info->size_max_len = dir_info->size_max_len < tmp->size_len ?
		tmp->size_len : dir_info->size_max_len;
	dir_info->links_max_len = dir_info->links_max_len < tmp->nlink_len ?
		tmp->nlink_len : dir_info->links_max_len;
	dir_info->u_name_max_len = dir_info->u_name_max_len < tmp->u_name_len ?
		tmp->u_name_len : dir_info->u_name_max_len;
	dir_info->g_name_max_len = dir_info->g_name_max_len < tmp->g_name_len ?
		tmp->g_name_len : dir_info->g_name_max_len;
	dir_info->minor_max_len = dir_info->minor_max_len < tmp->minor_len ?
		tmp->minor_len : dir_info->minor_max_len;
	dir_info->major_max_len = dir_info->major_max_len < tmp->major_len ?
		tmp->major_len : dir_info->major_max_len;
	dir_info->lnk_max_len = dir_info->lnk_max_len < tmp->lnk_len ?
		tmp->lnk_len : dir_info->lnk_max_len;
	dir_info->size_max_len = dir_info->size_max_len <
		dir_info->minor_max_len + dir_info->major_max_len + 3 ?
		dir_info->minor_max_len + dir_info->major_max_len + 3 :
		dir_info->size_max_len;
	dir_info->total += tmp->st_blocks;
	dir_info->lnk_ammount += (tmp->lnk_len) ? 1 : 0;
}

void	ft_init_dir_info(t_dir_info *dir_info)
{
	dir_info->lnk_ammount = 0;
	dir_info->file_max_len = 0;
	dir_info->size_max_len = 0;
	dir_info->links_max_len = 0;
	dir_info->lnk_max_len = 0;
	dir_info->u_name_max_len = 0;
	dir_info->g_name_max_len = 0;
	dir_info->minor_max_len = 0;
	dir_info->major_max_len = 0;
	dir_info->file_max_len = 0;
	dir_info->total = 0;
}

int		ft_open_dirs(char *path, char *name, size_t check)
{
	DIR				*dir;
	size_t			*vector;
	struct dirent	*pdirent;
	t_file_info		*tmp;
	t_dir_info		dir_info;

	ft_print_dir(path, check);
	if (!(dir = opendir(path)))
		return (ft_errno_error(path, name));
	vector = ft_vector_create(sizeof(size_t *));
	ft_init_dir_info(&dir_info);
	while ((pdirent = readdir(dir)) != NULL)
	{
		if (pdirent->d_name[0] != '.' || (g_flags & LS_A))
		{
			tmp = ft_add_file(path, pdirent);
			if (!(ft_vector_push_back((void **)&vector, &tmp)))
				exit(EXIT_FAILURE);
			ft_fill_dir_info(&dir_info, tmp);
		}
	}
	dir_info.files_ammount = ft_vector_get_len(vector);
	ft_rec_dirs(&dir_info, &vector);
	return (closedir(dir));
}
