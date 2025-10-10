#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

// Account structure
typedef struct {
    char firstName[50];
    char lastName[50];
    char birthday[20];
    char gender[10];
    int age;
    char contact[20];
    char gmail[50];
    char section[20];
    char username[50];
    char password[50];
} Account;

// Function declarations
void enableANSI();
void loadingScreen();
void invalid_Display();
void createAccount();
void loginAccount();
void forgotPassword();
void inputPassword(char *password);
int isStrongPassword(const char *password);

// Enable ANSI escape sequences (for color and cursor control)
void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

// Animated loading screen
void loadingScreen() {
    printf("\n\n\tLoading");
    for (int i = 0; i < 5; i++) {
        printf(".");
        Sleep(300);
    }
    printf("\n");
}

// Invalid input flashing display
void invalid_Display() {
    for (int i = 0; i < 5; i++) {
        printf("\033[2J\033[H"); // clear screen
        printf("\n\n");
        printf("  ╔══════════════════════════════════════════════════════════════════════╗\n");
        printf("  ║                                                                      ║\n");
        printf("  ║                   ⚠️   INVALID INPUT! TRY AGAIN!   ⚠️                ║\n");
        printf("  ║                                                                      ║\n");
        printf("  ╚══════════════════════════════════════════════════════════════════════╝\n");
        Sleep(200);
        system("cls");
        Sleep(200);
    }
}

// Password input masking
void inputPassword(char *password) {
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == 13) { // Enter key
            password[i] = '\0';
            printf("\n");
            break;
        } else if (ch == 8 && i > 0) { // Backspace
            i--;
            printf("\b \b");
        } else if (ch != 8) {
            password[i++] = ch;
            printf("*");
        }
    }
}

// Password strength checker
int isStrongPassword(const char *password) {
    int hasDigit = 0;
    int length = strlen(password);

    if (length < 8)
        return 0;  // too short

    for (int i = 0; i < length; i++) {
        if (password[i] >= '0' && password[i] <= '9')
            hasDigit = 1;
    }

    return hasDigit; // must have a number
}

// Create Account
void createAccount() {
    FILE *fp;
    Account acc;
    char retypePass[50];

    system("cls");
    printf("\033[1;33m=========================================================\n");
    printf("                 CREATE ACCOUNT FORM\n");
    printf("=========================================================\033[0m\n");

    printf("\nEnter First Name: ");
    fflush(stdin);
    fgets(acc.firstName, sizeof(acc.firstName), stdin);
    acc.firstName[strcspn(acc.firstName, "\n")] = '\0';

    printf("Enter Last Name: ");
    fgets(acc.lastName, sizeof(acc.lastName), stdin);
    acc.lastName[strcspn(acc.lastName, "\n")] = '\0';

    printf("Enter Birthday (MM/DD/YYYY): ");
    fgets(acc.birthday, sizeof(acc.birthday), stdin);
    acc.birthday[strcspn(acc.birthday, "\n")] = '\0';

    printf("Enter Gender (Male/Female): ");
    fgets(acc.gender, sizeof(acc.gender), stdin);
    acc.gender[strcspn(acc.gender, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &acc.age);
    fflush(stdin);

    printf("Enter Contact Number: ");
    fgets(acc.contact, sizeof(acc.contact), stdin);
    acc.contact[strcspn(acc.contact, "\n")] = '\0';

    printf("Enter Gmail Account: ");
    fgets(acc.gmail, sizeof(acc.gmail), stdin);
    acc.gmail[strcspn(acc.gmail, "\n")] = '\0';

    printf("Enter Section: ");
    fgets(acc.section, sizeof(acc.section), stdin);
    acc.section[strcspn(acc.section, "\n")] = '\0';

    printf("Enter Username: ");
    fgets(acc.username, sizeof(acc.username), stdin);
    acc.username[strcspn(acc.username, "\n")] = '\0';

    while (1) {
        printf("Enter Password: ");
        inputPassword(acc.password);

        if (!isStrongPassword(acc.password)) {
            printf("\n❌ Password must be at least 8 characters long and contain at least one number.\n\n");
            continue;
        }

        printf("Retype Password: ");
        inputPassword(retypePass);

        if (strcmp(acc.password, retypePass) != 0) {
            printf("\n❌ Passwords do not match! Please re-enter.\n\n");
            Sleep(800);
            continue;
        }

        break;
    }

    fp = fopen("accounts.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fwrite(&acc, sizeof(Account), 1, fp);
    fclose(fp);

    printf("\n✅ Account created successfully!\n");
    loadingScreen();
    Sleep(1000);
}

// Login Account
void loginAccount() {
    FILE *fp;
    Account acc;
    char username[50], password[50];
    int found = 0;

    system("cls");
    printf("\033[1;34m============================ LOGIN ============================\033[0m\n");

    printf("\nEnter Username: ");
    fflush(stdin);
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    inputPassword(password);

    fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        printf("\n⚠️  No accounts found. Please create one first.\n");
        Sleep(2000);
        return;
    }

    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (strcmp(username, acc.username) == 0 && strcmp(password, acc.password) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found) {
        printf("\n✅ Login successful! Welcome, %s %s!\n", acc.firstName, acc.lastName);
        loadingScreen();
    } else {
        printf("\n❌ Invalid username or password!\n");
        invalid_Display();
    }
}

// Forgot Password
void forgotPassword() {
    FILE *fp, *temp;
    Account acc;
    char username[50], newPass[50], confirmPass[50];
    int found = 0;

    system("cls");
    printf("\033[1;31m===================== PASSWORD RECOVERY =====================\033[0m\n");

    printf("\nEnter Username: ");
    fflush(stdin);
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    fp = fopen("accounts.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (strcmp(username, acc.username) == 0) {
            found = 1;
            while (1) {
                printf("Enter New Password: ");
                inputPassword(newPass);

                if (!isStrongPassword(newPass)) {
                    printf("\n❌ Password must be at least 8 characters long and contain at least one number.\n\n");
                    continue;
                }

                printf("Retype New Password: ");
                inputPassword(confirmPass);

                if (strcmp(newPass, confirmPass) != 0) {
                    printf("\n❌ Passwords do not match! Please re-enter.\n\n");
                    continue;
                }

                strcpy(acc.password, newPass);
                printf("\nUpdating password...\n");
                loadingScreen();
                printf("\n✅ Password reset successfully!\n");
                break;
            }
        }
        fwrite(&acc, sizeof(Account), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found)
        printf("\n❌ Username not found!\n");
}

// Main Program
int main() {
    int choice;
    enableANSI();

    while (1) {
        system("cls");
        printf("\033[1;36m=====================================================\n");
        printf("   WELCOME TO PHILTECH SCHOOL MANAGEMENT SYSTEM\n");
        printf("=====================================================\033[0m\n");
        printf("\n[1] Create Account\n");
        printf("[2] Login\n");
        printf("[3] Forgot Password\n");
        printf("[4] Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: loginAccount(); break;
            case 3: forgotPassword(); break;
            case 4:
                printf("\nThank you for using PhilTech SMS. Goodbye!\n");
                exit(0);
            default:
                invalid_Display();
        }

        printf("\nPress any key to continue...");
        getch();
    }

    return 0;
}
