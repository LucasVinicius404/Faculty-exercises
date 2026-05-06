import { Fee } from "./fee.ts";

export class PlatformFee implements Fee {
    // Aplica 5.85% sobre o valor
    calculate(amount: number): number {
        return amount * 0.0585;
    }
}