#include "header.h"

static int	 ft_check_n(t_bin *bin, char **argv)
{
	int i;
	int j;
	int ret;

	i = 1;
	j = 2;
	while (argv[i])
	{
		if (!ft_strncmp(argv[i], "-n", 2))
		{
			while (argv[i][j])
			{
				if (argv[i][j] != 'n' && argv[i][j] && argv[i][j] != ' ')
					return (i);
				j++;
			}
			bin->n_flag = 1;
			ret = i + 1;
		}
		i++;
		j = 2;
	}
	if (bin->n_flag)
		return (ret);
	else
		return (1);
}


void ft_echo(t_bin *bin, char **argv)
{
	int		move;

	//argv = bin->argv;
	move = 1;
	if (argv[1] == 0)
	{
		ft_putchar('\n');
		return;
	}
	move = ft_check_n(bin, argv);
	if (!argv[2] && bin->n_flag)
		return;
	while(argv[move])
	{
		ft_putstr(argv[move]);
		move++;
		if (argv[move])
			ft_putchar(' ');
	}
	if (!bin->n_flag)
		ft_putchar('\n');
}