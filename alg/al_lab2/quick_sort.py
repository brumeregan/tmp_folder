alist = [54, 26, 93, 17, 77, 31, 44, 55, 20]

def quicksort(xs):
    """Given indexable and slicable iterable, return a sorted list"""
    if xs: # if given list (or tuple) with one ordered item or more:
        pivot = xs[0]
        # below will be less than:
        below = [i for i in xs[1:] if i < pivot]
        # above will be greater than or equal to:
        above = [i for i in xs[1:] if i >= pivot]
        return quicksort(below) + [pivot] + quicksort(above)
    else:
        return xs # empty list

print(quicksort(alist))