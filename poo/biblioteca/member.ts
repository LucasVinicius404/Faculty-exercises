import { Loan } from "./loan.ts";

export enum MemberType {
    REGULAR = 'REGULAR',
    PREMIUM = 'PREMIUM',
}

export class Member {
    activeLoans: Loan[] = []
    blockedUntil?: Date

    constructor(
        public id: string,
        public name: string,
        public type: MemberType = MemberType.REGULAR 
    ) {}

    canBorrow(): boolean {
        if (!this.blockedUntil) return true;
        return new Date() > this.blockedUntil;
    }

    addLoan(loan: Loan) {
        this.activeLoans.push(loan)
    }

    removeLoan(loan: Loan) {
        this.activeLoans = 
            this.activeLoans.filter(l => l !== loan)
    }

    blockUntil(date: Date) {
        this.blockedUntil = date
    }

    getLoans(): Loan[] {
        return [...this.activeLoans]
    }
}