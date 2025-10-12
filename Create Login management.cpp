#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

struct Account {
    char username[50];
    char password[50];
    char role[20];
    char course[50];
    char firstName[50];
    char lastName[50];
};

void menu();
int createAccount();
void loginAccount();
void forgotPassword();
void inputPassword(char *pass);
void loadingScreen();
void clear_stdin();

int main() {
    menu();
    return 0;
}

void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void menu() {
    char choice;

    while (1) {
        system("cls");
        printf("=====================================================\n");
        printf("|          PHILTECH SCHOOL MANAGEMENT SYSTEM        |\n");
        printf("=====================================================\n");
        printf("|           [1] Create Account                      |\n");
        printf("|           [2] Login                               |\n");
        printf("|           [3] Forgot Password                     |\n");
        printf("|           [4] Exit                                |\n");
        printf("-----------------------------------------------------\n");
        printf("Enter your choice: ");
        choice = getch();
        printf("%c\n", choice);

        switch (choice) {
            case '1': createAccount(); break;
            case '2': loginAccount(); break;
            case '3': forgotPassword(); break;
            case '4':
                printf("\nThank you for using the system!\n");
                exit(0);
            default:
                printf("\n? Invalid input! Please press any key to try again.\n");
                getch();
                continue;
        }

        printf("\nPress any key to return to main menu...");
        getch();
    }
}

