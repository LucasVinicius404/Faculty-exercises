a = int(input("Informe os dias para a atividade A: "))
b = int(input("Informe os dias para a atividade B: "))
c = int(input("Informe os dias para a atividade C: "))

print(f"O total de tempo para o projeto é de {a + b + c} dias")if(a >= 0 and b>= 0 and c>= 0) else print("Erro: os dias não pode ser negativos")