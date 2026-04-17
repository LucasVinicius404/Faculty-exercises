# 1. Perguntas simples que retornam 'string'
nome = input("Qual o nome da pessoa? ")

# 2. Converta para 'int' logo após o input.
#    Use uma f-string (com o 'f' antes das aspas) para colocar a variável 'nome' na pergunta.
codigo = int(input(f"Qual o código do {nome}? "))

# 3. Salário deve ser 'float' (para aceitar centavos)
#    Note como a f-string pode formatar a pergunta com múltiplas variáveis.
salario = float(input(f"Qual é o salário do {nome} (cód: {codigo})? "))

# 4. Este é o jeito certo de pegar um 'bool'
#    'bool(input())' não funciona como se espera.
#    O jeito certo é pegar um texto (ex: "s") e COMPARAR.
resposta_ativo = input(f"O {nome} está ativo? (s/n) ")
ativo = resposta_ativo.lower() == 's'  # Isso VAI resultar em True ou False

print("\n--- Ficha da Pessoa ---")

# 5. Use f-strings para imprimir também. É mais limpo.
print("Codigo:",codigo)
print("Nome:",nome)
print("Salario: %.2f"% salario)  # O ': .2f' formata o float com 2 casas decimais
print("Ativo: ",ativo)


"""
teste
print("Codigo: %d" % codigo)     # %d funciona, pois 'codigo' AGORA é um int
print("Nome: %s" % nome)
print("Salario: R$ %.2f" % salario) # %.2f é o certo para float de dinheiro
print("Ativo: %s" % ativo)       # %s imprime "True" ou "False"
"""