#include <stdio.h>


int sum(int n)
{
    int sum = 0;
    sum += n;
    return sum;
}

int main()
{
    int s = sum(5);

    s = sum(2);
    
    printf("%d\n",s );
}