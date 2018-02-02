def get_pow(base, power):
    result = 1

    for index in range(0, power):
        result *= base

    return result

print(get_pow(2, 10))

def get_pow_recursion(base, power):
    if power == 0:
        return 1

    if power != 1:
        return base * get_pow_recursion(base, power - 1)
    else:
        return base


print(get_pow_recursion(2, 1))
