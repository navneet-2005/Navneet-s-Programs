#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ================= BUBBLE SORT ================= */
int bubbleSort(int *a, int n)
{
    int count = 0, i, j, flag, t;

    for(i = 0; i < n - 1; i++)
    {
        flag = 0;
        for(j = 0; j < n - i - 1; j++)
        {
            count++;
            if(a[j] > a[j+1])
            {
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
                flag = 1;
            }
        }
        if(flag == 0)
            break;
    }
    return count;
}

/* ================= INSERTION SORT ================= */
int insertionSort(int *arr, int n)
{
    int count = 0;

    for(int i = 1; i < n; i++)
    {
        int value = arr[i];
        int j = i - 1;

        while(j >= 0 && (++count && arr[j] > value))
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = value;
    }
    return count;
}

/* ================= SELECTION SORT ================= */
int selectionSort(int *a, int n)
{
    int count = 0;

    for(int i = 0; i < n - 1; i++)
    {
        int min = i;

        for(int j = i + 1; j < n; j++)
        {
            count++;
            if(a[j] < a[min])
                min = j;
        }

        if(min != i)
        {
            int t = a[i];
            a[i] = a[min];
            a[min] = t;
        }
    }
    return count;
}

/* ================= PLOTTER ================= */
void plotter()
{
    int *arr, n, count;
    srand(time(NULL));

    FILE *fb1, *fb2, *fb3;
    FILE *fi1, *fi2, *fi3;
    FILE *fs1, *fs2, *fs3;

    fb1 = fopen("BUBBLEBEST.txt", "w");
    fb2 = fopen("BUBBLEWORST.txt", "w");
    fb3 = fopen("BUBBLEAVG.txt", "w");

    fi1 = fopen("INSERTIONBEST.txt", "w");
    fi2 = fopen("INSERTIONWORST.txt", "w");
    fi3 = fopen("INSERTIONAVG.txt", "w");

    fs1 = fopen("SELECTIONBEST.txt", "w");
    fs2 = fopen("SELECTIONWORST.txt", "w");
    fs3 = fopen("SELECTIONAVG.txt", "w");

    if(!fb1 || !fb2 || !fb3 || !fi1 || !fi2 || !fi3 || !fs1 || !fs2 || !fs3)
    {
        printf("File error\n");
        exit(1);
    }

    n = 10;

    while(n <= 30000)
    {
        arr = (int*)malloc(sizeof(int)*n);
        if(arr == NULL)
        {
            printf("Memory error\n");
            exit(1);
        }

        /* -------- WORST CASE -------- */
        for(int i = 0; i < n; i++)
            arr[i] = n - i;

        fprintf(fb2, "%d\t%d\n", n, bubbleSort(arr,n));
        fprintf(fi2, "%d\t%d\n", n, insertionSort(arr,n));
        fprintf(fs2, "%d\t%d\n", n, selectionSort(arr,n));

        /* -------- BEST CASE -------- */
        for(int i = 0; i < n; i++)
            arr[i] = i + 1;

        fprintf(fb1, "%d\t%d\n", n, bubbleSort(arr,n));
        fprintf(fi1, "%d\t%d\n", n, insertionSort(arr,n));
        fprintf(fs1, "%d\t%d\n", n, selectionSort(arr,n));

        /* -------- AVERAGE CASE -------- */
        for(int i = 0; i < n; i++)
            arr[i] = rand() % n;

        fprintf(fb3, "%d\t%d\n", n, bubbleSort(arr,n));
        fprintf(fi3, "%d\t%d\n", n, insertionSort(arr,n));
        fprintf(fs3, "%d\t%d\n", n, selectionSort(arr,n));

        if(n < 10000)
            n *= 10;
        else
            n += 10000;

        free(arr);
    }

    fclose(fb1); fclose(fb2); fclose(fb3);
    fclose(fi1); fclose(fi2); fclose(fi3);
    fclose(fs1); fclose(fs2); fclose(fs3);

    printf("All data files generated!\n");
}

/* ================= TESTER ================= */
void tester()
{
    int *arr, n;

    printf("Enter number of elements:\n");
    scanf("%d", &n);

    arr = (int*)malloc(sizeof(int)*n);

    printf("Enter elements:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nOriginal Array:\n");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    /* Choose algorithm */
    int choice;
    printf("\n\n1.Bubble  2.Insertion  3.Selection\n");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1: bubbleSort(arr,n); break;
        case 2: insertionSort(arr,n); break;
        case 3: selectionSort(arr,n); break;
        default: printf("Invalid\n");
    }

    printf("\nSorted Array:\n");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");

    free(arr);
}

/* ================= MAIN ================= */
int main()
{
    int key;

    while(1)
    {
        printf("\nMENU\n1.TEST\n2.PLOT\n0.EXIT\n");
        scanf("%d",&key);

        switch(key)
        {
            case 1: tester(); break;
            case 2: plotter(); break;
            case 0: exit(0);
            default: printf("Invalid choice\n");
        }
    }
}
