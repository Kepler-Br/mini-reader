#include <malloc.h>
#include "getline.h"
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

int getline_next(t_getline *getline, char **line)
{
    char *symbol;
    unsigned int size;
    int read_status;

    read_status = read(getline->file_descriptor, getline->buffer, getline->buffer_size-1);
    if(read_status <= 0 )
        return (read_status);
    getline->buffer[getline->buffer_size] = '\0';
    symbol = ft_strchr(getline->buffer, '\n');
    if(symbol == NULL)
    {

    }
    else
    {
        size = symbol - getline->buffer;
        line = malloc(sizeof(char)*size + 1);
        line[size] = '\0';
        ft_memcpy((void *)line, (void*)getline->buffer, size);
        ft_memmove((void*)getline->buffer, symbol + 1, ft_strchr(symbol, '\0') - symbol);
        return (line);
    }
}

t_getline start_getline(char *filename, unsigned buffer_size)
{
    t_getline getline;

    getline.buffer_size = buffer_size;
    getline.buffer = malloc(sizeof(char)*buffer_size + 1);
    getline.buffer[0] = '\0';
    getline.file_descriptor = open(filename, O_RDONLY);
    return (getline);
}

void stop_getline(t_getline *get_line)
{
    free(get_line->buffer);
    close(get_line->file_descriptor);
}
