def loadDataBase(fname, produtos):
    # A estrutura try: except: evita o programa parar de funcionar caso seja introduzido o nome de um ficheiro inválido ou inexistente quando se faz " python3 shop.py "name_file" "

    try:
        file = open(f"{fname}", "r", encoding='utf-8')           # Abre o ficheiro em modo de leitura e com " encoding='utf-8' " para aceitar acentuação
    except OSError:
        print("Error opening file")
        return

    lines = file.readlines()

    # Neste bloco por cada linha cria-se uma lista em que cada posição corresponde ao que está escrito entre os ";".
    # Neste bloco cria-se um dicionário com todos os produtos existentes no ficheiro, sendo q a "key" = "CODIGO" e o "value" = "nome, seccao, preço_base, taxa"

    for line in lines:
        lst = line.split(";")
       
        if(lst[0] == "CODIGO"):
            pass
        else:
            codigo = lst[0]
            nome = lst[1]
            seccao = lst[2]
            preço_base = float(lst[3])
            taxa = int(lst[4][:-2])
            produtos[codigo] = (nome, seccao, preço_base, taxa)

    file.close()          # Nesta estrutura de abrir ficheiros é-se obrigado a fechar o ficheiro para não haver problemas, pois o ficheiro com esta estrutura não fecha automaticamente 


def registaCompra(produtos):
    carrinho = {}          # Cria-se um dicionário para registar cada produto que se pede num só sítio
    a = "1"
    while a != "":
        a = input("Code? ")
        x = a.split()          # Faz-se uso da função ".split()" para se puder dar o valor da quantidade que se quer comprar de um certo produto, ou seja, o "CODIGO" não é a única coisa permita
        if(len(x) > 1):          # Caso em que é introduzido uma quantidade para o produto
           if x[0] in produtos:
               b = float(produtos[x[0]][-2]) * ((float(produtos[x[0]][-1])/ 100) + 1) * float(x[1]) # Preço final
               print("{} {} {:.2f}".format(produtos[x[0]][0],x[1],b))
               if not x[0] in carrinho:
                   carrinho.update({x[0] : x[1]})         # x[0] corresponde ao "CODIGO" e x[1] corresponde à quantidade
               else:
                   carrinho[x[0]] += int(x[1])
        elif(len(x) == 1):       # Caso em que é introduzido apenas o "CODIGO" do produto
           if a in produtos:
               b = float(produtos[a][2]) + (float(produtos[a][3]) / 100) * float(produtos[a][2])
               print("{} {} {:.2f}".format(produtos[a][0],"1",b))
               if not a in carrinho:
                   carrinho.update({a :1})
               else:
                   carrinho[a] += 1
        else:
           pass     # Situações em que são introduzidos valores inválido ex: -5; ceb; ...
    return carrinho

def fatura(produtos, compra):
    b = i = l = 0         # A variável "b" corresponde ao total bruto, a variável "i" corresponde ao total iva, a variável "l" corresponde ao total líquido
    categoria = []        # Cria-se uma lista para armazenar cada registo de compra

    # Por cada valor em compra

    for k in compra:
        if k in categoria:
            continue
        print (produtos[k][1])
        for w in compra:
            if produtos[w][1] == produtos [k][1]:

                p = float(produtos[w][-2]) * ((float(produtos[w][-1])/ 100) + 1) * float(compra[w])       # Preço Final
                l = l + p
                b = b + float(produtos[w][-2]) * float(compra[w])
                i = i + float(produtos[w][-2]) * (float(produtos[w][-1]) / 100) * float(compra[w])
                print("{:<3} {:>20} ({:2d}%) {:>10.2f}".format(compra[w],produtos[w][0],produtos[w][3],p))
                categoria.append(w)
    print("{:>55} {:>10.2f}".format("Total Bruto:",b))
    print("{:>55} {:>10.2f}".format("Total Iva:",i))
    print("{:>55} {:>10.2f}".format("Total Liquido:",l))

def main(args):
    # produtos guarda a informação da base de dados numa forma conveniente.

    produtos = {'p1': ('Ketchup.', 'Mercearia Salgado', 1.59, 0.23)}

    # Carregar base de dados principal

    loadDataBase("produtos.txt", produtos)

    # Juntar bases de dados opcionais (Não altere)

    for arg in args:
        loadDataBase(arg, produtos)

    # Use este código para mostrar o menu e ler a opção repetidamente

    MENU = "(C)ompra (F)atura (S)air ? "

    c = []

    while True:

        # Utilizador introduz a opção com uma letra minúscula ou maiúscula

        op = input(MENU).upper()

        # Processar opção
        
        if op == "C":
            c.append(registaCompra(produtos))
        elif op == "F":
            n = int(input("Numero compra? "))
            fatura(produtos, c[n - 1])
        elif op == "S":
            break
    print("Obrigado!")


# Não altere este código / Do not change this code
import sys
if __name__ == "__main__":
    main(sys.argv[1:])
