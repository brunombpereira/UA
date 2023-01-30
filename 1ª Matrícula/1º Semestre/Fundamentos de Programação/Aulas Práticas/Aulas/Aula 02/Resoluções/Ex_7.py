print("Índice de Massa Corporal\n")

altura = float(input("Altura (m)? "))
peso = float(input("Peso (kg)? "))

imc = peso / altura**2

print("IMC:", imc, "kg/m2")

if(imc < 18.5):
    cat = "Magro"
elif(18.5 <= imc < 25):
    cat = "Saudável"
elif(25 <= imc < 30):
    cat = "Forte"
else:
    cat = "Obeso"

print("Categoria:", cat)
