#include "header.h"

int		find_redirects(t_bin * bin)
{
	int i;

	i = -1;
	while (bin->argv[++i])
		if (bin->argv[i][0] == '>' || bin->argv[i][0] == '<')
			return (1);
	return (0);
}

// 1 - >>, 2 - <, 3 - >
// обработать ошибки

int		ft_redopen(t_bin *bin, char *way, int flag, int index)
{
	int ret = 0;

	if (flag == 1)
	{
		if (bin->to)
			close(bin->to);
		ret = open(way, O_CREAT | O_RDWR | O_APPEND, 0666);
	}
	if (flag == 2)
	{
		if (bin->from)
			close(bin->from);
		ret = open(way, O_RDONLY);
	}
	if (flag == 3)
	{
		if (bin->to)
			close(bin->to);
		ret = open(way, O_CREAT | O_RDWR | O_APPEND, 0666);
	}
	if (ret == -1)
	{
		command_error(way, 5);
		bin->error = 1;
		ft_close_redifd(bin);
		return (-1);
	}
	if (flag == 2)
	{
		bin->from = ret;
		bin->indx_from = index;
	}
	else if ( flag == 1)
	{
		bin->to = ret;
		bin->append = 1;
		bin->indx_to = index;
	}
	else
	{
		bin->to = ret;
		bin->append = 0;
		bin->indx_to = index;
	}
	return (1);
}

void	ft_redirects(t_bin *bin, char **argv)
{
	int i;
	int flag;

	i = 0;
	bin->del_pipes = 0;
	while (argv[i])
	{
		flag = 0;
		if	(!ft_strcmp(argv[i], "|"))
			bin->del_pipes++;
		if	(!ft_strcmp(argv[i], ">>"))
			flag = ft_redopen(bin, argv[i + 1], 1, i - 1);
		if	(!ft_strcmp(argv[i], "<"))
			flag = ft_redopen(bin, argv[i + 1], 2, i - 1);
		if	(!ft_strcmp(argv[i], ">"))
			flag = ft_redopen(bin, argv[i + 1], 3, i - 1);
		if (flag)
		{
			argv = ft_del_index_in2massive(argv, i);
			if (argv[i])
				argv = ft_del_index_in2massive(argv, i);
			i--;
		}
		i++;
	}
	bin->argv = argv;
}