from math import sqrt, acos, degrees

a = float(input('Comprimento cateto A: '))
b = float(input('Comprimento cateto B: '))

h = sqrt(a ** 2 + b ** 2)
ang = degrees(acos(a/h))

print(h)
