#include "get_next_line.h"
#include <fcntl.h>

int	main()
{
	int	file;
	char	*text;

	file = open("test.txt", O_RDONLY);
	text = get_next_line(file);

	while (text)
	{
		printf("%s", text);
		free(text);
		text = get_next_line(file);
	}
	close(file);
	return (0);
}