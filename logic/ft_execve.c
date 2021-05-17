#include "header.h"

char *get_excve_str(t_bin *bin, char *command, char **argv)
{
	char			*execve_str;
	int				ret;
	char			*dir_to_open = NULL;
	char			**split_str = NULL;
	struct dirent	*dir = NULL;
	int				flag = 1;
	int 			i = 0;
	DIR				*folder = NULL;
	char			*path = NULL;

	if (command[ft_strlen(command) - 1] == '/')
	{
		folder = opendir(command);
		if (folder)
			dir = readdir(folder);
		if (command)
			command_error(command, 6);
		else
			command_error(command, 5);
		return(NULL);
	}
	// проверка на абсолютный путь
	if (argv[0][0] == '/' || argv[0][0] == '.')
		execve_str = command;
	else
	{
		// достаем папки с коммандами из path
		path = ft_get_value(bin->export, "PATH");
		if (!path)
		{
			command_error(command, 5);
			return(NULL);
		}
		split_str = ft_split(path, ':');
		while (split_str[i] && flag)
		{
			if (dir_to_open)
				free(dir_to_open);
			dir_to_open = ft_strjoin(split_str[i], "/");
			folder = opendir(dir_to_open);
			while (folder && ret && flag)
			{
				dir = readdir(folder);
				if (!dir)
					ret = 0;
				if (dir && !strcmp(dir->d_name, command))
					flag = 0;
			}
			ret = 1;
			if (folder)
				closedir(folder);
			i++;
		}
		if (!dir)
		{
			command_error(command, 1);
			return(NULL);
		}
		execve_str = ft_strjoin(dir_to_open, command);
	}
	if (dir_to_open)
			free(dir_to_open);
	if (split_str)
		free_split(split_str);
	return(execve_str);
}

void	ft_execve(t_bin *bin, char *execve_str, char **argv)
{
	int		ret = 0;
	pid_t	pid;
	//folder = opendir(argv[0]);
	// for pipes

	// делает пид если нет пайпов
	if (bin->p_count == 0)
	{
		execve_str = get_excve_str(bin, argv[0], argv);
		bin->pid = fork();
	}
	// запуск execve
	// if (bin->pid == 0)
	// {
	if (bin->pid == 0)
	{
		ret = execve(execve_str, argv, bin->envp);
		if (argv[0][0] == '.')
			exit(command_error(argv[0], 5));
		else
			exit(command_error(argv[0], 1));
	}
	else
		wait(NULL);
	write(2, "\nft_execve main process\n", 24);
}