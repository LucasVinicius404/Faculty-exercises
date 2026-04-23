maca = int(input("Digite a quantidade de maçãs vendidas: "))
banana = int(input("Digite a quantidade de bananas vendidas: "))

if maca > banana:
    print("\nAs maçãs venderam mais")
elif maca == banana:
    print("\nVenderam a mesma quantidade")
else:
    print("\nAs bananas venderam mais")