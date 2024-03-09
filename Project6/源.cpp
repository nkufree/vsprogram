#include<stdio.h>
void Sort(char a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (a[j] < a[j - 1])
            {
                char c = a[j];
                a[j] = a[j - 1];
                a[j - 1] = c;
            }
        }
    }
}
int main()
{
    printf("Input 10 characters:");
    char a[11] = {};
    for (int i = 0; i < 10; i++)
        a[i] = getchar();
    printf("Before sorting: %s\n", a);
    Sort(a, 10);
    printf("After sorting:  %s\n", a);
    return 0;
}
