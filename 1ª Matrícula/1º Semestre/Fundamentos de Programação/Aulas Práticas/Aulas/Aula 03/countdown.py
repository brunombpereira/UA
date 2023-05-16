def countdown(n):
    print(n)
    if n > 0:
        countdown(n - 1)


def main():
    countdown(5)
    print()
    countdown(10)
    print()
    countdown(0)
    print()
    countdown(-1)


if __name__ == "__main__":
    main()
