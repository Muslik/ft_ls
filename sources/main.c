/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:53:18 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/26 15:16:32 by dmorgil          ###   ########.fr       */
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

void	ft_sort_args(size_t *vector, size_t len)
{
	char		*tmp;
	t_file_info	*file;
	size_t		i;

	i = -1;
	while (++i < len)
	{
		file = (t_file_info *)(vector[i]);
		tmp = file->rel_path;
		file->rel_path = file->name;
		file->name = tmp;
	}
	ft_ls_sort(vector, len);
	i = -1;
	while (++i < len)
	{
		file = (t_file_info *)(vector[i]);
		tmp = file->rel_path;
		file->rel_path = file->name;
		file->name = tmp;
	}
}

int		main(int argc, char **argv)
{
	int		i;

	g_flags = 0;
	i = ft_get_flags(argc, argv);
	if (i == argc)
	{
		ft_open_dirs(".", ".", 0);
		return (0);
	}
	ft_print_dirs(i, argc, argv, ft_print_non_dirs(i, argc, argv));
	return (0);
}
