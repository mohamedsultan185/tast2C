#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME 50
#define MAX_PASSWORD 50

struct FlagInfo {
    bool activeFlag;
};

struct User {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    struct FlagInfo flagInfo;
};

union ActivityFlag {
    int activeFlag;
    char flagChar[4];
};

void registerUser(struct User users[], union ActivityFlag *flag, int *userCount) {
    printf("Enter username: ");
    scanf("%s", users[*userCount].username);

    printf("Enter password: ");
    scanf("%s", users[*userCount].password);

    printf("Enter activity flag (true/1 or false/0): ");
    scanf("%d", &flag->activeFlag);

    // Update the flagInfo in the User struct based on user input
    users[*userCount].flagInfo.activeFlag = flag->activeFlag;

    (*userCount)++;
    printf("Registration successful!\n");
}

int loginUser(struct User users[], int userCount, char username[], char password[]) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            if (users[i].flagInfo.activeFlag) {
                return 1; // Active user, login successful
            } else {
                printf("User is not active. Please contact the administrator.\n");
                return 0; // Inactive user, login failed
            }
        }
    }
    return -1; // Invalid username or password, login failed
}

int main() {
    struct User users[MAX_USERS];
    union ActivityFlag flag;
    int userCount = 0;
    int choice;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    do {
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser(users, &flag, &userCount);
                break;
            case 2:
                printf("Enter username: ");
                scanf("%s", username);

                printf("Enter password: ");
                scanf("%s", password);

                int loginStatus = loginUser(users, userCount, username, password);
                if (loginStatus == 1) {
                    printf("Login successful!\n");
                } else if (loginStatus == 0) {
                    printf("Login failed. User is not active.\n");
                } else {
                    printf("Login failed. Invalid username or password.\n");
                }
                break;
            case 3:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
