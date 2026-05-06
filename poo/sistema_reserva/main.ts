import { casa } from "./domain/casa.ts";
import { apartamento } from "./domain/apartamento.ts";
import { republica } from "./domain/republica.ts";
import { PlatformFee } from "./domain/implement-fee.ts";
import { ServiceFee } from "./domain/service-fee.ts";
import { PricingService } from "./aplicacao/preco_servico.ts";
import { CreateBooking } from "./aplicacao/create-booking.ts";
import { InMemoryAccommodationRepository } from "./infra/in-memory.ts";
import { InMemoryBookingRepository } from "./infra/booking-in-memory.ts";

// --- INICIALIZAÇÃO ---
const accRepo = new InMemoryAccommodationRepository();
const bookingRepo = new InMemoryBookingRepository();
const pricingService = new PricingService([new PlatformFee(), new ServiceFee(20)]);
const createBooking = new CreateBooking(accRepo, pricingService);

// Cadastro inicial das 3 modalidades[cite: 9, 10, 13]
accRepo.save(new casa("1", "Casa de Campo", 450));
accRepo.save(new apartamento("2", "Apartamento Studio", 180));
accRepo.save(new republica("3", "Vaga em República", 40));

const CAPACIDADE_MAXIMA = 10;
let executando = true;

console.log("=== SISTEMA DE GESTÃO DE RESERVAS ===");

while (executando) {
    console.log("\n--------------------------------");
    console.log("1. Realizar Nova Reserva");
    console.log("2. Listar Todas as Reservas");
    console.log("3. Verificar Ocupação Atual");
    console.log("0. Sair do Sistema");
    
    const opcao = prompt("Escolha uma opção:");

    switch (opcao) {
        case "1":
            // Verificação de Lotação
            if (bookingRepo.findAll().length >= CAPACIDADE_MAXIMA) {
                console.log("AVISO: O sistema atingiu a capacidade máxima de reservas!");
                break;
            }

            console.log("\nTipos disponíveis:");
            console.log("[1] Casa (Taxa Limpeza: R$150)");
            console.log("[2] Apartamento (Taxa Condomínio: R$50)");
            console.log("[3] República (Sem taxas adicionais)");
            
            const id = prompt("Digite o número do tipo desejado:");
            const dias = prompt("Quantos dias?");

            try {
                // O CreateBooking busca no repo, calcula preço e aplica taxas[cite: 5, 15]
                const reserva = createBooking.execute(id!, Number(dias));
                bookingRepo.save(reserva); // Persistência em memória
                
                console.log("\n✅ RESERVA REALIZADA!");
                console.log(`Local: ${reserva.accommodation.name}`);
                console.log(`Preço Base: R$ ${reserva.basePrice.toFixed(2)}`);
                console.log(`Total (com taxas plataforma): R$ ${reserva.totalPrice.toFixed(2)}`);
            } catch (e: any) {
                console.log(`\n❌ Erro: ${e.message}`);
            }
            break;

        case "2":
            const reservas = bookingRepo.findAll();
            console.log("\n=== RELATÓRIO DE RESERVAS ===");
            if (reservas.length === 0) {
                console.log("Nenhuma reserva registrada até o momento.");
            } else {
                reservas.forEach((b, i) => {
                    console.log(`${i + 1}. [${b.accommodation.constructor.name}] ${b.accommodation.name}`);
                    console.log(`   Duração: ${b.days} dias | Total: R$ ${b.totalPrice.toFixed(2)}`);
                });
            }
            break;

        case "3":
            const total = bookingRepo.findAll().length;
            const porcentagem = (total / CAPACIDADE_MAXIMA) * 100;
            console.log(`\nStatus: ${total}/${CAPACIDADE_MAXIMA} vagas ocupadas (${porcentagem}%).`);
            break;

        case "0":
            console.log("Finalizando sistema...");
            executando = false;
            break;

        default:
            console.log("Opção inválida. Tente novamente.");
    }
}