array = [12, 15, 16, 20, 17, 13]

def iterate_method(arr):
    print(arr)
    new_array = []
    length = len(arr) - 1
    for idx in range(length, -1, -1):
        new_array.append(arr[idx])

    print(new_array)

iterate_method(array)

def recursive(arr, arr_length):
    print(str(arr[arr_length]) + " : " + str(arr_length))
    if arr_length > 0:
        recursive(arr, arr_length - 1)
    else:
        return

recursive(array, len(array) - 1)
