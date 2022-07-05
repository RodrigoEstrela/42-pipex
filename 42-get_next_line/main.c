#include "get_next_line.h"

int main()
{
    int fd = open(/*"put name of file here"*/, O_RDWR);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
	}
}
