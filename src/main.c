#include "../incl/minishell.h"

void	print_folders(char **folder_strs)
{
	int	i;

	i = 0;
	while (folder_strs[i])
	{
		printf("folder %i: |%s|\n", i, folder_strs[i]);
		i++;
	}
}

// t_cmd_list	*scan_folder(char *folder_buffer, char *path, t_data *data)
// {
// 	t_cmd_list	*new;
//
// 	new = NULL;
// 	return (new);
// }

int	fpl(char *path)
{
	int	i;

	i = 0;
	while (*path != ':' && *path)
	{
		i++;
		path++;
	}
	return (i);
}

int	get_folders(char *path, char **folder_strs)
{
	int	i;

	i = 0;
	while (*path)
	{
		folder_strs[i] = malloc(sizeof(char) * (fpl(path) + 1));
		if (folder_strs[i] == NULL)
		{
			perror("Folder str: ");
			return (-1);
		}
		while (*path != ':' && *path)
		{
			*folder_strs[i] = *path;
			path++;
			folder_strs[i]++;
		}
		if (*path)
			path++;
	}
	return (0);
}

int	get_number_of_folders(char *path)
{
	int	i;

	i = 1;
	while (*path)
	{
		if (*path == ':')
			i++;
		path++;
	}
	return (i);
}

void	init_folder_strs(char **folder_strs, int num_of_flds)
{
	int	i;

	i = 0;
	while (i != num_of_flds)
	{
		folder_strs[i] = NULL;
		i++;
	}
}

int	get_cmd_list(t_data *data)
{
	char	*path;
	char	**folder_strs;

	data = data;
	folder_strs = NULL;
	path = NULL;
	path = getenv("PATH");
	if (path == NULL)
	{
		perror("Path: ");
		return (-1);
	}
	folder_strs = malloc(sizeof(char *) * (get_number_of_folders(path) + 1));
	if (folder_strs == NULL)
	{
		perror("Folder strings: ");
		return (-1);
	}
	folder_strs[get_number_of_folders(path)] = NULL;
	init_folder_strs(folder_strs, get_number_of_folders(path));
	get_folders(path, folder_strs);
	printf("%s\n", path);
	printf("number of folders to scan: %i\n", get_number_of_folders(path));
	print_folders((folder_strs));
	return (0);
}

int main(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		perror("Main data struct: ");
		return (-1);
	}
	if(data_init(data) == -1)
		return (-1);
	if (get_cmd_list(data) == -1)
		return (-1);
	free_data(data);
    return (0);
}
