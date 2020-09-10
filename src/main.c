#include <stdio.h>
#include "getline.h"
#include <stdlib.h>

int main()
{
    t_getline getline = start_getline("CMakeLists.txt", 5);
    char *line;
    getline_next(&getline, &line);
    printf("%s\n", line);
    free(line);
    getline_next(&getline, &line);
    printf("%s\n", line);
    stop_getline(&getline);
    return 0;
}
