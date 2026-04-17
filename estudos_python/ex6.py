nota1 = float(input("digite a nota da primeira prova do aluno: "))

if nota1 > 10.00:
    nota1 = float(input("nota invalida digite a nota no intervalo de 0 - 10: "))

nota2 = float(input("digite a nota da segunda prova do aluno: "))
if nota2 > 10.00 or nota2 < 0.00:
    nota2 = float(input("nota invalida digite a nota no intervalo de 0 - 10: "))

presença = float(input("digite a porcentagem de presença do aluno: "))
if presença > 100.00 or presença <  0.00:
    presença = float(input("presença invalidada digite novamente no intervalo de 0-100: "))

media_final = (nota1 + nota2)/2

if media_final >=6.00 and presença >= 75.00:
    print("aluno aprovado com media final de: %.1f"%media_final, "e com presença de %.2f%% " % presença)
elif media_final < 6.00 and presença >= 75.00:
    print("o aluno está de exame")
else:
    if presença < 75.00:
        print("o aluno foi reprovado por presença")
    else:
        print("o aluno não atingiu a media necessaria para o exame e foi reprovado direto")