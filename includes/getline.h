#ifndef MINI_READER_GETLINE_H
#define MINI_READER_GETLINE_H

typedef struct s_getline
{
    int file_descriptor;
    unsigned int buffer_size;
    char *buffer;
} t_getline;

int getline_next(t_getline *getline, char **line);
t_getline start_getline(char *filename, unsigned buffer_size);
void stop_getline(t_getline *get_line);

#endif //MINI_READER_GETLINE_H
