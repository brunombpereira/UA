from time import strftime

def menu():
    print('\n(I)nserir itens')
    print('(F)acturar')
    print('(S)air')
    while True:
        op = input('Opção? ').upper()
        if op not in ['I', 'F', 'S']:
            print('Opção não válida!', end=' ')
        else:
            break
    return op

def loadFicheiro(itens):
    with open('hipermercado.txt', 'r') as file:
        for line in file:
            item = line.strip().split(';')
            itens[item[0]] = (item[1],item[2],item[3],item[4])

def inserirItem(itens,compras):
    while True:
        codigo = input('Código item: ')
        if codigo == '0':
            break
        else:
            if codigo in itens:
                preco = float(itens[codigo][2]) + (float(itens[codigo][3][:-1])/100)*float(itens[codigo][2])
                if codigo not in compras:
                    compras[codigo] = [1, preco]
                else:
                    compras[codigo][0] += 1
                    compras[codigo][1] += preco
                print('{}: {:0.2f}€'.format(codigo[0], preco))
            else:
                print('Código inválido!', end=' ')

def venda(compras):
    with open('Vendas.txt', 'a') as file1:
        total = 0
        for item in compras:
            total += float(compras[item][1])
        t = strftime("%y-%m-%d %H:%M: ")
        file1.write(t + str(round(total, 2)) + '\n')

def stocks(compras):
    with open('StockOut.txt', 'a') as file2:
        for item in compras:
            file2.write('{}; {}\n'.format(item, compras[item][0]))

def main():
    itens = {}
    compras = {}
    loadFicheiro(itens)
    while True:
        op = menu()
        if op == 'I':
            inserirItem(itens,compras)
        if op == 'S':
            venda(compras)
            stocks(compras)
            print('Próximo cliente!')
            break

main()