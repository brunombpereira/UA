def validate_number(number):
    if len(number) == 0:
        return False

    if number[0] == "+":
        number = number.replace("+", "")
    
    if len(number) >= 3:
        if number.isdigit() == True and int(number) >= 0:
            return True
        else:
            return False
    else:
        return False


def register_call(c):
    print('\n')

    while True:
        original_phone = input(' Telefone origem? ')

        if validate_number(original_phone) == True:
            destination_phone = input(' Telefone destino? ')

            while True:
                if validate_number(destination_phone) == True:
                    duration = input(' Duração? ')
                    
                    while True:
                        if duration.isdigit() == True and int(duration) >= 0:
                            c[original_phone] = [destination_phone, duration]
                            break
                        else:
                            duration = input(' Duração? ')
                    
                    break
                else:
                    destination_phone = input(' Telefone destino? ')

            print('\n')
            break
        else:
            pass
    
    return c


def read_files(r):
    file_name = input(" Ficheiro? ")

    while True:            
        try:
            file = open(f"{file_name}", "r", encoding='utf-8') 
            break
        except OSError:
            file_name = input(" Ficheiro? ")

    lines = file.readlines()

    for line in lines:
        lst = line.split()

        original_phone = lst[0]
        destination_phone = lst[1]
        duration = lst[2]

        r[original_phone] = [destination_phone, duration]

    file.close()
    
    return r


def list_clients(r):
    clients = []

    for i in r.keys():
        if i in clients:
            pass
        else:
            clients.append(i)
    
    return clients


def bill(c):
    client_number = input(' Cliente? ')
    precoT = 0

    while True:
        if validate_number(client_number) == True:
            print(f'Destino               Duração              Custo')

            for x in c.keys():
                if client_number == x :
                    if x[0][0] == 2:
                        cpm = 0.02
                        preco = (int(c[x][1]) / 60) * cpm
                        precoT += (int(c[x][1]) / 60) * cpm
                    elif x[0][0] == '+':
                        cpm = 0.8
                        preco = (int(c[x][1]) / 60) * cpm
                        precoT += (int(c[x][1]) / 60) * cpm
                    elif x[:2] == x[0][:2]:
                        cpm = 0.04
                        preco = (int(c[x][1]) / 60) * cpm
                        precoT += (int(c[x][1]) / 60) * cpm
                    else:
                        cpm = 0.1
                        preco = (int(c[x][1]) / 60) * cpm
                        precoT += int(c[x][1]) * cpm

                print("{:40s}{:2}{:>16.2f}".format(x, c[x][1], preco))

            print("{:>50}{:>8.2f}".format("Total :", precoT))

            break
        else:
            client_number = input(' Cliente? ')


def main():
    MENU = ' 1) Registar chamada\n 2) Ler ficheiro\n 3) Listar CLientes\n 4) Fatura\n 5) Terminar\n\n Opção? '
    c = {}

    while True:
        op = input(MENU)

        if op == "1":
            c = register_call(c)
        elif op == "2":
            c = read_files(c)
        elif op == "3":
            list_clients(c)
        elif op == "4":
            bill(c)
        elif op == "5":
            break

main()
