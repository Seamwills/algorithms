/*
 * INSERTION-SORT, sort an array of length n
 *
 * INSERTION-SORT(A)
 *  for i = 2 to A.length
 *      key = A[i]
 *      // Insert A[i] into the sorted sequence A[1..i-1]
 *      j = i - 1
 *      while j > 0 and A[j] > key
 *          A[j+1] = A[j]
 *          j = j - 1
 *      A[j+1] = key
 *
 */

/*
 * Description:
 * For the second element all throught to the last element A[i],
 * set it to key: key = A[i]
 *
 * Insert the key element to the already sorted sequence A[1..i-1],
 * after the last element was inserted into the sorted sequence,
 * the entire sequence was sorted.
 *
 */

void
insertion_sort(int A[], int n)
{
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = A[i];
        // Insert A[i] into the sorted sequence A[0..i-1]
        j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j -= 1;
        }
        A[j + 1] = key;
    }
}
