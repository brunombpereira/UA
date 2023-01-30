def validate(nr):
	c=True
	if len(nr)<3:
		c=False
	for n in nr:
		if n not in "+1234567890":
			c=False
	return c

def registar():
	to=input("Telefone Origem? ")
	while validate(to)==False:
		to=input("Telefone Origem? ")
	tc=input("Telefone Chegada? ")
	while validate(tc)==False:
		tc=input("Telefone Chegada? ")
	dur=input("Duração (s)? ")
	return [[to, tc, dur]]
	
def ler():
	fil=input("Ficheiro? ")
	l=[]
	with open(fil) as f:
		for line in f:
			line=line.split()
			l.append(line)
	return l
	
def listar(reg):
	c=[]
	for e in reg:
		if e[0] not in c:
			c.append(e[0])
		if e[1] not in c:
			c.append(e[1])
	c.sort()
	print ("Clientes: {}".format([x for x in c]))

def main():
	op=0
	while op!=5:
		print("1) Registar Chamada\n2) Ler ficheiro\n3) Listar clientes\n4) Fatura\n5) Terminar")
		op=float(input("Opção? "))
		if op==1:
			reg=registar()
		elif op==2:
			reg=ler()
		elif op==3:
			listar(reg)
		elif op==4:
			main()
		elif op==5:
			print("Teminado")

main()