/* createAccount:
   - collects personal info + account info
   - writes a record to accounts.txt in the format:
     username,password,role,course,firstName,lastName\n
*/
int createAccount() {
    char firstName[50], lastName[50], birthD[20], sex[10], address[200];
    char username[50], password[50], confirmPassword[50];
    char role[20], course[50];
    FILE *fp;

    // FIRST NAME
    while (1) {
        system("cls");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                       * --------------------- / ---------------- /                       [ 9 ] Back  |\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +====================================================================================================================+\n\n");
        printf("                                                                   Personal Information\n\n");

        printf("\n\n                                  Enter firstname:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");

        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", firstName) != 1) { clear_stdin(); continue; }

        if (strcmp(firstName, "9") == 0) {
            return 0; // go back to menu
        }

        if (strlen(firstName) < 2) {
            printf("\n                            (System): Firstname too short! Try again.\n");
            printf("                            Press any key to try again...");
            getch();
            continue;
        }

        int boxWidth = 90;
        int textLen = strlen(firstName);
        int leftPadding = (boxWidth - textLen) / 2;

        system("cls");
        printf("\n\n                                  Enter FIRSTNAME:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |%*s%s%*s|\n", leftPadding, "", firstName, boxWidth - textLen - leftPadding, "");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        break;
    }

    // LAST NAME
    while (1) {
        printf("\n\n                                  Enter lastname:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", lastName) != 1) { clear_stdin(); continue; }

        if (strlen(lastName) < 2) {
            printf("\n                            (System): Lastname too short! Try again.\n");
            printf("                            Press any key to try again...");
            getch();
            continue;
        }

        int boxWidth = 90;
        int textLen = strlen(lastName);
        int leftPadding = (boxWidth - textLen) / 2;

        system("cls");
        printf("\n\n                                  Enter LASTNAME:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |%*s%s%*s|\n", leftPadding, "", lastName, boxWidth - textLen - leftPadding, "");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        break;
    }

    // DATE OF BIRTH
    while (1) {
        printf("\n\n                                  Date of Birth (DD/MM/YYYY):\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");

        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", birthD) != 1) { clear_stdin(); continue; }

        if (strlen(birthD) != 10 || birthD[2] != '/' || birthD[5] != '/') {
            printf("\n                            (System): Invalid date format! Use DD/MM/YYYY\n");
            printf("                            Press any key to try again...");
            getch();
            continue;
        }

        int boxWidth = 90;
        int textLen = strlen(birthD);
        int leftPadding = (boxWidth - textLen) / 2;

        system("cls");
        printf("\n\n                                  Date of Birth (DD/MM/YYYY):\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |%*s%s%*s|\n", leftPadding, "", birthD, boxWidth - textLen - leftPadding, "");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        break;
    }

    // SEX
    while (1) {
        printf("\n\n                                  Sex at Birth (Male/Female):\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");

        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", sex) != 1) { clear_stdin(); continue; }

        sex[0] = toupper((unsigned char)sex[0]);
        for (int i = 1; sex[i]; i++) sex[i] = tolower((unsigned char)sex[i]);

        if (strcmp(sex, "Male") != 0 && strcmp(sex, "Female") != 0) {
            printf("\n                            (System): Please enter either 'Male' or 'Female'\n");
            printf("                            Press any key to try again...");
            getch();
            continue;
        }

        int boxWidth = 90;
        int textLen = strlen(sex);
        int leftPadding = (boxWidth - textLen) / 2;

        system("cls");
        printf("\n\n                                  Sex at Birth (Male/Female):\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |%*s%s%*s|\n", leftPadding, "", sex, boxWidth - textLen - leftPadding, "");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        break;
    }

    // ADDRESS (no strict validation)
    printf("\n\n                                  Home Address:\n");
    printf("                                  ------------------------------------------------------------------------------------------\n");
    printf("                                 |                                                                                          |\n");
    printf("                                  ------------------------------------------------------------------------------------------\n");
    printf("\n                                  Type here: ");
    clear_stdin(); // ensure no leftover
    if (!fgets(address, sizeof(address), stdin)) address[0] = '\0';
    address[strcspn(address, "\n")] = 0;

    {
        int boxWidth = 90;
        int textLen = strlen(address);
        int leftPadding = (boxWidth - textLen) / 2;
        system("cls");
        printf("\n\n                                  Home Address:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |%*s%s%*s|\n", leftPadding, "", address, boxWidth - textLen - leftPadding, "");
        printf("                                  ------------------------------------------------------------------------------------------\n");
    }

    // ACCOUNT INFO: username
    while (1) {
        printf("\n\n                                  Create Username:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", username) != 1) { clear_stdin(); continue; }

        if (strcmp(username, "9") == 0) {
            return 0;
        }

        if (strlen(username) < 4) {
            printf("\n                            (System): Username too short! Must be at least 4 characters.\n");
            printf("                            Press any key to try again...");
            getch();
            continue;
        }

        // check if username already exists
        fp = fopen("accounts.txt", "r");
        if (fp) {
            struct Account tmp;
            int exists = 0;
            while (fscanf(fp, "%49[^,],%49[^,],%19[^,],%49[^,],%49[^,],%49[^\n]\n",
                          tmp.username, tmp.password, tmp.role, tmp.course, tmp.firstName, tmp.lastName) == 6) {
                if (strcmp(tmp.username, username) == 0) { exists = 1; break; }
            }
            fclose(fp);
            if (exists) {
                printf("\n                            (System): Username already exists. Choose another.\n");
                printf("                            Press any key to try again...");
                getch();
                continue;
            }
        }

        int boxWidth = 90;
        int textLen = strlen(username);
        int leftPadding = (boxWidth - textLen) / 2;

        system("cls");
        printf("\n\n                                  Create Username:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |%*s%s%*s|\n", leftPadding, "", username, boxWidth - textLen - leftPadding, "");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        break;
    }

    // PASSWORD with confirmation
    while (1) {
        printf("\n\n                                  Create Password:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        inputPassword(password);

        if (strlen(password) < 4) {
            printf("\n                            (System): Password too short! Must be at least 4 characters.\n");
            printf("                            Press any key to try again...");
            getch();
            continue;
        }

        printf("\n\n                                  Confirm Password:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        inputPassword(confirmPassword);

        if (strcmp(password, confirmPassword) != 0) {
            printf("\n                            (System): Passwords do not match! Try again.\n");
            printf("                            Press any key to try again...");
            getch();
            continue;
        }

        system("cls");
        printf("\n\n                                  Password Successfully Set!\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |%*s%s%*s|\n", 40 - 4, "", "********", 40 - 4, ""); // masked display
        printf("                                  ------------------------------------------------------------------------------------------\n");
        break;
    }

    // ROLE and COURSE
    while (1) {
        printf("\n\n                                  Role (Student/Staff):\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", role) != 1) { clear_stdin(); continue; }

        role[0] = toupper((unsigned char)role[0]);
        for (int i = 1; role[i]; i++) role[i] = tolower((unsigned char)role[i]);

        if (strcmp(role, "Student") != 0 && strcmp(role, "Staff") != 0) {
            printf("\n                            (System): Please enter either 'Student' or 'Staff'\n");
            printf("                            Press any key to try again...");
            getch();
            continue;
        }

        if (strcmp(role, "Student") == 0) {
            printf("\n\n                                  Course (e.g., BSIT):\n");
            printf("                                  ------------------------------------------------------------------------------------------\n");
            printf("                                 |                                                                                          |\n");
            printf("                                  ------------------------------------------------------------------------------------------\n");
            printf("\n                                  Type here: ");
            if (scanf(" %[^\n]", course) != 1) strcpy(course, "-");
        } else {
            strcpy(course, "-");
        }
        break;
    }

    // SAVE to file
    fp = fopen("accounts.txt", "a");
    if (fp == NULL) {
        printf("\n(System): Unable to open accounts file for writing.\n");
        return 0;
    }
    // Format: username,password,role,course,firstName,lastName\n
    fprintf(fp, "%s,%s,%s,%s,%s,%s\n", username, password, role, course, firstName, lastName);
    fclose(fp);

    printf("\n\n(System): Account created successfully!\n");
    printf("Username: %s\n", username);
    printf("Role: %s %s\n", role, (strcmp(course, "-") == 0) ? "" : course);
    printf("Press any key to continue...");
    getch();

    return 0;
}

