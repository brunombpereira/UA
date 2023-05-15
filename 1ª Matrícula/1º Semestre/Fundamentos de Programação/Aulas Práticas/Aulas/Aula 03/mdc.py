def mdc(a, b):
    assert a > 0
    assert b > 0
    r = a % b
    if r == 0:
        return b
    else:
        return mdc(b, r)


def main():
    print(mdc(10, 5))    # 5
    print(mdc(10, 3))    # 1
    print(mdc(10, 2))    # 2
    print(mdc(10, 1))    # 1
    print(mdc(15, 3))    # 3

    x1 = int(input("x1: "))
    y1 = int(input("y1: "))
    print(mdc(x1, y1))


if __name__ == "__main__":
    main()