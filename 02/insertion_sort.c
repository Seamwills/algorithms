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
