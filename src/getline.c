#include <stdlib.h>
#include "getline.h"
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

int getline_next(t_getline *getline, char **line)
{
    char *symbol;
    unsigned int size;
    int read_count;
    unsigned int prev_line_size;

	// reading first time
    if(ft_strlen(getline->buffer) == 0)
    {
		read_count = read(getline->file_descriptor, getline->buffer, getline->buffer_size);
		if(read_count <= 0 )
			return (read_count);
		getline->buffer[getline->buffer_size] = '\0';
		symbol = ft_strchr(getline->buffer, '\n');
		// EOL not found
		if(symbol == NULL)
		{
			*line = malloc(sizeof(char)*1);
			*line[0] = '\0';
			while(read_count != 0 || *symbol != '\n')
			{
				prev_line_size = ft_strlen(*line);
				*line = ft_realloc(*line, prev_line_size, read_count + 1);
				if((symbol = ft_strchr(getline->buffer, '\n')) != NULL)
				{
					read_count = symbol;
				}
				ft_memcpy(&(*line)[prev_line_size], getline->buffer, read_count + 1);
				(*line)[prev_line_size + read_count] = '\0';
				read_count = read(getline->file_descriptor, getline->buffer, getline->buffer_size);
				getline->buffer[getline->buffer_size] = '\0';
				symbol = ft_strchr(getline->buffer, '\n');
			}
			return (1);
		}
    }
    else if (ft_strlen(getline->buffer) != 0)
	{

	}
    else
    {
        size = symbol - getline->buffer;
        *line = malloc(sizeof(char)*size + 1);
		(*line)[size] = '\0';
        ft_memcpy((void *)*line, (void*)getline->buffer, size);
        ft_memmove((void*)getline->buffer, symbol + 1, ft_strchr(symbol, '\0') - symbol);
        return (1);
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
