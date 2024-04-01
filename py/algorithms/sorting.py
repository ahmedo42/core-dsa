# main idea: recursively sort the array and merge the results
def merge_sort(arr):
    def merge(arr1, arr2):
        result = []
        i = 0
        j = 0
        while i < len(arr1) and j < len(arr2):
            if arr1[i] <= arr2[j]:
                result.append(arr1[i])
                i += 1
            else:
                result.append(arr2[j])
                j += 1

        while i < len(arr1):
            result.append(arr1[i])
            i += 1

        while j < len(arr2):
            result.append(arr2[j])
            j += 1

        return result

    if len(arr) <= 1:
        return arr

    middle_idx = len(arr) // 2
    left_half = merge_sort(arr[:middle_idx])
    right_half = merge_sort(arr[middle_idx:])
    result = merge(left_half, right_half)
    return result

# main idea: partition the array recursively such that left < pivot < right
def quicksort(arr, left, right):
    def partition(arr, left, right, pivot_element):
        while left <= right:
            while arr[left] < pivot_element:
                left += 1
            while arr[right] > pivot_element:
                right -= 1
            if left <= right:
                arr[right], arr[left] = arr[left], arr[right]
                left += 1
                right -= 1

        return left

    if left >= right:
        return
    middle_idx = left + ((right - left) // 2)
    pivot_element = arr[middle_idx]
    pivot_idx = partition(arr, left, right, pivot_element)
    quicksort(arr, left, pivot_idx - 1)
    quicksort(arr, pivot_idx, right)
    return arr


# main idea: at iteration i, elements 0->i are sorted
def insertion_sort(arr):
    for i in range(1, len(arr)):
        j = i
        while j > 0 and arr[j - 1] > arr[j]:
            arr[j], arr[j - 1] = arr[j - 1], arr[j]
            j -= 1
    return arr

# main idea: bubble the largest element at the end of the array at each iteration
def bubble_sort(arr):
    for i in range(len(arr)):
        for j in range(i, len(arr)):
            if arr[j] < arr[i]:
                arr[j], arr[i] = arr[i], arr[j]
    return arr
