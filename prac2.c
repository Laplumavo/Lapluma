#include <stdio.h>
#include <stdlib.h>
#include <time.h>


 
int main()
{
    int arr[10] = {0};
    int len = sizeof(arr) / sizeof(arr[0]);

    srand(time(NULL));

    for ( int i = 0; i < len; i++ )
    {
        int num = rand() % 10 + 1;
        int pd = tag1(arr, len, num);
        if (!pd)
        {
            arr[i] = num;
        }
        else
        {
            i--;
        }
    }

    for ( int i = 0; i < len; i++)
    {
        printf("%d\n",arr[i]);
    }

    return 0;
}

int tag1 (int arr[], int len, int num)
{
    for ( int i = 0; i < len; i++)
    {
    if (arr[i] == num)
    {
        return 1;
    }
    return 0;
    }
}