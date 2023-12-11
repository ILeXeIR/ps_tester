#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "../libft/libft.h"

#define BUFFER 20000

void	print_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	test_push_swap(char *filename, int err)
{
	char	*line;
	char	command[BUFFER];
	int		fd;
	int		len;
	int		n;

	ft_printf("\nTest '%s':\n", filename + 6);
	if (err == 1)
		ft_printf("Error messages and zeros should be displayed.\n");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error("Can't open file.");
	line = get_next_line(fd);
	n = 1;
	while (line != NULL)
	{
		len = strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		ft_printf("Line %d - ", n);
		if (err == 0)
			sprintf(command, "ARG=\"%s\"; ../push_swap $ARG | ../checker_linux $ARG", line);
		else
			sprintf(command, "../push_swap \"%s\" 1>/dev/null", line);
		system(command);
		sprintf(command, "../push_swap \"%s\" 2>/dev/null | wc -l", line);
		system(command);
		free(line);
		line = get_next_line(fd);
		n++;
	}
	close(fd);
}

void	test_push_swap_empty(void)
{
	ft_printf("Test empty:\n[");
	system("../push_swap");
	ft_printf("] Shouldn't be anything between square brackets\n");
}

int	main(void)
{
	test_push_swap_empty();
	test_push_swap("files/test_errors.txt", 1);
	test_push_swap("files/test_3.txt", 0);
	test_push_swap("files/test_5.txt", 0);
	test_push_swap("files/test_100.txt", 0);
	test_push_swap("files/test_500.txt", 0);
	return (0);
}
