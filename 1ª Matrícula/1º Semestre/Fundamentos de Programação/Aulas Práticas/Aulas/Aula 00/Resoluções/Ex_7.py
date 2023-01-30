print('---Cálculo da área e perímetro de um retângulo---\n')

height = float(input('Indique a altura do retângulo: '))
width = float(input('Indique a largura do retângulo: '))

area = height * width
perimetro = 2 * width + 2 * height

print(f'O retângulo de altura = {height} uc e largura = {width} uc tem uma área de {area} ua e um perímetro de {perimetro} uc.')