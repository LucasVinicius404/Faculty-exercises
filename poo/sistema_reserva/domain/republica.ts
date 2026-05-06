import { acomodacao } from "./acomodacao.ts";

export class republica extends acomodacao {
    
    calculatePrice(days: number): number {
        return (this.basePricePerDay * days);
    }
}