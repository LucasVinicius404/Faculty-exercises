import { Book } from "./book.ts";
import { BookItem } from "./book-item.ts";
import { Member, MemberType } from "./member.ts";
import { Library } from "./library.ts";

const biblioteca = new Library();

// --- SETUP: Criando acervo ---
const livros = [
    new Book("101", "Machado de Assis", "Dom Casmurro"),
    new Book("102", "J.K. Rowling", "Harry Potter"),
    new Book("103", "J.R.R. Tolkien", "Senhor dos Anéis"),
    new Book("104", "George Orwell", "1984"),
    new Book("105", "Aldous Huxley", "Admirável Mundo Novo")
];

livros.forEach((l, i) => {
    biblioteca.addBookItem(new BookItem(`item-${i}`, l));
});


console.log("=== TESTE PARTE 0 & 2: MEMBROS E PRAZOS ===");
const lucas = new Member("M1", "Lucas", MemberType.REGULAR); 
const joao = new Member("M2", "João", MemberType.PREMIUM);   

const empRegular = biblioteca.borrowBook("101", lucas);
const empPremium = biblioteca.borrowBook("102", joao);

console.log(`Regular (Lucas) deve devolver em: ${empRegular.dueDate.toLocaleDateString()}`); 
console.log(`Premium (João) deve devolver em: ${empPremium.dueDate.toLocaleDateString()}`);  

console.log("\n=== TESTE PARTE 1: LIMITE DE 3 LIVROS ===");
try {
    biblioteca.borrowBook("103", lucas); // 2º livro
    biblioteca.borrowBook("104", lucas); // 3º livro
    console.log("Tentando pegar o 4º livro para o Lucas...");
    biblioteca.borrowBook("105", lucas); // Deve falhar
} catch (e) {
    console.log("Sucesso no Teste de Limite:", e.message); 
}

console.log("\n=== TESTE PARTE 3: PENALIDADES (ATRASO) ===");

// 1. Caso Regular: Atraso de 1 dia = Bloqueio de 1 dia
console.log("Simulando atraso de 1 dia para membro REGULAR...");
empRegular.dueDate.setDate(empRegular.dueDate.getDate() - 15); // Força atraso de 1 dia
biblioteca.returnBook(empRegular);
console.log(`Lucas bloqueado? ${!lucas.canBorrow() ? "Sim" : "Não"}`);

// 2. Caso Premium: Tolerância de até 3 dias 
console.log("\nSimulando atraso de 2 dias para membro PREMIUM (Tolerância)...");
empPremium.dueDate.setDate(empPremium.dueDate.getDate() - 32); // Força atraso de 2 dias
biblioteca.returnBook(empPremium);
console.log(`João bloqueado com 2 dias de atraso? ${!joao.canBorrow() ? "Sim" : "Não (Tolerância OK)"}`); 

// 3. Caso Premium: Atraso de 5 dias (Bloqueia)
const novoLivro = new Book("106", "Autor", "Livro Teste");
const novoItem = new BookItem("item-6", novoLivro);
biblioteca.addBookItem(novoItem);

const empPremiumAtrasado = biblioteca.borrowBook("106", joao);
console.log("\nSimulando atraso de 5 dias para membro PREMIUM (Punição)...");
empPremiumAtrasado.dueDate.setDate(empPremiumAtrasado.dueDate.getDate() - 35); // Força atraso de 5 dias
biblioteca.returnBook(empPremiumAtrasado);
console.log(`João bloqueado com 5 dias de atraso? ${!joao.canBorrow() ? "Sim (Punição OK)" : "Não"}`);