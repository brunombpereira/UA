s = int(input('Duração da chamada por segundos: '))

initial_value = 0.12
value_per_second = initial_value / 60

if(s <= 60):
    print(f'O custo da chamada foi de {initial_value}€')
else:
    s -= 61
    total_value = initial_value + s * value_per_second
    print(f'O custo da chamada foi de {total_value :.2}€')
