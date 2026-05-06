import { Booking } from "./booking.ts";

export interface BookingRepository {
    save(booking: Booking): void;
    findAll(): Booking[];
}