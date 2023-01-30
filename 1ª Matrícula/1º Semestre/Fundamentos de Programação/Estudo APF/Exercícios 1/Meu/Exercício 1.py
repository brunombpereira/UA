def menu():
    print('\nOpções disponíveis:')
    print('1) Registar chamada')
    print('2) Ler ficheiro')
    print('3) Listar clientes')
    print('4) Fatura')
    print('5) Terminar')
    while True:
        op = input('Opção? ')
        if op not in ['1','2','3','4','5']:
            print('Opção não válida!')
        else:
            break
    return op

def validarNumero(msg):
    while True:
        num = input(msg)
        if len(num) >= 3 and len(num) <= 10:
            if num[0] == '+' and num[1:].isdigit() and len(num) > 3:
                break
            elif num.isdigit():
                break
            else:
                print('Número inválido!', end=' ')
        else:
            print('Número inválido!', end=' ')
    return num

def registarChamada(chamadas):
    to = validarNumero('Telefone origem? ')
    td = validarNumero('Telefone destino? ')
    d = input('Duração (s)? ') 
    chamadas.append([to,td,d])

def lerFicheiro(chamadas):
    with open(input('Ficheiro? '), 'r') as file:
        for line in file:
            chamada = line.strip().split()
            chamadas.append(chamada)

def listarClientes(chamadas, clientes):
    for i in chamadas:
        if i[0] not in clientes:
            clientes.append(i[0])
    print(sorted(clientes))

def main():
    chamadas = []
    clientes = []
    while True:
        op = menu()
        if op == '1':
            registarChamada()
        if op == '2':
            lerFicheiro(chamadas)
        if op == '3':
            listarClientes(chamadas, clientes)
        if op == '5':
            print('Terminado!')
            break

main()