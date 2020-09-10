#include <stdio.h>
#include "getline.h"
#include <malloc.h>

int main()
{
    t_getline getline = start_getline("CMakeLists.txt", 1000);
    char *line = getline_next(&getline);
    printf("%s\n", line);
    free(line);
    line = getline_next(&getline);
    printf("%s\n", line);
    stop_getline(&getline);
    return 0;
}
