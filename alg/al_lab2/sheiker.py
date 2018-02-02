alist = [54,26,93,17,77,31,44,55,20]

def sheik(array):
    left = 0
    right = len(array) - 1

    changes = 0

    while left <= right:
        for i in range(left, right):
            if array[i] > array[i+1]:
                array[i], array[i + 1] = array[i + 1], array[i]
                changes += 1
        right -= 1

        for i in range(right, left, -1):
            if array[i - 1] > array[i]:
                array[i], array[i - 1] = array[i - 1], array[i]
                changes += 1
        left += 1

    print(count)
    return array

print(sheik(alist))
