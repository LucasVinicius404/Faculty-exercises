import { acomodacao } from "./acomodacao.ts";

export class casa extends acomodacao {
    private readonly CLEANING_FEE = 150; // Taxa fixa

    calculatePrice(days: number): number {
        return (this.basePricePerDay * days) + this.CLEANING_FEE;
    }
}