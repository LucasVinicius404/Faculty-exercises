import { BookItem } from "./book-item.ts";
import { Loan } from "./loan.ts";
import { Member,MemberType } from "./member.ts";

export class Library {
    bookItems: BookItem[] = [];
    loans: Loan[] = [];

    addBookItem(item: BookItem) {
        this.bookItems.push(item)
    }


borrowBook(bookId: string, member: Member): Loan {
    if (member.activeLoans.length >= 3) {
        throw new Error("Limite de 3 empréstimos atingido.");
    }
    if (!member.canBorrow()) {
        throw new Error("Membro está bloqueado.");
    }

    const copies = this.bookItems.filter(bi => bi.book.id === bookId);
    const availableCopy = copies.find(c => c.isAvailable());
    if (!availableCopy) throw new Error("Não há cópias disponíveis.");


    const loanDays = member.type === MemberType.PREMIUM ? 30 : 14; 

    const now = new Date();
    const dueDate = new Date(now);
    dueDate.setDate(dueDate.getDate() + loanDays);

    const loan = new Loan(availableCopy, member, now, dueDate);

    availableCopy.markAsLoaned();
    member.addLoan(loan);
    this.loans.push(loan);

    return loan;
}

    returnBook(loan: Loan) {
    const now = new Date();

    loan.returnBook(now);
    loan.member.removeLoan(loan);


    if (now > loan.dueDate) {
        const daysLate = Math.ceil(
            (now.getTime() - loan.dueDate.getTime()) / (1000 * 60 * 60 * 24)
        );

        let aplicarBloqueio = false;

        if (loan.member.type === MemberType.PREMIUM) {
            if (daysLate > 3) {
                aplicarBloqueio = true;
            }
        } else {
            aplicarBloqueio = true;
        }

        if (aplicarBloqueio) {
            const blockUntil = new Date(now);
            blockUntil.setDate(blockUntil.getDate() + daysLate); 
            loan.member.blockUntil(blockUntil);
        }
    }
}
}