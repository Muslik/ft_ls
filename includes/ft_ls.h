/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 17:47:31 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/21 17:38:21 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# ifndef _DARWIN_FEATURE_64_BIT_INODE
# define _DARWIN_FEATURE_64_BIT_INODE
# endif

# define ARR_SIZE 10
# define A 1.5

# include "libft.h"

#include <sys/ioctl.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

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

int flags;

typedef	struct	s_ft_merge_info_ft_ls
{
	size_t		*to_sort;
	size_t		*buf;
	int			(*cmp)(void *data1, void *data2);
}				t_ft_merge_info_ft_ls;

/*
** blkcnt_t     - block size
** mode_t       - file permissions
** nlink_t      - number of hard links
** uid_t        - owner name
** gid_t        - owner group
** off_t        - file size
** dev_t        - device type
** time_t       - last modification time
** char *name   - file name
*/

/*
 * Колонки
*/
size_t			g_term_col;

typedef	struct	s_dir_info
{
	size_t	file_max_len;
	size_t	term_rows;
	size_t	files_ammount;
}				t_dir_info;

typedef struct	s_file_info
{
	blkcnt_t			st_blocks;
	mode_t				mode;
	nlink_t				st_nlink;
	uid_t				st_uid;
	gid_t				st_gid;
	off_t				st_size;
	dev_t				st_rdev;
	time_t				ftime;
	char				*name;
	char				full_path[PATH_MAX];
	char				*rel_path;
	size_t				file_len;
}				t_file_info;

/*
 ** VECTORS
*/

int		ft_vector_to_array(void **ft_vector);
void	*ft_vector_create(size_t elem_byte_size);
int		ft_vector_push_back(void **ft_vector, const void *data);
void	ft_vector_free(void **ft_vector);
long double	ft_ceill(long double x);
long double	ft_floorl(long double x);
void	*ft_vector_get_elem_n(void *ft_vector, size_t nbr);
void	*ft_vector_get_last_elem(void *ft_vector);
void	*ft_vector_get_first_elem(void *ft_vector);
size_t	ft_vector_get_len(void *ft_vector);

int		ft_open_dirs(char *path, char *name);
void	ft_rec_dirs(t_dir_info *dir_info, size_t **vector);

/*
 ** FLAGS PARSER
*/

int		ft_get_flags(int argc, char **argv);
int		ft_usage_error(char c);
int		ft_errno_error(char *path, char *name);

/*
 **
*/
void	ft_print_files(size_t *vector, t_dir_info *dir_info);
void	ft_print_in_terminal(size_t *vec_files, t_dir_info *dir_info);
int		ft_merge_sort_ft_ls(size_t *to_sort, size_t left, size_t right, int (*cmp)(void *data1, void *data2));
#endif
