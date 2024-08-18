#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {
    // Initialize screens with specific seat counts
    Screen Screens[NO_OF_SCREEN];

    // Screen 1
    Screens[0].screenNo = 1;
    Screens[0].classes[0].classType = 0; // VIP
    Screens[0].classes[0].totalSeats = 30;
    Screens[0].classes[0].availableSeats = 30;
    Screens[0].classes[0].seats = (int *)calloc(Screens[0].classes[0].totalSeats, sizeof(int));

    Screens[0].classes[1].classType = 1; // Gold
    Screens[0].classes[1].totalSeats = 80;
    Screens[0].classes[1].availableSeats = 80;
    Screens[0].classes[1].seats = (int *)calloc(Screens[0].classes[1].totalSeats, sizeof(int));

    Screens[0].classes[2].classType = 2; // Silver
    Screens[0].classes[2].totalSeats = 40;
    Screens[0].classes[2].availableSeats = 40;
    Screens[0].classes[2].seats = (int *)calloc(Screens[0].classes[2].totalSeats, sizeof(int));

     // Screen 2
Screens[1].screenNo = 2;
Screens[1].classes[0].classType = 0; // VIP
Screens[1].classes[0].totalSeats = 20;
Screens[1].classes[0].availableSeats = 20;
Screens[1].classes[0].seats = (int *)calloc(Screens[1].classes[0].totalSeats, sizeof(int));

Screens[1].classes[1].classType = 1; // Gold
Screens[1].classes[1].totalSeats = 60;
Screens[1].classes[1].availableSeats = 60;
Screens[1].classes[1].seats = (int *)calloc(Screens[1].classes[1].totalSeats, sizeof(int));

Screens[1].classes[2].classType = 2; // Silver
Screens[1].classes[2].totalSeats = 40;
Screens[1].classes[2].availableSeats = 40;
Screens[1].classes[2].seats = (int *)calloc(Screens[1].classes[2].totalSeats, sizeof(int));

// Screen 3
Screens[2].screenNo = 3;
Screens[2].classes[0].classType = 0; // VIP
Screens[2].classes[0].totalSeats = 20;
Screens[2].classes[0].availableSeats = 20;
Screens[2].classes[0].seats = (int *)calloc(Screens[2].classes[0].totalSeats, sizeof(int));

Screens[2].classes[1].classType = 1; // Gold
Screens[2].classes[1].totalSeats = 60;
Screens[2].classes[1].availableSeats = 60;
Screens[2].classes[1].seats = (int *)calloc(Screens[2].classes[1].totalSeats, sizeof(int));

Screens[2].classes[2].classType = 2; // Silver
Screens[2].classes[2].totalSeats = 40;
Screens[2].classes[2].availableSeats = 40;
Screens[2].classes[2].seats = (int *)calloc(Screens[2].classes[2].totalSeats, sizeof(int));

// Initialize users array
Login users[NUM_USERS] = {0};
int numUsers = 0; // Track the number of registered users

int choice, userId = INCORRECT;
char username[MAX_STRING_SIZE], password[MAX_STRING_SIZE];

Booking *bookings = initialize_booking(NUM_USERS);

while (1) {
    if (userId == INCORRECT) {
        display_menu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                userId = login_User(users, numUsers, username, password);
                if (userId != INCORRECT) {
                    printf("Login successful!\n");
                } else {
                    printf("Login failed. Try again.\n");
                }
                break;
            case 2: // Register new user
                if (numUsers < NUM_USERS) {
                    printf("Enter a new username: ");
                    scanf("%s", username);
                    printf("Enter a new password: ");
                    scanf("%s", password);
                    strcpy(users[numUsers].username, username);
                    strcpy(users[numUsers].password, password);
                    numUsers++;
                    printf("Registration successful! Please log in.\n");
                } else {
                    printf("User limit reached. Cannot register more users.\n");
                }
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Please log in first or register.\n");
        }
    } else {
        while (userId != INCORRECT) {
            display_UserMenu();
            printf("Enter choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    book_ticket(users, userId, Screens, NO_OF_SCREEN);
                    break;
                case 2:
                    printf("Enter booking ID to cancel: ");
                    int bookingId;
                    scanf("%d", &bookingId);
                    cancel_ticket(bookings, bookingId, Screens, NO_OF_SCREEN);
                    break;
                case 3:
                    printf("Enter screen number and class type to check availability (format: screenNo classType): ");
                    int screenNo, classType;
                    scanf("%d %d", &screenNo, &classType);
                    check_availability(Screens, NO_OF_SCREEN, screenNo, classType);
                    break;
                case 4:
                    printf("Logging out...\n");
                    userId = INCORRECT; // Log out the user
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    }
}

// Free allocated memory
for (int i = 0; i < NO_OF_SCREEN; i++) {
    free(Screens[i].classes[0].seats);
    free(Screens[i].classes[1].seats);
    free(Screens[i].classes[2].seats);
}

free(bookings);

return 0;
}
