def media(soma,quantidade):
    if quantidade > 0:
        return soma/quantidade
    else:
        return 0

soma = 0.0
quantidade = 0

valor = float(input("digite um valor: "))

while(valor != -1):
    soma += valor
    quantidade += 1
    valor = float(input("digite um valor: "))

print("\n a soma total foi de %.2f" %soma)
if media(soma,quantidade):
    print("\n a media final foi de %.1f" %media(soma,quantidade))
else:
    print("não há valores contaveis!!")