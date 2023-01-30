x1 = float(input("x1? "))
y1 = float(input("y1? "))
x2 = float(input("x2? "))
y2 = float(input("y2? "))

p1 = (x1, y1)
p2 = (x2, y2)

print("Point 1 :", p1)
print("Point 2 :", p2)

d = (x2 - x1) ** 2 + (y2 - y1) ** 2

print(f'A distância entre os dois pontos é {d} uc.')
