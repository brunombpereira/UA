pf = 20
pc = 24.95
imp = 0.23
spa = 0.20

profit = ((pc - spa) / (1 + imp)) - pf
total_imp = imp * pc

total_books = int(input('Quantos livros foram vendidos? '))

print(f'Sendo que foram vendidos {total_books} livros houve um lucro de {profit * total_books :.2f}€ e um total de {total_imp * total_books :.2f}€ em impostos.')
