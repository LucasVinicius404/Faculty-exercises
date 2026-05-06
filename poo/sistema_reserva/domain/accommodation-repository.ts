import { acomodacao } from "./acomodacao.ts";

export interface AccommodationRepository {
    findById(id: string): acomodacao | undefined; // Busca por ID
}