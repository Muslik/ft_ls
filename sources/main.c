/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:53:18 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/25 23:47:59 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	find_term_col_ammount(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	g_term_col = w.ws_col;
}

char	*ft_get_name(char *str)
{
	char	*pos;

	pos = str;
	while (*str != '\0')
	{
		if (*str == '/')
			pos = str + 1;
		str++;
	}
	return (pos);
}

void	ft_print_dir_argv(char *path, size_t check)
{
	size_t	len;
	char	*buf;

	len = ft_strlen(path);
	if (!(buf = malloc(len + 3)))
		exit(EXIT_FAILURE);
	if (check)
	{
		ft_memmove(buf, "\n", 1);
		ft_memmove(buf + 1, path, len);
		ft_memmove(buf + len + 1, ":\n", 2);
		write(1, buf, len + 3);
	}
	else
	{
		ft_memmove(buf, path, len);
		ft_memmove(buf + len, ":\n", 2);
		write(1, buf, len + 2);
	}
	free(buf);
}

static void mul_args(size_t i, size_t argc, char **argv)
{
	size_t			j;
	size_t			*vector;
	t_file_info		*file;
	size_t			len;
	struct stat		*stat;

	vector = ft_vector_create(sizeof(size_t *));
	j = i;
	while (j < argc)
	{
		if (!(file = (t_file_info *)malloc(sizeof(t_file_info))))
			exit(EXIT_FAILURE);
		ft_memset(file, 0, sizeof(t_file_info));
		if (!(file->name = ft_strdup(ft_get_name(argv[j]))))
			exit(EXIT_FAILURE);
		printf("%s\n", file->name);
		fflush(stdout);
		file->file_len = ft_strlen(file->name);
		if (!(file->rel_path = ft_strdup(argv[j])))
			exit(EXIT_FAILURE);
		if (g_flags & (LS_T | LS_UU | LS_U | LS_SS | LS_C))
		{
			if (!(stat = (struct stat *)malloc(sizeof(struct stat))))
				exit(EXIT_FAILURE);
			ft_memset(stat, 0 , sizeof(struct stat));
			lstat(file->rel_path, stat);
			if (g_flags & LS_SS)
			{
				file->st_size = stat->st_size;
			}
			else if (g_flags & (LS_U | LS_UU | LS_C | LS_T))
			{
				file->ftime = stat->st_mtimespec.tv_sec;
				file->ftime = (g_flags & LS_U) ? stat->st_atimespec.tv_sec : file->ftime;
				file->ftime = (g_flags & LS_UU) ? stat->st_birthtimespec.tv_sec : file->ftime;
				file->ftime = (g_flags & LS_C) ? stat->st_ctimespec.tv_sec : file->ftime;
			}
			free(stat);
		}
		if (!(ft_vector_push_back((void **)&vector, &file)))
			exit(EXIT_FAILURE);
		j++;
	}
	len = ft_vector_get_len(vector);
	ft_vector_to_array((void **)&vector);
	ft_ls_sort(vector, len);
	i = -1;
	while (++i < len)
	{
		file = (t_file_info *)(vector[i]);
		if (i == 0)
			ft_print_dir_argv(file->rel_path, 0);
		else
			ft_print_dir_argv(file->rel_path, 1);
		ft_open_dirs(file->rel_path, file->name, 0);
	}
	ft_free_vec_of_files(len, vector);
}

int main(int argc, char **argv)
{
	int		i;

	g_flags = 0;
	i = ft_get_flags(argc, argv);
	find_term_col_ammount();
	if (i == argc)
	{
		ft_open_dirs(".", ".", 0);
		return (0);
	}
	if (i == argc - 1)
	{
		ft_open_dirs(argv[i], ft_get_name(argv[i]), 0);
		return (0);
	}
	mul_args(i, argc, argv);
	return (0);
}
