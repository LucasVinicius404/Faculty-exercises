import { AccommodationRepository } from "../domain/accommodation-repository.ts";
import { acomodacao } from "../domain/acomodacao.ts";

export class InMemoryAccommodationRepository implements AccommodationRepository {
    private accommodations: acomodacao[] = [];

    // Método extra para a gente cadastrar casas nos testes
    save(acc: acomodacao): void {
        this.accommodations.push(acc);
    }

    findById(id: string): acomodacao | undefined {
        return this.accommodations.find(acc => acc.id === id);
    }
}