def recursive_binary_search(elements, target, low, high):
    if low > high:
        return -1

    mid = (high + low) // 2

    if elements[mid] == target:
        return mid

    elif elements[mid] > target:
        return recursive_binary_search(elements, target, low, mid - 1)

    else:
        return recursive_binary_search(elements, target, mid + 1, high)


def iterative_binary_search(elements, target):
    low = 0
    high = len(elements) - 1
    while low <= high:
        mid = (high + low) // 2
        if elements[mid] == target:
            return mid
        elif elements[mid] > target:
            high = mid - 1
        else:
            low = mid + 1

    return -1
