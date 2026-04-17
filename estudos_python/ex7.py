soma = 0.0
quantidade = 0


valor = float(input("digite um valor: "))

while(valor != -1):
    soma += valor
    quantidade += 1
    valor = float(input("digite um valor: "))

print("\n a soma do valores adicionados foi de %.2f" %soma)
print("\n a quantidade de valores adicionado foi de: ",quantidade)
if quantidade > 0:
    print("\n a media final foi de %.1f" % (soma / quantidade))
else:
    print("\n Nenhum valor foi digitado.")
