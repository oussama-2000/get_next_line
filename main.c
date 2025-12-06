// #include "get_next_line_bonus.h"
#include "get_next_line.h"

int main(void)
{
    int fd1 = open("splinta.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);

    char *result;

    while ((result = get_next_line(fd1)))
    {
        printf("%s", result);
        free(result);
    }
   
    // result = get_next_line(fd1);
    // printf("%s",result);
    // free(result);

    // result = get_next_line(fd2);
    // printf("%s",result);
    // free(result);

    // result = get_next_line(fd1);
    // printf("%s",result);
    // free(result);
}