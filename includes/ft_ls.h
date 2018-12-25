/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 17:47:31 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/25 21:06:27 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define ARR_SIZE 10
# define A 1.5

# include "libft.h"

# include <sys/ioctl.h>
# include <limits.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/acl.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

# define ANSI_COLOR_BLACK   "\x1b[31m"
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36"
# define ANSI_COLOR_RESET   "\x1b[0m"

# define LS_RR	1
# define LS_SS	2
# define LS_UU	4
# define LS_A	8
# define LS_C	16
# define LS_F	32
# define LS_L	64
# define LS_R	128
# define LS_T	256
# define LS_U   512
# define LS_ONE 1024

int					g_flags;

typedef	struct		s_ft_merge_info_ft_ls
{
	size_t			*to_sort;
	size_t			*buf;
	int				(*cmp)(void *data1, void *data2);
}					t_ft_merge_info_ft_ls;

/*
 ** Columns
*/

size_t				g_term_col;

typedef	struct		s_dir_info
{
	size_t			file_max_len;
	size_t			term_rows;
	size_t			files_ammount;
	size_t			links_max_len;
	size_t			u_name_max_len;
	size_t			g_name_max_len;
	size_t			size_max_len;
	size_t			minor_max_len;
	size_t			major_max_len;
	size_t			lnk_max_len;
	size_t			total;
	size_t			lnk_ammount;
}					t_dir_info;

typedef struct		s_file_info
{
	blkcnt_t		st_blocks;
	mode_t			mode;
	char			lnk[PATH_MAX + 1];
	char			*st_nlink;
	char			*minor;
	char			*major;
	char			*u_name;
	char			*g_name;
	off_t			st_size;
	char			*str_size;
	time_t			ftime;
	unsigned char	type;
	char			*name;
	char			full_path[PATH_MAX];
	char			*rel_path;
	char			f_color[9];
	size_t			lnk_len;
	size_t			file_len;
	size_t			size_len;
	size_t			nlink_len;
	size_t			u_name_len;
	size_t			g_name_len;
	size_t			minor_len;
	size_t			major_len;
}					t_file_info;

/*
 ** VECTORS
*/

int					ft_vector_to_array(void **ft_vector);
void				*ft_vector_create(size_t elem_byte_size);
int					ft_vector_push_back(void **ft_vector, const void *data);
void				ft_vector_free(void **ft_vector);
long double			ft_ceill(long double x);
long double			ft_floorl(long double x);
void				*ft_vector_get_elem_n(void *ft_vector, size_t nbr);
void				*ft_vector_get_last_elem(void *ft_vector);
void				*ft_vector_get_first_elem(void *ft_vector);
size_t				ft_vector_get_len(void *ft_vector);

int					ft_open_dirs(char *path, char *name, size_t check);
void				ft_rec_dirs(t_dir_info *dir_info, size_t **vector);

/*
 ** FLAGS PARSER
*/

void				ft_print_dir(char *path, size_t check);
char				ft_get_file_type(int mode);
char				ft_get_file_acl(char *path);
char				*ft_show_time(t_file_info *file);

void				ft_free_vec_of_files(t_dir_info *dir_info, size_t *vector);
int					ft_get_flags(int argc, char **argv);
int					ft_usage_error(char c);
int					ft_errno_error(char *path, char *name);

int					ft_display_list(t_file_info *file, t_dir_info *dir_info,
									char *buf, size_t offset);
void				ft_print_files(size_t *vector, t_dir_info *dir_info);
int					cmp_alpha(void *data1, void *data2);
int					rev_cmp_alpha(void *data1, void *data2);
void				ft_ls_sort(size_t *vector, size_t len);
void				ft_print_files(size_t *vector, t_dir_info *dir_info);
void				ft_print_in_terminal(size_t *vec_files,
										t_dir_info *dir_info);
int					ft_m_sort(size_t *to_sort, size_t left,
						size_t right, int (*cmp)(void *data1, void *data2));
t_file_info			*ft_add_file(char *path, struct dirent	*pdirent);
#endif
