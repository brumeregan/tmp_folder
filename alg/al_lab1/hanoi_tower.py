tower = [3, "A", "B", "C"]

def hanoi_tower_rec(num, first, second, third):
    if num < 0:
        return False

    if num == 1:
        print(first + '->' + third)
    else:
        hanoi_tower_rec(num - 1, first, third, second)
        hanoi_tower_rec(1, first, second, third)
        hanoi_tower_rec(num - 1, second, first, third)

    return 0

def hanoi_r(n, src, dest, temp):
    if n == 0:
        return False

    hanoi_r(n - 1, src, temp, dest)
    print(src + '->' + dest)
    hanoi_r(n - 1, temp, dest, src)

hanoi_r(3, "A", "C", "B")
print("******************")
hanoi_tower_rec(3, "A", "B", "C")

def hanoi(num, first, second, third):


    return 0

