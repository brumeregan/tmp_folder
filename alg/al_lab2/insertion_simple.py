alist = [54,26,93,17,77,31,44,55,20]


def ins_sort(array):
    for idx in range(1, len(array)):
        current = array[idx]
        while idx > 0 and array[idx - 1] > current:
            array[idx] = array[idx - 1]
            idx = idx - 1

        array[idx] = current
    return array


print(alist)
print(ins_sort(alist))