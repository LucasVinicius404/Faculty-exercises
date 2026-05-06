import { acomodacao } from "./acomodacao.ts";

export class Booking {
    constructor(
        public readonly accommodation: acomodacao,
        public readonly days: number,
        public readonly basePrice: number,
        public readonly totalPrice: number
    ) {
        // Validação básica: não faz sentido uma reserva de 0 dias
        if (days <= 0) {
            throw new Error("A reserva deve ter pelo menos 1 dia.");
        }
    }
}