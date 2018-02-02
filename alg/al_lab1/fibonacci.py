def fibonacci(n):
    result = 1
    f1 = 1
    f2 = 1
    if n == 0:
        return 0
    for index in range(2, n):
        result = f1 + f2
        f1 = f2
        f2 = result

    return result

print(fibonacci(3))

def fibonacci_recursive(n):
    if n == 0:
        return 0

    if n == 1:
        return 1
    else:
        return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2)

print(fibonacci_recursive(3))
