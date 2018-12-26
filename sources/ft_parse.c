/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 13:39:24 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/26 13:06:33 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_strchr_by_index(char *str, int c)
{
	int j;

	j = 0;
	while (str[j])
	{
		if (str[j] == c)
			return (j);
		j++;
	}
	return (-1);
}

int			ft_usage_error(char c)
{
	ft_putstr_fd("./ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ./ft_ls [-aflRrtG1Ss] [file ...]", 2);
	exit(EXIT_FAILURE);
	return (1);
}

int			ft_errno_error(char *path, char *name)
{
	if (errno != 20)
	{
		ft_putstr_fd("./ft_ls: ", 2);
		if (errno == 13)
			ft_putstr_fd(name, 2);
		else
			ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (1);
}

static int	ft_add_flags(char *str)
{
	int bit;

	while (*(++str))
	{
		if ((bit = ft_strchr_by_index("RSUacflrtu1", *str)) == -1)
			ft_usage_error(*str);
		if ((*str == 'l') || (*str == '1'))
			g_flags &= ~(LS_ONE | LS_L);
		if ((*str == 'u') || (*str == 'U') || (*str == 'c'))
			g_flags &= ~LS_U & ~LS_C & ~LS_UU;
		g_flags |= (1 << bit);
	}
	return (1);
}

int			ft_get_flags(int argc, char **argv)
{
	int i;

	i = 1;
	if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == '\0')
		return (i + 1);
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
	{
		if (!ft_add_flags(argv[i]))
			return (-1);
		i++;
	}
	return (i);
}
