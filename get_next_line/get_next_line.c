#include "get_next_line.h"

int ft_strlen(char *s)
{
    int i = 0;

    if (!s)
        return(0);
    while(s[i])
        i++;
    return(i);
}

int checknl(char *s)
{
    if (!s)
        return(0);
    while(*s)
    {
        if (*s == '\n')
            return(1);
        s++;
    }
    return (0);
}

char *ft_calloc(int len, int size)
{
    int i = 0;
    char *str;

    if (len < 0)
        return(NULL);
    str = (char *)malloc(len * size);
    while (i < len)
        str[i++] = '\0';
    return(str);
}

char *ft_strjoin(char *s1, char *s2)
{
    int i = 0;
    int j = 0;
    char *join;

    if (!s1)
        s1 = ft_calloc(1, sizeof(char));
    if (!s1 && !s2)
        return(NULL);
    if (!s2)
        return(s1);
    join = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
    while (s1[i])
    {
        join[i] = s1[i];
        i++;
    }
    while (s2[j])
        join[i++] = s2[j++];
    free (s1);
    return(join);
}

char *get_line(char *st)
{
    int i = 0;
    char *line;

    if (!st[0])
        return(NULL);
    while (st[i] && st[i] != '\n')
        i++;
    if (st[i] == '\n')
        i++;
    line = ft_calloc(i + 1, sizeof(char));
    i = 0;
    while (st[i] && st[i] != '\n')
    {
        line[i] = st[i];
        i++;
    }    
    if (st[i] == '\n')
        line[i] = '\n';
    return (line);
}

char *get_st(char *st)
{
    int i = 0;
    int j = 0;
    char *new;

    if (!st)
        return(NULL);
    while(st[i] && st[i] != '\n')
        i++;
    if (st[i] == '\0')
        return(free(st), NULL);
    i++;
    new = ft_calloc((ft_strlen(st) - i) + 1, sizeof(char));
    while(st[i])
        new[j++] = st[i++];
    free(st);
    return (new);
}

char *get_next_line(int fd)
{
    static char *st = NULL;
    char *line = NULL;
    char buffer[BUFFER_SIZE + 1];
    int rd = 1;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return(NULL);
    while (rd > 0 && checknl(st) == 0)
    {
        rd = read(fd, buffer, BUFFER_SIZE);
        if (rd == -1)
            return(free(st), NULL);
        buffer[rd] = '\0';
        st = ft_strjoin(st, buffer);
    }
    line = get_line(st);
    st = get_st(st);
    return(line);
}

/* #include<stdio.h>
#include<fcntl.h>

int main(int ac, char **av)
{
    (void)ac;
    char *line = NULL;
    int fd = open(av[1], O_RDONLY);
    while((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    return(0);
} */
