import { AccommodationRepository } from "../domain/accommodation-repository.ts";
import { PricingService } from "./preco_servico.ts";
import { Booking } from "../domain/booking.ts";

export class CreateBooking {
    constructor(
        private repository: AccommodationRepository, // Depende da interface
        private pricingService: PricingService      // Serviço de taxas
    ) {}

    execute(accommodationId: string, days: number): Booking {
        // 1. Busca a acomodação no "banco de dados"
        const acc = this.repository.findById(accommodationId);
        if (!acc) throw new Error("Acomodação não encontrada!");

        // 2. Delega o cálculo do preço base para a acomodação (Polimorfismo)
        const basePrice = acc.calculatePrice(days);

        // 3. Aplica as taxas usando o serviço (Composição)
        const totalPrice = this.pricingService.calculateTotal(basePrice);

        // 4. Retorna a entidade de Reserva pronta
        return new Booking(acc, days, basePrice, totalPrice);
    }
}