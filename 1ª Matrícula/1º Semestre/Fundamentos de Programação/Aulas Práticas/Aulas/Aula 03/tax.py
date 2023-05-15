def tax(r):
    if r <= 1000:
        return r * 0.1
    elif r <= 2000:
        return r * 0.2 - 100
    else:
        return r * 0.3 - 300


print(tax(4500))
print(tax(1500))
print(tax(500))
print(tax(2500))
print(tax(1000))
print(tax(2000))