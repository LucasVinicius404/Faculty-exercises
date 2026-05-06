import { BookingRepository } from "../domain/booking-repository.ts";
import { Booking } from "../domain/booking.ts";

export class InMemoryBookingRepository implements BookingRepository {
    private bookings: Booking[] = [];

    save(booking: Booking): void {
        this.bookings.push(booking);
    }

    findAll(): Booking[] {
        return [...this.bookings];
    }
}