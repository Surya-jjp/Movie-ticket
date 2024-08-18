#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

Booking* initialize_booking(int numUsers) {
    Booking *bookings = (Booking *)malloc(numUsers * sizeof(Booking));
    if (!bookings) {
        printf("Memory allocation failed.\n");
        return FAIL;
    }
    for (int i = 0; i < numUsers; i++) {
        bookings[i].userId = INITIALIZE;
        bookings[i].screenNo = INITIALIZE;
        bookings[i].classType = INITIALIZE;
        bookings[i].seatNumber = INITIALIZE;
    }
    return bookings;
}

// Initialize the user list
void initialize_user_list(UserList *list) {
    list->capacity = INITIAL_CAPACITY;
    list->size = 0;
    list->users = (Login *)malloc(list->capacity * sizeof(Login));
    if (!list->users) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

// Add a new user to the list
void add_user(UserList *list, const char *username, const char *password) {
    if (list->size >= list->capacity) {
        list->capacity *= GROWTH_FACTOR;
        list->users = (Login *)realloc(list->users, list->capacity * sizeof(Login));
        if (!list->users) {
            printf("Memory reallocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    strcpy(list->users[list->size].username, username);
    strcpy(list->users[list->size].password, password);
    list->size++;
}

// Find a user in the list
int find_user(UserList *list, const char *username, const char *password) {
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->users[i].username, username) == 0 &&
            strcmp(list->users[i].password, password) == 0) {
            return i; // Return user index
        }
    }
    return INCORRECT; // User not found
}

// Free the user list memory
void free_user_list(UserList *list) {
    free(list->users);
    list->users = NULL;
    list->size = 0;
    list->capacity = 0;
}

void display_menu() {
    printf("1. Login\n");
    printf("2. Register\n");
    printf("5. Exit\n");
}

// Display user menu
void display_UserMenu() {
    printf("User Menu:\n");
    printf("1. Book Ticket\n");
    printf("2. Cancel Ticket\n");
    printf("3. Check Availability\n");
    printf("4. Logout\n");
}

// Login function
int login_User(Login *users, int numUsers, char username[], char password[]) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return INCORRECT;
}

// Book Ticket function
void book_ticket(Login *users, int userId, Screen *Screens, int numScreens) {
    static int nextBookingId = 1; // Static variable to generate unique booking IDs
    int screenNo, classType, seatNumber;
    int isAvailable = 0;

    printf("Enter the screen number (1 to %d): ", numScreens);
    if (scanf("%d", &screenNo) != 1) {
        printf("Invalid input.\n");
        return;
    }
    screenNo--; // Adjust for 0-based indexing

    if (screenNo < 0 || screenNo >= numScreens) {
        printf("Invalid screen number.\n");
        return;
    }

    printf("Enter class type (0 for VIP, 1 for Gold, 2 for Silver): ");
    if (scanf("%d", &classType) != 1) {
        printf("Invalid input.\n");
        return;
    }

    if (classType < 0 || classType >= 3) {
        printf("Invalid class type.\n");
        return;
    }

    // Check if seats are available in the selected class
    for (int i = 0; i < Screens[screenNo].classes[classType].totalSeats; i++) {
        if (Screens[screenNo].classes[classType].seats[i] == 0) { // Seat is available
            seatNumber = i;
            isAvailable = 1;
            break;
        }
    }

    if (!isAvailable) {
        printf("No seats available in this class.\n");
        return;
    }

    // Book the seat
    Screens[screenNo].classes[classType].seats[seatNumber] = 1;
    Screens[screenNo].classes[classType].availableSeats--;

    // Store the booking details
    Booking newBooking;
    newBooking.id = nextBookingId++;
    newBooking.userId = userId;
    newBooking.screenNo = screenNo;
    newBooking.classType = classType;
    newBooking.seatNumber = seatNumber;

    // Confirmation of booking
    printf("Ticket booked successfully!\n");
    printf("Booking ID: %d\n", newBooking.id);
    printf("User: %s\n", users[userId].username);
    printf("Screen No: %d, Class Type: %d, Seat No: %d\n", screenNo + 1, classType, seatNumber + 1);
}

// Cancel ticket function
void cancel_ticket(Booking *bookings, int bookingId, Screen *Screens, int numScreens) {
    int bookingFound = 0;

    for (int i = 0; i < INITIAL_CAPACITY; i++) { // Assuming INITIAL_CAPACITY is the max number of bookings
        if (bookings[i].id == bookingId && bookings[i].userId != CANCEL) {
            bookingFound = 1;

            // Free up the seat in the screen and class
            int screenNo = bookings[i].screenNo;
            int classType = bookings[i].classType;
            int seatNumber = bookings[i].seatNumber;

            if (screenNo >= 0 && screenNo < numScreens && classType >= 0 && classType < 3) {
                if (Screens[screenNo].classes[classType].seats[seatNumber] == 1) { // Check if the seat is actually booked
                    Screens[screenNo].classes[classType].seats[seatNumber] = 0; // Mark the seat as available
                    Screens[screenNo].classes[classType].availableSeats++; // Increment the available seats count

                    printf("Seat number %d in Screen %d, Class %d is now available.\n", seatNumber + 1, screenNo + 1, classType);
                }
            }

            // Mark the booking as canceled
            bookings[i].userId = CANCEL;
            printf("Ticket cancellation successful.\n");
            return;
        }
    }

    if (!bookingFound) {
        printf("No booking found with this ID.\n");
    }
}

// Check availability function
void check_availability(Screen *Screens, int numScreens, int screenNo, int classType) {
    if (screenNo < 1 || screenNo > numScreens) {
        printf("Invalid screen number.\n");
        return;
    }

    if (classType < 0 || classType > 2) {
        printf("Invalid class type.\n");
        return;
    }

    int availableSeats = Screens[screenNo - 1].classes[classType].availableSeats;
    printf("Available seats in screen %d, class %d: %d\n", screenNo, classType, availableSeats);
}

// Confirm booking function
void confirmation_booking(Login *user, Booking *booking) {
    printf("Booking confirmed for user %s, screen %d, class %d, seat %d.\n",
           user->username, booking->screenNo, booking->classType, booking->seatNumber);
}
