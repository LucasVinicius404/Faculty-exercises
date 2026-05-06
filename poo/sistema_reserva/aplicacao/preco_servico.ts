import { Fee } from "../domain/fee.ts";

export class PricingService {
    // Composição: o serviço RECEBE uma lista de taxas[cite: 8]
    constructor(private fees: Fee[]) {}

    calculateTotal(basePrice: number): number {
        const totalFees = this.fees.reduce((acc, fee) => acc + fee.calculate(basePrice), 0);
        return basePrice + totalFees;
    }
}