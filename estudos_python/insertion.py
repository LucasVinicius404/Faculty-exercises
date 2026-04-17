def insertion_sort(lista):
    for i in range(1,len(lista)):
        chave = lista[i]
        j = i - 1

        while j>= 0 and lista[j] > chave:
            lista[j + 1] = lista[j]
            j -= 1

        lista[j + 1] = chave

meu_vetor = [12,9,8,50,60]
insertion_sort(meu_vetor)
print("o novo vetor ordenado é: ",meu_vetor)

