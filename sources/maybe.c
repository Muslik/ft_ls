#include <stdlib.h>
/* int		ft_handle_error(int er_code) */
/* { */

/* } */

int		ft_parse_flags(int argc, char **argv)
{
	/* char *flags = "lRart"; */
	int i;
	DIR *dir;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] != '-' || argv[i][1] == '\0')
		{
			dir = opendir(argv[1]);
			if (errno == 2)
			{
				ft_putstr("./ft_ls: ");
				perror(argv[1]);
			}
			if (dir)
				closedir(dir);
		}
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] != '\0')
		{
			ft_putendl_fd("./ft_ls: illegal option -- -", 2);
			ft_putendl_fd("usage: ./ft_ls [Ralrt] [file ...]", 2);
			return (-1);
		}
	}
	return (0);
}

int		ft_parse_flags(int argc, char **argv)
{
	int i;
	char *str;

	i = 0;
	while (++i < argc && argv[i][0] == '-')
	{
		str = argv[i];
		while (*str)
			ft_strchr(LS_FLAGS, *str++)
	}
}
