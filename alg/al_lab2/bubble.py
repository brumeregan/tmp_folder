alist = [54,26,93,17,77,31,44,55,20]


def bubble(array):
    comparison = 0
    changes = 0

    for idx in range(len(array) - 1, 0, -1):
        for i in range(0, idx):
            comparison += 1
            if array[i] > array[i + 1]:
                changes += 1
                array[i+1], array[i] = array[i], array[i + 1]
    print('comparison')
    print(comparison)

    print('changes')
    print(changes)
    return array

print(bubble(alist))

