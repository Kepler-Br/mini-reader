#include <stdio.h>
#include "getline.h"
#include <stdlib.h>
#include "libft.h"

typedef struct s_mini_argument
{
    char *name;
    int type;
    char *value;
} t_mini_argument;

#define MINIARG_TYPE_INT 0
#define MINIARG_TYPE_STR 1
#define MINIARG_TYPE_INVALID -1

int is_whitespace(char chr)
{
    if(chr == '\t' || chr == ' ')
        return (1);
    return (0);
}

char *skip_whitespaces(char *str)
{
    if(str == NULL)
        return (NULL);
    while(1)
    {
        if(*str == '\0')
            return (NULL);
        if(is_whitespace(*str))
            str++;
        else
            break;
    }
    return (str);
}

int is_valid_line(char *line)
{
    if(ft_strchr(line, ':') == NULL || ft_strchr(line, '=') == NULL)
        return (0);
    return (1);
}

char *miniarg_get_name(char *line)
{
    char *arg_name;
    char *arg_end;
    unsigned int str_len;

    if((line = skip_whitespaces(line)) == NULL)
        return (NULL);
    if((arg_end = ft_strchr(line, ':')) == NULL)
        return (NULL);
    while(is_whitespace(*arg_end))
        arg_end--;
    str_len = arg_end - line;

    arg_name = malloc(sizeof(char) * str_len);
    ft_strncpy(arg_name, line, str_len);
    return (arg_name);
//    ft_strncpy()
}

int miniarg_get_type(char *line)
{
    char *equ_chr;

    line = ft_strchr(line, ':');
    if((line = skip_whitespaces(++line)) == NULL)
        return (MINIARG_TYPE_INVALID);
    if((equ_chr = ft_strchr(line, '=')) == NULL)
        return (MINIARG_TYPE_INVALID);
    equ_chr--;
    if(line == equ_chr)
        return (MINIARG_TYPE_INVALID);
    while(is_whitespace(*equ_chr))
        equ_chr--;

    if(equ_chr - line == 2 && ft_strncmp(line, "int", 3) == 0)
        return (MINIARG_TYPE_INT);
    if(equ_chr - line == 2 && ft_strncmp(line, "str", 3) == 0)
        return (MINIARG_TYPE_STR);
    return (MINIARG_TYPE_INVALID);
}

char *miniarg_get_value(char *line)
{

}

t_mini_argument *parse_miniarg_line(char *line)
{
    t_mini_argument *arg;

    if(!is_valid_line(line))
        return (NULL);
    arg = malloc(sizeof(t_mini_argument));
    arg->name = miniarg_get_name(line);
    arg->type = miniarg_get_type(line);
//    arg->value = miniarg_get_value(line);
    return (arg);
}

int main()
{
    t_getline getline = start_getline("config.mini", 10);
    char *line;
    t_mini_argument *arg;
    while(getline_next(&getline, &line, 0))
	{
        if(!is_valid_line(line))
        {
            free(line);
            continue;
        }
        printf("%s\n", line);
        arg = parse_miniarg_line(line);
        printf("Name: %s\n", arg->name);
        printf("Type: %d\n", arg->type);
//        printf("Is valid: %d\n", is_valid_line(line));
		free(line);
	}
//	if(getline_next(&getline, &line, 1))
//	printf("%s\n", line);
    stop_getline(&getline);
    return 0;
}
