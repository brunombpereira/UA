v1 = float(input('Qual a velocidade média feita no 1º percurso em Km/h? '))
v2 = float(input('Qual a velocidade média feita no 2º percurso em Km/h? '))

vmt = 2 * v2 * v1 / (v2 + v1)

print(f'Tendo em conta a velocidade média feita no 1º e 2º percursos o automóvel teve na viagem completa uma velocidade média de {vmt} 50 Km/h.')