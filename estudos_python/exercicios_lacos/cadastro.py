usuario = []
flag = -1

while flag != 1:
    user = input("Digite o seu nome de usuario: ")
    senha = input("digite a sua senha: ")
    if(len(user) < 5 or len(senha) < 8):
        flag = 0;
        if(len(user) < 5):
            print("O nome de usuario tem que ter pelo menos 5 Caracteres")
        elif(len(senha) < 8):
            print("A senha deve ter pelo menos 8 caracteres")
    else:
        print("Cadastro realizado com sucesso!")
        flag = 1
        usuario.append({"user": user,"senha":senha})
       

