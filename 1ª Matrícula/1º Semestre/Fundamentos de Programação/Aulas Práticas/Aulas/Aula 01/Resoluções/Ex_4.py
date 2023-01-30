sec = int(input('Digite o número de segundos que deseja converter: '))

h = sec // 3600
m = sec % 3600 * 60 // 3600
s = sec % 3600 % 60
    
print(f'{sec} segundos corresponde a {h} h {m} min {s} sec. ')
