# André Almeida Oliveira
# 107637

def lerFicheiro(ficheiro,veiculos,clientes):
    with open(ficheiro, 'r') as file:
        for i in file:
            i = i.rstrip().split(';')
            if i[2] not in clientes:
                clientes[i[2]] = []
            clientes[i[2]].append(i[0])
            if i[0] not in veiculos:
                veiculos[i[0]] = (i[1],i[2])

def imprimirVeiculos(veiculos):
    for i in sorted(veiculos, key = lambda x: (veiculos[x][1],x)):
        print("{} : ('{}', '{}')".format(veiculos[i][1], i, veiculos[i][0]))

def imprimirVeiculosNIF(clientes):
    for i in clientes:
        print("{} : {}".format(i, clientes[i]))

def validarMatricula():
    while True:
        string = input('Matricula? ')
        stringList = string.rstrip().split('-')
        if len(stringList) == 3:
            if len(stringList[0]) == len(stringList[1]) == len(stringList[2]) == 2 and stringList[0].isdigit() and stringList[2].isdigit() and stringList[1].isalpha() and stringList[1].isupper():
                break
        else:
            print('Invalida!', end = ' ')
    return string

def validarTempo():
    while True:
        tempo = input('Duração? ')
        if tempo.isdigit() and int(tempo) > 0:
            break
        else:
            print('Invalida!', end = ' ')
    return tempo

def adicionarEstacionamento(estacionamentos):
    mat = validarMatricula()
    dur = validarTempo()
    if mat not in estacionamentos:
        estacionamentos[mat] = []
    estacionamentos[mat].append(dur)

def escreverFicheiro(estacionamentos):
    lst = []
    for b in estacionamentos:
        for i in estacionamentos[b]:
            lst.append((i, b))
    with open('parque.csv', 'w') as file1:
        for i in sorted(lst, key = lambda x: int(x[0]), reverse = True):
            file1.write("{};{}\n".format(i[0],i[1]))

def faturaNIF(veiculos,clientes,estacionamentos):
    while True:
        nif = input('NIF? ')
        if nif in clientes:
            break
        else:
            print('NIF inexistente!', end = ' ')
    print('Fatura NIF: {}'.format(nif))
    print('{:11s} {:11s} {:>11s} {:>8s}'.format('Matricula','Marca','Duracao','Custo'))
    total = 0
    for i in clientes[nif]:
        if i in estacionamentos:
            for d in estacionamentos[i]:
                custo = int(d) * 0.01
                total += custo
                print("{:11s} {:11s} {:>11s} {:>8.2f}".format(i, veiculos[i][0], d, custo))
    print("{:11s} {:11s} {:>11s} {:>8.2f}".format("Total:", "", "", total))

def menu():
    print("\nOpcoes disponiveis:")
    print('0 - Terminar')
    print('1 - Ler ficheiro de cliente')
    print('2 - Imprimir clientes ordenados')
    print('3 - Mostrar matriculas por Cliente')
    print('4 - Adicionar acesso ao parque')
    print('5 - Gravar acessos ao parque')
    print('6 - Gerar fatura para um cliente')
    while True:
        op = input('Opcao? ')
        if op not in ['0','1','2','3','4','5','6']:
            print("Opcao invalida!", end=" ")
        else:
            break
    return op

def main():
    veiculos = {}
    clientes = {}
    estacionamentos = {}
    while True:
        op = menu()
        if op == '0':
            print('Obrigado por usar software desenvolvido em FP!')
            break
        elif op == '1':
            lerFicheiro(input('Nome do ficheiro? '), veiculos, clientes)
            if len(veiculos) != 0:
                print('Foram importados {} registos.'.format(len(veiculos)))
            else:
                print('Não existem registos!')
        elif op == '2':
            if len(veiculos) != 0:
                print(imprimirVeiculos(veiculos))
            else:
                print('Não existem registos!')
        elif op == '3':
            if len(clientes) != 0:
                print(imprimirVeiculosNIF(clientes))
            else:
                print('Não existem clientes!')
        elif op == '4':
            adicionarEstacionamento(estacionamentos)
        elif op == '5':
            if len(estacionamentos) != 0:
                escreverFicheiro(estacionamentos)
                print('Ficheiro gravado com sucesso!')
            else:
                print('Não existem entradas no Parque!')
        elif op == '6':
            if len(clientes) != 0 and len(estacionamentos) != 0 and len(veiculos) != 0:
                faturaNIF(veiculos,clientes,estacionamentos)
            else:
                print('Dados insuficientes para criar fatura!')

main()