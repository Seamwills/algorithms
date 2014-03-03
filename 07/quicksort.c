/*
 * QUICKSORT, sort array A from subscript p to r
 *
 * QUICKSORT(A, p, r)
 *  if p < r
 *      q = PARTITION(A, p, r)
 *      QUICKSORT(A, p, q-1)
 *      QUICKSORT(A, q+1, r)
 *
 * PARTITION(A, p, r)
 *  x = A[r]
 *  i = p-1
 *  for j = p to r-1
 *      if A[j] <= x
 *          i = i + 1
 *          exchange A[i] with A[j]
 *  exchange A[i+1] with A[r]
 *  return i + 1
 *
 */

/*
 * Description:
 * on subarray A[p..r], PARTITION maintains 4 rigion:
 *
 * A[r] = x;
 * Elements in A[p..i] <= x; Elements in A[i+1..j-1] > x;
 * Elements in subarray A[j..r-1] can be either case.
 *
 * i  pj                   r
 *    2  8  7  1  3  5  6  4
 *
 *    p  i        j        r   
 *    2  1  7  8  3  5  6  4
 *
 */

void
quicksort(int A[], int p, int r)
{
    int q;

    if (p < r) {
        q = partition(A, p, r);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}

int
partition(int A[], int p, int r)
{
    int i, j;
    int x;

    x = A[r];
    i = p - 1;

    for (j = p; j <= r - 1; j++) {
        if (A[j] <= x) {
            i = i + 1;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[r]);

    return i + 1;
}
