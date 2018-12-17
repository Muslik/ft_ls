/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 17:47:31 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/17 15:09:33 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# define ARR_SIZE 10
# define A 1.5

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# define LS_FLAGS "Ralrt"

typedef	struct	s_ft_merge_info_ft_ls
{
	size_t		*to_sort;
	size_t		*buf;
	int			(*cmp)(void *data1, void *data2);
}				t_ft_merge_info_ft_ls;

typedef	struct	s_flags
{
	char		l;
	char		R;
	char		a;
	char		r;
	char		t;
}				t_flags;

typedef struct	s_file_info
{
	char		*filename;
	char		*filetime;
	char		*fileright;
}				t_file_info;

typedef struct	s_help
{
	char		*str;
}				t_help;

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

/*
 ** FLAGS PARSER
*/

int		ft_get_flags(t_flags *flags, int argc, char **argv);
void	ft_add_flags(t_flags *flags, char *str);
void	ft_handle_errors(char *str);
#endif
