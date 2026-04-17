A = input("digite o valor da variavel A: ")
B = input("digite o valor da variavel B: ")

if(A > B):
    aux = A
    A = B
    B = aux

print("agora a a variavel A é:",A)
print("e a variavel B é:", B)
