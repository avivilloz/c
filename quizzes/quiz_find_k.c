/*****************************************************************************
Title: quiz_find_k 
Description: learn quiz_find_k
******************************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

/*****************************************************************************/

void Swap(int arr[], size_t i, size_t j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int FindKSmallestElem(int arr[], size_t size, size_t K)
{
    size_t i = 0, j = 0, k = 0;
    int k_smallest_elem = 0;
    int *buff = malloc(sizeof(int) * K);
    if (NULL == buff)
    {
        return -1;
    }    

    for (; i < size; ++i)
    {
        if (j != K)
        {
            k = j;
            buff[j] = arr[i];
            ++j;   
        }
        else if (buff[K - 1] > arr[i])
        {
            k = K - 1;
            buff[K - 1] = arr[i];
        }

        for (; k > 0 && buff[k] < buff[k - 1]; --k)
        {
            Swap(buff, k, k - 1);
        }
    }

    k_smallest_elem = buff[K - 1];

    free(buff);

    return k_smallest_elem;
}

int main(void)
{
    int arr[5] = {4,6,2,8,1};

    printf("%d\n", FindKSmallestElem(arr, 5, 4));

	return 0;
}

/*****************************************************************************/

