#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "../libft/libft.h"

#define BUFFER 50000

void	print_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	test_checker(char *filename, int err)
{
	char	*line;
	char	command[BUFFER];
	int		fd;
	int		len;
	int		n;

	ft_printf("Test '%s':\n", filename + 6);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error("Can't open file.");
	line = get_next_line(fd);
	n = 1;
	if (err == 1)
		ft_printf("Error messages should be displayed.\n");
	while (line != NULL)
	{
		len = strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		ft_printf("Line %d - ", n);
		if (err == 0)
			sprintf(command, "ARG=\"%s\"; ../push_swap $ARG | ../checker $ARG", line);
		else
			sprintf(command, "echo -n | ../checker \"%s\" 1>/dev/null", line);
		system(command);
		free(line);
		line = get_next_line(fd);
		n++;
	}
	close(fd);
}

void	test_checker_empty(void)
{
	ft_printf("Test empty:\n[");
	system("../checker");
	ft_printf("] Shouldn't be anything between square brackets\n");
}

void	test_checker_simple(void)
{
	ft_printf("Test 1: ");
	system("echo -n | ../checker \"1 2 3\"");
	ft_printf("Test 2: ");
	system("echo -n | ../checker \"1\"");
	ft_printf("Test 3: ");
	system("echo -n \"sa\nsb\nss\npb\npa\nra\nrb\nrr\nrra\nrrb\nrrr\n\" | ../checker \"1\"");
	ft_printf("Test 4: ");
	system("echo -n \"ra\nra\nra\nsa\nsa\n\" | ../checker \"1 2 3\"");
	ft_printf("Test 5: ");
	system("echo -n \"pb\npb\nss\npa\npa\n\" | ../checker \"2 1 4 3\"");
}

void	test_checker_ko(void)
{
	ft_printf("Test 1: ");
	system("echo -n | ../checker \"4 2 3\"");
	ft_printf("Test 2: ");
	system("echo -n \"pb\n\" | ../checker \"1 2 3\"");
	ft_printf("Test 3: ");
	system("echo -n \"ra\nra\nra\nra\n\" | ../checker \"1 2 3\"");
	ft_printf("Test 4: ");
	system("echo -n \"pb\npb\nss\npa\npa\n\" | ../checker \"1 2 4 3\"");
}

void	test_checker_error(void)
{
	ft_printf("Incorrect instructions 1: ");
	system("echo -n \"pc\n\" | ../checker \"1 2 3\"");
	ft_printf("Incorrect instructions 2: ");
	system("echo -n \"sa sa\n\" | ../checker \"1 2 3\"");
	ft_printf("Incorrect instructions 3: ");
	system("echo -n \"rrrr\n\" | ../checker \"1 2 3\"");
	ft_printf("Incorrect instructions 4: ");
	system("echo -n \"sa\n\nsa\n\" | ../checker \"1 2 3\"");
	ft_printf("Incorrect instructions 5: ");
	system("echo -n \"sa\" | ../checker \"1 2 3\"");
}

int	main(void)
{
	test_checker_empty();
	ft_printf("\nTests OK:\n");
	test_checker_simple();
	test_checker("files/test_3.txt", 0);
	test_checker("files/test_100.txt", 0);
	test_checker("files/test_500.txt", 0);
	ft_printf("\nTests KO:\n");
	test_checker_ko();
	ft_printf("\nTests Errors:\n");
	test_checker("files/test_errors.txt", 1);
	test_checker_error();
	return (0);
}
