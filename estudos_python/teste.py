arquivo = open('arqText.txt','w')

arquivo.write("curso python\n")
arquivo.write('aula pratica')
arquivo.close()

leitura = open('arqText.txt','r')
print(leitura.read())
leitura.close

reescrita = open('arqText.txt','a')
reescrita.write("\nsalve")
reescrita.close()

ultimo = reescrita = open('arqText.txt','a+')
ultimo.write("\n eu denovo")
print(ultimo.read())
ultimo.close()