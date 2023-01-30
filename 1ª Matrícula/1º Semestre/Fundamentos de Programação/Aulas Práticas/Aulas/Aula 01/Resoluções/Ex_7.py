a = int(input("Número de andares? ")) #andares                              
floor_dweller = int(input("Número de moradores em cada andar? "))
total_residents = floor_dweller * a
times = int(input("Número de vezes que sobe e desce por dia? ")) #viagens
height = float(input("Qual é  altura de cada piso em metros? "))
velocity = int(input("Qual é a velocidade do elevador em m/s? "))
time = int(input("Quantos dias é que o elevador esteve em funcionamento?"))


dist = time * (a*(a+1)/2) * 2 * floor_dweller * height * times
h = (time * (height * (2*total_residents) / velocity) / 3600)

print("Distância total: ", dist)
print("Número de horas: ", h)