/* inputPassword: reads characters and prints '*' while typing; Enter ends input */
void inputPassword(char *pass) {
    int i = 0;
    char ch;
    while ((ch = getch()) != 13) { // Enter key
        if (ch == 8 && i > 0) {    // Backspace
            printf("\b \b");
            i--;
        } else if (ch >= 32 && ch <= 126 && i < 49) {
            pass[i++] = ch;
            printf("*");
        }
    }
    pass[i] = '\0';
    printf("\n");
}

/* loadingScreen: simple loading animation */
void loadingScreen() {
    int i;
    printf("Loading: ");
    for (i = 0; i <= 20; i++) {
        printf("%c", 219);
        Sleep(50);
    }
    printf(" 100%%\n");
}

/* loginAccount: reads accounts.txt and tries to match username/password */
void loginAccount() {
    struct Account acc;
    char username[50], password[50];
    int foundUser = 0, passwordMatch = 0, attempts = 0;
    FILE *fp;

    while (attempts < 3) {
        system("cls");

        // Open file
        fp = fopen("accounts.txt", "r");
        if (fp == NULL) {
            printf("\n(System): No accounts found. Please create one first.\n");
            printf("Press any key to return...");
            getch();
            return;
        }

        // HEADER DESIGN
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                               * --------------------- / ---------------- /                            |\n");
        printf("                  |                                                          LOGIN ACCOUNT                                                  |\n");
        printf("                  +====================================================================================================================+\n\n");

        // USERNAME INPUT
        printf("\n\n                                  Enter Username:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        clear_stdin();
        if (!fgets(username, sizeof(username), stdin)) { username[0] = '\0'; }
        username[strcspn(username, "\n")] = 0; // remove newline

        // PASSWORD INPUT
        printf("\n\n                                  Enter Password:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        inputPassword(password);

        foundUser = 0;
        passwordMatch = 0;

        // SEARCH ACCOUNT IN FILE (format: username,password,role,course,firstName,lastName)
        rewind(fp);
        while (fscanf(fp, "%49[^,],%49[^,],%19[^,],%49[^,],%49[^,],%49[^\n]\n",
                      acc.username, acc.password, acc.role, acc.course, acc.firstName, acc.lastName) == 6) {
            if (strcmp(username, acc.username) == 0) {
                foundUser = 1;
                if (strcmp(password, acc.password) == 0) {
                    passwordMatch = 1;
                }
                break;
            }
        }
        fclose(fp);

        // VERIFY LOGIN STATUS
        if (!foundUser) {
            printf("\n\n                            (System): Username not found! Try again.\n");
            attempts++;
        } else if (!passwordMatch) {
            printf("\n\n                            (System): Incorrect password! Try again.\n");
            attempts++;
        } else {
            printf("\n\n                            (System): Logging in...");
            loadingScreen();
            system("cls");
            printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
            printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
            printf("                  +----------------------------------------------------------------------------------------------------------------------\n");
            printf("\n");
            printf("                                    \x1b[32mLogin Successful!\x1b[0m Welcome, %s (%s)", acc.username, acc.role);
            if (strcmp(acc.role, "Student") == 0 && strlen(acc.course) > 0 && strcmp(acc.course, "-") != 0)
                printf(" - %s", acc.course);
            printf("\n\n                                    Press any key to continue...");
            getch();
            return;
        }

        // RETRY HANDLING
        if (attempts < 3) {
            printf("\n\n                            Attempts left: %d", 3 - attempts);
            printf("\n                            Press any key to try again...");
            getch();
        } else {
            printf("\n\n                            (System): Too many failed attempts.\n");
            printf("                            Returning to main menu...");
            Sleep(2000);
            return;
        }
    }
}

/* forgotPassword: reveals password for a username (simple, not secure) */
void forgotPassword() {
    struct Account acc;
    char username[50];
    int found = 0;
    FILE *fp = fopen("accounts.txt", "r");

    if (fp == NULL) {
        printf("\n(System): No accounts found.\n");
        return;
    }

    printf("\nEnter your username to recover password: ");
    clear_stdin();
    if (!fgets(username, sizeof(username), stdin)) username[0] = '\0';
    username[strcspn(username, "\n")] = 0;

    // File format: username,password,role,course,firstName,lastName
    while (fscanf(fp, "%49[^,],%49[^,],%19[^,],%49[^,],%49[^,],%49[^\n]\n",
                  acc.username, acc.password, acc.role, acc.course, acc.firstName, acc.lastName) == 6) {
        if (strcmp(username, acc.username) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found)
        printf("\n(System): Your password is: %s\n", acc.password);
    else
        printf("\n(System): Username not found.\n");
}
