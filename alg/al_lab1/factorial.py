def factorial(base):
    result = 1

    for index in range(1, base + 1):
        result *= index

    return result

print(factorial(5))

def factorial_recursion(base):
    if base != 1:
        return base * factorial_recursion(base - 1)
    else:
        return 1

print(factorial_recursion(5))
