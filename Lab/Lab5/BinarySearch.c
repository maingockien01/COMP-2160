#include<stdio.h>
#include<string.h>
#include<assert.h>

#define ARRAY_MAX_N 10

typedef int DataType;

int n;
DataType t;

DataType array[ARRAY_MAX_N];

int binarySearch (DataType t);
int isSorted ();

int main () {
    while (scanf("%d %d", &n, &t) != EOF) {
        int i;
        if (n > ARRAY_MAX_N) {
            printf("Error: n limit is %d.\n", ARRAY_MAX_N);
            continue;
        } else if (n <= 0) {
            printf("Error: n must be greater than 0.\n");
            continue;
        }

        for (i = 0; i < n; i ++) {
            array[i] = 10 * i;
        };

        for (i = 0; i < n-1; i ++) {
            assert(binarySearch(10*i) == i);
            assert(binarySearch(10*i - 5) == -1);
        }

        assert(binarySearch(10*(n-1)) == i);
        assert(binarySearch(10*(n-1) - 5) == -1);

        printf(" %d\n", binarySearch(t) );
        //reset search
        n = 0;
        t = -1;
    }
}

int binarySearch (DataType t) {
    if (isSorted() == 0) {
        return -1;
    }

    int start = 0 , end = n-1;
    int mid;
    
    while (start < end) {
        mid = (start+end)/2;

        if (array[mid] < t) {
            start = mid + 1;
        } else if (array[mid] == t) {
            assert(0 <= mid && mid < n && array[mid] == t);
            return mid;
        } else {
            end = mid - 1;
        }
    }

    assert((end < 0 || array[end] < t) && (end + 1 >= n || array[end+1] > t));
    return -1;
}

int isSorted () {
    int i;
    for (i = 0; i < n-1; i ++) {
        if (array[i] > array[i+1]) {
            return 0;
        }
    }
    return 1;
}
