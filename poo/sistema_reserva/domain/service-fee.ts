import { Fee } from "./fee.ts";

export class ServiceFee implements Fee {
    constructor(private fixedValue: number) {}

    calculate(amount: number): number {
        return this.fixedValue; // Taxa fixa de serviço
    }
}