🏠 Sistema de Reservas de Acomodações (Estilo Airbnb)
Este projeto consiste em um sistema de gestão de hospedagens desenvolvido para a disciplina de Programação Orientada a Objetos da UNIFESP. O objetivo principal foi a aplicação prática de conceitos de arquitetura e padrões de projeto em um ambiente TypeScript. 

🛠️ Tecnologias Utilizadas
TypeScript: Linguagem principal para tipagem estática.  
Deno: Ambiente de execução (Runtime).  
Paradigma: Orientação a Objetos (POO).

🏗️ Decisões de Modelagem e Arquitetura
O projeto foi organizado em camadas seguindo os princípios da Clean Architecture para garantir o desacoplamento e a testabilidade do código:  

1-Domain (Domínio): Contém as entidades principais e as regras de negócio puras.

    .Polimorfismo: Implementado através da classe abstrata acomodacao e suas especializações (casa, apartamento, republica). Cada uma calcula seu preço de forma independente, sem o uso de condicionais (if/else) baseadas em tipo.  
    
    .Interfaces: Utilizadas para definir contratos como o Fee (taxas) AccommodationRepository.  

2- Application (Aplicação): Contém os casos de uso e serviços.
    .Composição: O PricingService utiliza composição para aplicar múltiplas taxas dinamicamente a uma reserva.  
    
    .Caso de Uso: O CreateBooking orquestra a criação de uma reserva unindo o repositório e o serviço de preços.  Infra (Infraestrutura): Implementações concretas de ferramentas externas.Persistência em Memória: Implementação de repositórios que armazenam acomodações e reservas em arrays durante a execução do programa.

2-Infra (Infraestrutura): Implementações concretas de ferramentas externas.
    .Persistência em Memória: Implementação de repositórios que armazenam acomodações e reservas em arrays durante a execução do programa.

📋 Funcionalidades

    .Realizar Reserva: Escolha entre Casa, Apartamento ou República, defina os dias e veja o cálculo automático com taxas da plataforma.  

    .Listar Reservas: Exibe todas as reservas armazenadas na memória durante a sessão.  

    .Verificar Ocupação: Informa se o sistema está operando em capacidade máxima (limite definido na main).