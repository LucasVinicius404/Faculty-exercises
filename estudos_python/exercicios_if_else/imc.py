Altura = float(input("Digite sua altura em metros: "))
peso  = int(input("Digite o seu pego em kilogramas: "))

imc = peso / (Altura ** 2)

print(f"seu imc é de {imc: .2f}")

if(imc < 18.5):
    print("Você está abaixo do peso.")
elif imc < 25.0:
    print("Você está com peso normal.")
else:
    print("Você está acima do peso.")