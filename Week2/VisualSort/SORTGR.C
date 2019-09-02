/*                                                           */
/*  SORTGR.C  :  Show sort process in graphic                */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <alloc.h>
#include <string.h>
#include <graphics.h>
#include <bios.h>
#include <stdlib.h>
#include <limits.h>
#include "hardcopy.h"

#define SIZE     160

int *base;

int *set_array(int *a, int n)
    {
    int i, r1, r2, t;
    for (i = 0; i < n; i++)
        a[i] = i;
    for (i = 0; i < 1000; i++)
        {   /* Shuffling */
        r1 = random(n);
        r2 = random(n);
        t = a[r1];
        a[r1] = a[r2];
        a[r2] = t;
        }
    return a;
    }

void sort_grp(int *a, int pos)
    {
    int x, y, i;
    char *rem[] =
	{ "        (a)",
	  "        (b)",
	  "        (c)",
	  "        (d)",
	  "        (e)",
	  "        (f)" };
    if (pos > 5) return;
    x = (pos % 3) * (SIZE + 30);
    y = (pos / 3) * (SIZE + 50);  /* for Hercules (size + 10) */
    rectangle(x, y, x+SIZE, y+SIZE);
    outtextxy(x, y+SIZE+5, rem[pos]);  /* for hercules y+size */
    for (i = 0; i < SIZE; i++)
        {
        putpixel(x+i, y+SIZE-a[i], WHITE);
        putpixel(x+i, y+SIZE-a[i]-1, WHITE);
        putpixel(x+i+1, y+SIZE-a[i], WHITE);
        putpixel(x+i+1, y+SIZE-a[i]-1, WHITE);
        }
    }

void g_select_sort(int a[], int n)
    {
    int min;
    int minindex;
    int i, j;
    int p = 0;

    sort_grp(a, p++);
    for (i = 0; i < n-1; i++)
	{
	if (i+2 == n*p/5)
	    sort_grp(a, p++);
	minindex = i;
	min = a[i];
	for (j = i + 1; j < n; j++)
	    {
	    if (min > a[j])
		{
		min = a[j];
		minindex = j;
		}
	    }
        a[minindex] = a[i];
        a[i] = min;
        }
    }

void g_insert_sort(int a[], int n)
    {
    int i, j, t;
    int p = 0;

    sort_grp(a, p++);
    for (i = 1; i < n; i++)
	{
	t = a[i];
	j = i;
	while (a[j-1] > t && j > 0)
	    {
	    a[j] = a[j-1];
	    j--;
	    }
	a[j] = t;
	if (i+1 == n*p/5)
	    sort_grp(a, p++);

	}
    }

void g_bubble_sort(int a[], int n)
    {
    int i, j, t;
    int p = 0;

    sort_grp(a, p++);
    for (i = 0; i < n-1; i++)
	{
	if (i == n*p/5)
	    sort_grp(a, p++);
	for (j = 0; j < n-i-1; j++)
	    {
	    if (a[j] > a[j+1])
		{
		t = a[j];
		a[j] = a[j+1];
                a[j+1] = t;
                }
            }
        }
    sort_grp(a, p);
    }

void g_shell_sort(int a[], int n)
    {
    int i, j, k, h, v;
    int p = 0;
    for (h = n/2; h > 0; h /= 2)
	{
	if (h == SIZE || h == SIZE/4 || h == SIZE/16 || h == SIZE/32 ||
	    h == SIZE/64 || h == SIZE/128)
	    sort_grp(a, p++);
	for (i = 0; i < h; i++)
	    {
	    for (j = i+h; j < n; j += h)
		{
		v = a[j];
		k = j;
		while (k > h-1 && a[k-h] > v)
		    {
		    a[k] = a[k-h];
		    k -= h;
		    }
		a[k] = v;
		}
	    }
	}
    sort_grp(a, p++);
    }

void g_quick_sort(int a[], int n)
    {
    int v, t;
    int i, j;
    static int p = 0;
    if (n > 1)    /* terminal condition */
	{
	if ((n > 12 && n < 20) || n == SIZE) sort_grp(base, p++);
	v = a[n-1];
	i = -1;
	j = n-1;
	while (1)      /* partition */
	    {
	    while (a[++i] < v);
	    while (a[--j] > v);
	    if (i >= j) break;
	    t = a[i];
	    a[i] = a[j];
	    a[j] = t;
	    }
	t = a[i];
	a[i] = a[n-1];
	a[n-1] = t;
	g_quick_sort(a, i);
	g_quick_sort(a+i+1, n-i-1);
	}
    }

unsigned bits(unsigned x, int k, int j)
    {
    return (x >> k) & ~(~0 << j);
    }

void g_radix_exchange_sort(int a[], int n, int b)
    {
    int t, i, j;
    static int p = 0;
    if (n > 1  &&  b >= 0)
        {
        if (b < 6 && b > 3) sort_grp(base, p++);
        i = 0;
        j = n-1;
        while (i != j)
            {
            while (bits(a[i], b, 1) == 0 && i < j) i++;
            while (bits(a[j], b, 1) != 0 && i < j) j--;
            t = a[i];
            a[i] = a[j];
            a[j] = t;
            }
        if (bits(a[n-1], b, 1) == 0) j++;
        g_radix_exchange_sort(a, j, b-1);
        g_radix_exchange_sort(a+j, n-j, b-1);
        }
    }

