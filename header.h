#define NUM_USERS 1000
#define MAX_STRING_SIZE 50
#define NO_OF_SCREEN 3
#define CANCEL -1
#define INITIALIZE -1
#define FAIL NULL
#define INCORRECT -1

#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

typedef struct {
    char username[MAX_STRING_SIZE];
    char password[MAX_STRING_SIZE];
} Login;

typedef struct {
    Login *users;
    int size;
    int capacity;
} UserList;

void initialize_user_list(UserList *list);
void add_user(UserList *list, const char *username, const char *password);
int find_user(UserList *list, const char *username, const char *password);
void free_user_list(UserList *list);

struct _class_ {
    int classType; // 0 for VIP, 1 for Gold, 2 for Silver
    int totalSeats;
    int availableSeats; // Added this line
    int *seats;
};

typedef struct _class_ Class;

struct _screen_ {
    int screenNo;
    Class classes[3]; // Three classes: VIP, Gold, Silver
};
typedef struct _screen_ Screen;

struct _booking_ {
    int id;           // Unique booking ID
    int userId;       // ID of the user who made the booking
    int screenNo;     // Screen number
    int classType;    // Class type (VIP, Gold, Silver)
    int seatNumber;   // Seat number
};
typedef struct _booking_ Booking;

typedef struct {
    Booking *bookings;
    int size;
    int capacity;
} BookingArray;

Booking* initialize_booking(int numUsers);
void display_menu();
void display_UserMenu();
int login_User(Login *users, int numUsers, char username[], char password[]);
void book_ticket(Login *users, int userId, Screen *Screens, int numScreens);
void cancel_ticket(Booking *bookings, int bookingId, Screen *Screens, int numScreens);
void check_availability(Screen *Screens, int numScreens, int screenNo, int classType);
void confirmation_booking(Login *user, Booking *booking);
