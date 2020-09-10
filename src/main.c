#include <stdio.h>
#include "getline.h"
#include <stdlib.h>

int main()
{
    t_getline getline = start_getline("CMakeLists.txt", 10);
    char *line;
    while(getline_next(&getline, &line, 0))
	{
		printf("%s\n", line);
		free(line);
	}
	if(getline_next(&getline, &line, 1))
	printf("%s\n", line);
    stop_getline(&getline);
    return 0;
}