#define W  8
#define M  1
#define MV (1 << M)

void g_straight_radix_sort(int a[], int n)
    {
    int i, j, pass;
    int *b, *count;
    int p = 0;
    b = (int*)malloc(sizeof(int)*n);
    count = (int*)malloc(sizeof(int)*MV);
    for (pass = 0; pass < W/M; pass++)
        {
        if (pass == 0 || pass == 3 || pass == 5 || pass == 6 || pass == 7)
            sort_grp(a, p++);
        for (j = 0; j < MV; j++)
            count[j] = 0;
        for (i = 0; i < n; i++)
            count[bits(a[i], pass*M, M)]++;
        for (j = 1; j < MV; j++)
            count[j] = count[j] + count[j-1];
        for (i = n-1; i >= 0; i--)
            b[--count[bits(a[i], pass*M, M)]] = a[i];
        for (i = 0; i < n; i++)
            a[i] = b[i];
        }
    sort_grp(a, p++);
    free(b);
    free(count);
    }

void g_merge_sort(int a[], int n)
    {
    int i, j, k, first, second, size;
    int *b;
    int p = 0;
    b = (int*)malloc(sizeof(int)*n);
    for (size = 1; size < n; size <<= 1)
        {
        first = -2 * size;
        second = first + size;
        while (second+size < n)
            {
            first = second + size;
            second = first + size;
            i = first;
            j = second;
            k = first;
            while (i < first+size || (j < second+size && j < n))
                {
                if (a[i] <= a[j])
                    {
                    if (i < first+size)
                        b[k++] = a[i++];
                    else
                        b[k++] = a[j++];
                    }
                else
                    {
                    if (j < second+size && j < n)
                        b[k++] = a[j++];
                    else
                        b[k++] = a[i++];
                    }
                }
            }
        for (i = 0; i < n; i++)
            a[i] = b[i];   /* memcpy(a, b, sizeof(int)*n); */
        if (size == 1 || size == 4 || size == 16 || size == 64 ||
            size == 32 || size == 128) sort_grp(a, p++);
        }
    free(b);
    sort_grp(a, p++);
    }

void upheap(int a[], int k)
    {
    int v;
    v = a[k];
    a[0] = INT_MAX;  /* sentinel */
    while (a[k/2] <= v)
        {
        a[k] = a[k/2];
        k /= 2;
        }
    a[k] = v;
    }

void insert(int a[], int *n, int v)
    {
    a[++(*n)] = v;
    upheap(a, *n);
    }

void downheap(int a[], int n, int k)
    {
    int i, v;
    v = a[k];
    while (k <= n/2)
        {
        i = k<<1;
        if (i < n && a[i] < a[i+1]) i++;
        if (v >= a[i]) break;
        a[k] = a[i];
        k = i;
        }
    a[k] = v;
    }

int extract(int a[], int *n)
    {
    int v = a[1];
    a[1] = a[(*n)--];
    downheap(a, *n, 1);
    return v;
    }

void g_heap_sort(int a[], int n)
    {    /* top-down heap sort */
    int i;
    int p = 0;
    int hn = 0;
    for (i = 1; i <= n; i++)
        {
        if (i == 1 || i == n/2 || i == n) sort_grp(a+1, p++);
        insert(a, &hn, a[i]);
        }
    for (i = hn; i >= 1; i--)
        {
        if (i == 2*n/3 || i == 1*n/3) sort_grp(a+1, p++);
        a[i] = extract(a, &hn);
        }
    sort_grp(a+1, p++);
    }

void main(void)
    {
    int *a;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\tc\\bgi");
    if (graphresult() != grOk)
        {
        printf("\nGraphic system error!");
        return;
	}
    if ((a = (int*)malloc(sizeof(int)*(SIZE+1))) == NULL)
	{
	printf("\nOut of memory");
	return;
	}
    base = a;
    srand(16370);
    a = set_array(a, SIZE);
    g_select_sort(a, SIZE);
    wait_hardcopy(LPT1);

    cleardevice();
    a = set_array(a, SIZE);
    g_insert_sort(a, SIZE);
    wait_hardcopy(LPT1);

    cleardevice();
    a = set_array(a, SIZE);
    g_bubble_sort(a, SIZE);
    wait_hardcopy(LPT1);

    cleardevice();
    a = set_array(a, SIZE);
    g_quick_sort(a, SIZE);
    wait_hardcopy(LPT1);

    cleardevice();
    a = set_array(a, SIZE);
    g_shell_sort(a, SIZE);
    wait_hardcopy(LPT1);

    cleardevice();
    a = set_array(a, SIZE);
    g_radix_exchange_sort(a, SIZE, 15);
    wait_hardcopy(LPT1);

    cleardevice();
    a = set_array(a, SIZE);
    g_straight_radix_sort(a, SIZE);
    wait_hardcopy(LPT1);

    cleardevice();
    a = set_array(a, SIZE);
    g_merge_sort(a, SIZE);
    wait_hardcopy(LPT1);

    cleardevice();
    a = set_array(a+1, SIZE);
    g_heap_sort(a, SIZE);
    wait_hardcopy(LPT1);

    closegraph();
    }





