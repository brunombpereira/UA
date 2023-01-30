x1 = float(input("number? "))
x2 = float(input("number? "))
x3 = float(input("number? "))

if(x1 > x2 > x3):
    print(f'Maximum: ', x1)
elif(x1 < x2 < x3):
    print(f'Maximum: ', x3)
elif(x1 == x2 == x3):
    print('Os números são iguais.')
else:
    print('Maximum: ', x2)
