def max2(x, y):
    return x if x >= y else y


def max3(x, y, z):
    return max2(x, max2(y, z))


def main():
    print(max2(2, 3))
    print(max2(-3, -2))
    print(max2(3, 3))


main()
