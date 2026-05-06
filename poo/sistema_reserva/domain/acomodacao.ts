export abstract class acomodacao {
    constructor(
        public id: string,
        public name: string,
        public basePricePerDay: number
    ) {}

    // Toda acomodação é obrigada a ter esse método, mas cada uma implementa o seu
    abstract calculatePrice(days: number): number;
}