# Looking for max elem and placed it on needed position
import timeit


def sel_sort(array):
    count = 0
    change = 0

    for arr in range(len(array) - 1, 0, -1):
        pos_max = 0

        for idx in range(1, arr + 1):
            count += 1
            if array[idx] > array[pos_max]:
                pos_max = idx

        array[arr], array[pos_max] = array[pos_max], array[arr]
        change += 1

        # tmp = array[arr]
        # array[arr] = array[pos_max]
        # array[pos_max] = tmp

    print(str(count) + ' - сравнения')
    print(str(change) + ' - change')
    return array

alist = [54,26,93,17,77,31,44,55,20]
print(alist)
# print(sel_sort(alist))


def selection_sort(array):
    count = 0 # equals
    changes = 0

    for idx in range(0, len(array)):
        least = idx
        for i in range(idx + 1, len(array)):
            count += 1
            if array[i] < array[least]:
                least = i

        if idx != least:
            array[idx], array[least] = array[least], array[idx]
            changes += 1
    print(changes)
    print(count)
    return array


# timeit.timeit()
print(selection_sort(alist))



