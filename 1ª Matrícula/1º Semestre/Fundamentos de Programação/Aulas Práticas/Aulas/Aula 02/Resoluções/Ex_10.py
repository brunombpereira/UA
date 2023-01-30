import math

print("Enter the coordinates in mm from the center of the board.")
x = float(input("x? "))
y = float(input("y? "))

if (x != 0):
    declive = y / x
    angulo = math.degrees(math.atan2(y, x))
else:
    if (y > 0):
        if(y ** 2 <= 225.5 ** 2 and y ** 2 >= 170 ** 2 or y ** 2 == 170 ** 2 or y ** 2 == 162 ** 2 or y ** 2 == 107 ** 2 or y ** 2 == 99 ** 2 or y ** 2 == 16 ** 2 or y ** 2 == 6.35 ** 2 ):
            print('Pontos: 0')
        elif (y ** 2 < 170 ** 2 and y ** 2 > 162 ** 2):
            print('Pontos: 40')
        elif(y ** 2 < 162 ** 2 and y ** 2 > 107 ** 2):
            print('Pontos: 20')
        elif(y ** 2 < 107 ** 2 and y ** 2 > 99 ** 2):
            print('Pontos: 60')
        elif(y ** 2 < 99 and y ** 2 > 16 ** 2):
            print('Pontos: 20')
        elif(y ** 2 < 16 ** 2 and y ** 2 > 6.35 ** 2):
            print('Pontos: 25')
        else:
            print('Pontos: 50')
    elif (y == 0):
        print('Pontos: 50')
    else:
        if(y ** 2 <= 225.5 ** 2 and y ** 2 >= 170 ** 2 or y ** 2 == 170 ** 2 or y ** 2 == 162 ** 2 or y ** 2 == 107 ** 2 or y ** 2 == 99 ** 2 or y ** 2 == 16 ** 2 or y ** 2 == 6.35 ** 2 ):
            print('Pontos: 0')
        elif (y ** 2 < 170 ** 2 and y ** 2 > 162 ** 2):
            print('Pontos: 6')
        elif(y ** 2 < 162 ** 2 and y ** 2 > 107 ** 2):
            print('Pontos: 3')
        elif(y ** 2 < 107 ** 2 and y ** 2 > 99 ** 2):
            print('Pontos: 9')
        elif(y ** 2 < 99 and y ** 2 > 16 ** 2):
            print('Pontos: 3')
        elif(y ** 2 < 16 ** 2 and y ** 2 > 6.35 ** 2):
            print('Pontos: 25')
        else:
            print('Pontos: 50')
            
a = -171
b = -153

POINTS = [8, 16, 7, 19, 3, 17, 2, 15, 10, 6, 13, 4, 18, 1, 20, 5, 12, 9, 14]

if (x ** 2 + y ** 2 <= 225.5 ** 2 and x ** 2 + y ** 2 >= 170 ** 2 or x ** 2 + y ** 2 == 170 ** 2 or x ** 2 + y ** 2 == 162 ** 2 or x ** 2 + y ** 2 == 107 ** 2 or x ** 2 + y ** 2 == 99 ** 2 or x ** 2 + y ** 2 == 16 ** 2 or x ** 2 + y ** 2 == 6.35 ** 2):
    print(f'Pontos: 0')
elif(x **2 + y ** 2 < 170 ** 2 and x ** 2 + y ** 2 > 162 ** 2):
    for i in range(len(POINTS)):

        if (a < angulo + 180 > b and x < 0):

            score = POINTS[i] * 2

            print(f'Pontos: {score}')
            break
        elif (a < angulo < b):
            score = POINTS[i] * 2

            print(f'Pontos: {score}')
            break
        else:
            a += 18
            b += 18 
elif(x ** 2 + y ** 2 < 162 ** 2 and x ** 2 + y ** 2 > 107 ** 2):
    for i in range(len(POINTS)):

        if (a < angulo + 180 > b and x < 0):

            score = POINTS[i]

            print(f'Pontos: {score}')
            break
        elif (a < angulo < b):
            score = POINTS[i]

            print(f'Pontos: {score}')
            break
        else:
            a += 18
            b += 18
elif (x ** 2 + y ** 2 < 107 ** 2 and x ** 2 + y ** 2 > 99 ** 2):
    for i in range(len(POINTS)):

        if (a < angulo + 180 > b and x < 0):

            score = POINTS[i] * 3

            print(f'Pontos: {score}')
            break
        elif (a < angulo < b):
            score = POINTS[i] * 3

            print(f'Pontos: {score}')
            break
        else:
            a += 18
            b += 18             
elif (x ** 2 + y ** 2 < 99 and x ** 2 + y ** 2 > 16 ** 2):
    for i in range(len(POINTS)):

        if (a < angulo + 180 > b and x < 0):

            score = POINTS[i]

            print(f'Pontos: {score}')
            break
        elif (a < angulo < b):
            score = POINTS[i]

            print(f'Pontos: {score}')
            break
        else:
            a += 18
            b += 18           
elif(x ** 2 + y ** 2 < 16 ** 2 and x ** 2 + y ** 2 > 6.35 ** 2):
    print('Pontos: 25')
else:
    print('Pontos: 50')