import { acomodacao } from "./acomodacao.ts";

export class apartamento extends acomodacao {
    private readonly CONDO_FEE = 50;

    calculatePrice(days: number): number {
        return (this.basePricePerDay * days) + this.CONDO_FEE;
    }
}