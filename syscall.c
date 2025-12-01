#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


char *get(int fd)
{


    char content[100];
    char *line;

    line = malloc(100);
    
    read(fd,content,100);
    int i = 0;
    while(content[i] != '\n' && i < 20)
    {
        line[i] = content[i];
        i++;
    }
    return line;
}   

int main()
{
    int fd = open("file.txt" , O_RDONLY);

    char *result = get(fd);
    printf("%s",result);
    result = get(fd);
    printf("%s",result);
}