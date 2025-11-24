#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

#define ACC_FILE "accounts.txt"
#define TEMP_FILE "accounts_tmp.txt"

struct Account {
    char username[50];
    char password[100];
    char role[20];
    char course[50];
    char firstName[50];
    char lastName[50];
    char Department[100];
    char idNumber[30];
    char email[100];
    char address[200];
};


void menu();
int createAccount();
void loginAccount();
void forgotPassword();
void inputPassword(char *pass);
void loadingScreen();
void clear_stdin();
void generateId(const char* role, const char* department, char* idNumber);
void deleteAllUserData();

void BSCS1_Regular_Schedule();
void BSOA_Regular_Schedule();
void EDUC_Regular_Schedule();


void aboutUs(struct Account *acc);
void registrarDash(struct Account *acc);
void studentDashboard(struct Account *acc);
void facultyDashboard(struct Account *acc);
void adminDashboard(struct Account *acc);


void showStudentProfile(struct Account *acc);
void showFacultyProfile(struct Account *acc);
void editProfile(struct Account *acc);
int updateAccountInFile(struct Account *acc); 
int changePasswordAccount(struct Account *acc);
void viewAllAccounts();
void invalid_StudentID_Display();
void invalid_Display();
void usernotfound();
void noaccfound();
void invalidUser();
void invalid_Option();



void sanitize_for_csv(char *s);

int main() {
    menu();
    return 0;
}



void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void inputPassword(char *pass) {
    int i = 0;
    char ch;
    while ((ch = getch()) != 13) { 
        if (ch == 8 && i > 0) { 
            printf("\b \b");
            i--;
        } else if (ch >= 32 && ch <= 126 && i < 99) {
            pass[i++] = ch;
            printf("*");
        }
    }
    pass[i] = '\0';
    printf("\n");
}

void loadingScreen() {
    int i;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("                                 Loading: ");
    for (i = 0; i <= 40; i++) {
        printf("%c", 219);
        Sleep(20);
    }
    printf(" 100%%\n");
}

void sanitize_for_csv(char *s) {
  
    for (int i = 0; s[i]; ++i) {
        if (s[i] == ',') s[i] = ';';
    }
}



void generateId(const char* role, const char* department, char* idNumber) {
    static int seeded = 0;
    if (!seeded) { srand((unsigned int)time(NULL)); seeded = 1; }
    int randomNum = rand() % 900000 + 100000; 

    if (strcmp(role, "Student") == 0) {
        if (strstr(department, "BSCS") || strstr(department, "COMPUTER") || strstr(department, "CS"))
            sprintf(idNumber, "STU-CS-%06d", randomNum);
        else if (strstr(department, "BSOA") || strstr(department, "OFFICE") || strstr(department, "OA"))
            sprintf(idNumber, "STU-OA-%06d", randomNum);
        else if (strstr(department, "BSVTVTED") || strstr(department, "ED") || strstr(department, "TEACH"))
            sprintf(idNumber, "STU-ED-%06d", randomNum);
        else
            sprintf(idNumber, "STU-GEN-%06d", randomNum);
    } else if (strcmp(role, "Faculty") == 0) {
        if (strstr(department, "COMPUTER") || strstr(department, "CS"))
            sprintf(idNumber, "FAC-CS-%06d", randomNum);
        else if (strstr(department, "OFFICE") || strstr(department, "OA"))
            sprintf(idNumber, "FAC-OA-%06d", randomNum);
        else if (strstr(department, "TEACHER") || strstr(department, "ED"))
            sprintf(idNumber, "FAC-ED-%06d", randomNum);
        else
            sprintf(idNumber, "FAC-GEN-%06d", randomNum);
    } else if (strcmp(role, "Admin")==0){
    	if (strstr(department, "Registrar") || strstr(department, "RGR"))
    	sprintf(idNumber,"ADM-RGR-%06d", randomNum);
	}else 
        sprintf(idNumber, "ADM-%06d", randomNum % 999999);
    }




void menu() {
    char choice;
    while (1) {
        system("cls");
        printf("\033[36;5m");
      system("color E9");
    printf("                  [-]********************************************************************************************************************[-]\n");
    printf("                  [-]                                                                                                                    [-]\n");
    printf("                  [-]                                           P   H   I   L   T   E   C   H                                            [-]\n");
    printf("                  [-]                                                                                                                    [-]\n");
    printf("                  [-]====================================================================================================================[-]\n");
    printf("                  [-]||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]====================================================================================================================[-]\n");
    printf("                  [-]********************************************************************************************************************[-]\n");    
    printf("                  [-]                                                                                                                    [-]\n");
	printf("                  [-]                          ++_________________________________________________________++                             [-]\n");
	printf("                  [-]                          ++                                                         ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]  [1]   CREATE ACCOUNT      [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]                            [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++             [-]                          [-]            ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]   [2]   LOGIN              [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]                            [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++             [-]                          [-]            ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]   [3]   FORGET PASSWORD    [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]                            [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++             [-]                          [-]            ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]   [4]   DELETE ALL DATA    [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]                            [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
    printf("                  [-]                          ++             [-]                          [-]            ++                             [-]\n");
 	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]   [5]   EXIT               [-]    ++      ++                             [-]\n");    
	printf("                  [-]                          ++      ++   [-]                            [-]    ++      ++                             [-]\n");    
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");    
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");    
	printf("                  [-]                          ++                                                         ++                             [-]\n");    
	printf("                  [-]                          ++_________________________________________________________++                             [-]\n");    
	printf("                  [-]                                                                                                                    [-]\n");    
    printf("                  [-]                                                                                                                    [-]\n");
	printf("                  [-]********************************************************************************************************************[-]\n");
	printf("                  [-]====================================================================================================================[-]\n");
	 printf("Enter your choice: ");
        choice = getch();
        printf("%c\n", choice);

        switch (choice) {
            case '1': createAccount(); break;
            case '2': loginAccount(); break;
            case '3': forgotPassword(); break;
            case '4':  deleteAllUserData(); break;
            case '5':
                printf("\nThank you for using the system!\n");
                exit(0);
            default:
            	system("cls");
                invalid_Display();
                getch();
                continue;
        }

        printf("\nPress any key to return to main menu...");
        getch();
    }
}



int createAccount() {
    char firstName[50], lastName[50], birthD[20], sex[10], address[200], email[100];
    char username[50], password[100], confirmPassword[100];
    char role[20], course[50], department[100];
    char idNumber[30];
    FILE *fp;

 
    while (1) {
        system("cls");
        printf("\033[36;5m");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                       * --------------------- / ---------------- /                       [ 9 ] Back  |\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Personal Information\n\n");

        printf("\n\n                                  Enter firstname:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", firstName) != 1) { clear_stdin(); continue; }

        if (strcmp(firstName, "9") == 0) return 0;

        if (strlen(firstName) < 2) {
            printf("\n(System): Firstname too short! Try again.\n");
            getch();
            continue;
        }
        break;
    }


    while (1) {
        system("cls");
        printf("\033[36;5m");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Personal Information\n\n");

        printf("\n\n                                  Enter lastname:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", lastName) != 1) { clear_stdin(); continue; }
        if (strcmp(lastName, "9") == 0) return 0;
        if (strlen(lastName) < 2) {
            printf("\n(System): Lastname too short! Try again.\n");
            getch();
            continue;
        }
        break;
    }


    while (1) {
        system("cls");
        printf("\033[36;5m");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Personal Information\n\n");

        printf("\n\n                                  Date of Birth (DD/MM/YYYY):\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", birthD) != 1) { clear_stdin(); continue; }
        if (strcmp(birthD, "9") == 0) return 0;
        if (strlen(birthD) != 10 || birthD[2] != '/' || birthD[5] != '/') {
            printf("\n(System): Invalid date format! Use DD/MM/YYYY\n");
            getch();
            continue;
        }
        break;
    }


    while (1) {
        system("cls");
        printf("\033[36;5m");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Personal Information\n\n");

        printf("\n\n                                  Sex at Birth (Male/Female):\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", sex) != 1) { clear_stdin(); continue; }
        if (strcmp(sex, "9") == 0) return 0;
        sex[0] = toupper(sex[0]);
        for (int i = 1; sex[i]; i++) sex[i] = tolower(sex[i]);
        if (strcmp(sex, "Male") != 0 && strcmp(sex, "Female") != 0) {
            printf("\n(System): Please enter either 'Male' or 'Female'\n");
            getch();
            continue;
        }
        break;
    }


    clear_stdin();
    while (1) {
        system("cls");
        printf("\033[36;5m");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Personal Information\n\n");

        printf("\n\n                                  Home Address:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        fgets(address, sizeof(address), stdin);
        address[strcspn(address, "\n")] = 0;
        if (strcmp(address, "9") == 0) return 0;
        if (strlen(address) < 3) {
            printf("\n(System): Address too short!\n");
            getch();
            continue;
        }
        break;
    }


    while (1) {
        system("cls");
        printf("\033[36;5m");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Personal Information\n\n");

        printf("\n\n                                  Enter Email:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", email) != 1) { clear_stdin(); continue; }
        if (strcmp(email, "9") == 0) return 0;
        if (!strchr(email, '@') || !strchr(email, '.')) {
            printf("\n(System): Invalid email format!\n");
            getch();
            continue;
        }
        break;
    }


    while (1) {
        system("cls");
        printf("\033[36;5m");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Account Information\n\n");

        printf("\n\n                                  Create Username:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", username) != 1) { clear_stdin(); continue; }
        if (strcmp(username, "9") == 0) return 0;
        if (strlen(username) < 4) {
            printf("\n(System): Username too short!\n");
            getch();
            continue;
        }

        fp = fopen(ACC_FILE, "r");
        if (fp) {
            struct Account tmp;
            int exists = 0;
            while (fscanf(fp,
                "%49[^,],%99[^,],%19[^,],%49[^,],%49[^,],%49[^,],%99[^,],%29[^,],%99[^,],%199[^\n]\n",
                tmp.username, tmp.password, tmp.role, tmp.course, tmp.firstName,
                tmp.lastName, tmp.Department, tmp.idNumber, tmp.email, tmp.address) == 10) {
                if (strcmp(tmp.username, username) == 0) { exists = 1; break; }
            }
            fclose(fp);
            if (exists) {
                printf("\n(System): Username already exists!\n");
                getch();
                continue;
            }
        }
        break;
    }

 
    while (1) {
        system("cls");
        printf("\033[36;5m");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Account Information\n\n");

        printf("\n\n                                  Create Password:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        inputPassword(password);
        if (strlen(password) < 4) {
            printf("\n(System): Password too short!\n");
            getch();
            continue;
        }
        printf("\n                                  Confirm Password: \n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        
        inputPassword(confirmPassword);
        if (strcmp(password, confirmPassword) != 0) {
            printf("\n(System): Passwords do not match!\n");
            getch();
            continue;
        }
        break;
    }

 
    while (1) {
        system("cls");
        printf("\033[36;5m");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Position Selection\n\n");

        printf("\n\n                                  Role (Student/Faculty/Admin): ");
        if (scanf(" %[^\n]", role) != 1) { clear_stdin(); continue; }
        if (strcmp(role, "9") == 0) return 0;
        role[0] = toupper(role[0]);
        for (int i = 1; role[i]; i++) role[i] = tolower(role[i]);

        if (strcmp(role, "Student") != 0 && strcmp(role, "Faculty") != 0 && strcmp(role, "Admin") != 0) {
            printf("\n(System): Please enter 'Student', 'Faculty', or 'Admin'.\n");
            getch();
            continue;
        }

        if (strcmp(role, "Faculty") == 0) {
        	printf("\033[36;5m");
        	printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]           S   E   L   E   C   T     D   E   P   A   R   T   M   E   N   T             [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n"); 
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [C] COMPUTER SCIENCE                                              [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [O] OFFICE ADMIN                                                  [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [T] TEACHER EDUCATION                                             [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]                                                                                       [-]\n");
   	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
   	printf("                  [-]                                                                                       [-]\n");
    printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n"); 
            printf("                                  ======================================================\n");
            char ch = getch();
            if (ch == 'c' || ch == 'C') strcpy(department, "COMPUTER SCIENCE DEPARTMENT");
            else if (ch == 'o' || ch == 'O') strcpy(department, "OFFICE ADMINISTRATION DEPARTMENT");
            else if (ch == 't' || ch == 'T') strcpy(department, "TEACHER EDUCATION DEPARTMENT");
            else continue;
            strcpy(course, "-");
        } else if (strcmp(role, "Student") == 0) {
        	printf("\033[36;5m");
        	printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]                    S   E   L   E   C   T     C   O  U   R   S   E                      [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n"); 
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [1] BSCS                                                          [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [2] BSOA                                                          [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]                     [3] BTVTED                                                        [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]                                                                                       [-]\n");
   	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
   	printf("                  [-]                                                                                       [-]\n");
    printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n"); 
            char ch = getch();
            if (ch == '1') strcpy(course, "BSCS");
            else if (ch == '2') strcpy(course, "BSOA");
            else if (ch == '3') strcpy(course, "BSVTVTED");
            else continue;
            strcpy(department, "-");
        } else if (strcmp(role, "Admin") == 0) {
            printf("\033[36;5m");
            printf("                  [-]***************************************************************************************[-]\n");
            printf("                  [-]                                                                                       [-]\n");
            printf("                  [-]           S   E   L   E   C   T     D   E   P   A   R   T   M   E   N   T             [-]\n");
            printf("                  [-]                                                                                       [-]\n");
            printf("                  [-]=======================================================================================[-]\n");
            printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
            printf("                  [-]=======================================================================================[-]\n");
            printf("                  [-]***************************************************************************************[-]\n");
            printf("                  [-]                                                                                       [-]\n"); 
            printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
            printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
            printf("                  [-]                     [A] Administration                                               [-]\n");
            printf("                  [-]                                                                                       [-]\n");
            printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
            printf("                  [-]                     [R] Registrar                                                    [-]\n");
            printf("                  [-]                                                                                       [-]\n");
            printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
            printf("                  [-]                                                                                       [-]\n");
            printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
            printf("                  [-]                                                                                       [-]\n");
            printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n"); 
            char ch = getch();
            if (ch == 'a' || ch == 'A') strcpy(department, "Administration");
            else if (ch == 'r' || ch == 'R') strcpy(department, "Registrar");
            else continue;
            strcpy(course, "-");
        }
        break;
    }

 
    sanitize_for_csv(address);
    sanitize_for_csv(email);

 
    generateId(role, (strcmp(role, "Student") == 0) ? course : department, idNumber);
    loadingScreen();

       fp = fopen(ACC_FILE, "a");
    if (!fp) {
        printf("\n(System): Error opening file for writing!\n");
        return 0;
    }

    fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            username, password, role, course, firstName, lastName,
            department, idNumber, email, address);
    fclose(fp);

    printf("\n(System): Account created and saved successfully!\n");
    printf("Username: %s\nRole: %s\nGenerated ID: %s\n", username, role, idNumber);

getch(); 

return 1;  
}

    
 


 

void forgotPassword() {
    struct Account acc;
    char username[50];
    int found = 0;
    FILE *fp = fopen(ACC_FILE, "r");

    if (fp == NULL) {
        printf("\n(System): No accounts found.\n");
        getch();
        return;
    }

    printf("\nEnter your username to recover password: ");
    
    if (!fgets(username, sizeof(username), stdin)) username[0] = '\0';
    username[strcspn(username, "\n")] = 0;

    while (fscanf(fp,
        "%49[^,],%99[^,],%19[^,],%49[^,],%49[^,],%49[^,],%99[^,],%29[^,],%99[^,],%199[^\n]\n",
        acc.username, acc.password, acc.role, acc.course, acc.firstName,
        acc.lastName, acc.Department, acc.idNumber, acc.email, acc.address) == 10) {
        if (strcmp(username, acc.username) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found)
        printf("\n(System): Your password is: %s\n", acc.password);
    else
        usernotfound();

    printf("Press any key to return...");
    getch();
}

  
  
int updateAccountInFile(struct Account *acc) {
    FILE *fp = fopen(ACC_FILE, "r");
    FILE *tmp = fopen(TEMP_FILE, "w");
    int replaced = 0;
    if (!tmp) return 0;
    if (!fp) {
        fclose(tmp);
        return 0;
    }

    struct Account tmpAcc;
    while (fscanf(fp,
        "%49[^,],%99[^,],%19[^,],%49[^,],%49[^,],%49[^,],%99[^,],%29[^,],%99[^,],%199[^\n]\n",
        tmpAcc.username, tmpAcc.password, tmpAcc.role, tmpAcc.course, tmpAcc.firstName,
        tmpAcc.lastName, tmpAcc.Department, tmpAcc.idNumber, tmpAcc.email, tmpAcc.address) == 10) {

        if (strcmp(tmpAcc.username, acc->username) == 0) {
            
            sanitize_for_csv(acc->address);
            sanitize_for_csv(acc->email);
            fprintf(tmp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                acc->username, acc->password, acc->role, acc->course,
                acc->firstName, acc->lastName, acc->Department, acc->idNumber,
                acc->email, acc->address);
            replaced = 1;
        } else {
         
            sanitize_for_csv(tmpAcc.address);
            sanitize_for_csv(tmpAcc.email);
            fprintf(tmp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                tmpAcc.username, tmpAcc.password, tmpAcc.role, tmpAcc.course,
                tmpAcc.firstName, tmpAcc.lastName, tmpAcc.Department, tmpAcc.idNumber,
                tmpAcc.email, tmpAcc.address);
        }
    }

    fclose(fp);
    fclose(tmp);

    if (!replaced) {
      
        remove(TEMP_FILE);
        return 0;
    } else {
        
        remove(ACC_FILE);
        rename(TEMP_FILE, ACC_FILE);
        return 1;
    }
}

 
 
int changePasswordAccount(struct Account *acc) {
    char oldpass[100], newpass[100], confirm[100];
    printf("Enter current password: ");
    inputPassword(oldpass);
    if (strcmp(oldpass, acc->password) != 0) {
        printf("\n(System): Current password incorrect.\n");
        getch();
        return 0;
    }
    while (1) {
        printf("Enter new password: ");
        inputPassword(newpass);
        if (strlen(newpass) < 4) {
            printf("(System): New password too short (min 4 chars).\n");
            getch();
            continue;
        }
        printf("Confirm new password: ");
        inputPassword(confirm);
        if (strcmp(newpass, confirm) != 0) {
            printf("(System): Passwords do not match. Try again.\n");
            getch();
            continue;
        }
        break;
    }
    
    strcpy(acc->password, newpass);
    if (updateAccountInFile(acc)) {
        printf("\n(System): Password changed successfully.\n");
        getch();
        return 1;
    } else {
        printf("\n(System): Failed to update password in file.\n");
        getch();
        return 0;
    }
}

 
void editProfile(struct Account *acc) {
    char newEmail[100], newAddress[200];
    system("cls");
    printf("\033[36;5m");
    printf("=====================================================\n");
    printf("|                 EDIT PROFILE                      |\n");
    printf("=====================================================\n");
    printf("Current Email  : %s\n", acc->email);
    printf("Current Address: %s\n", acc->address);
    printf("-----------------------------------------------------\n");
    printf("Enter new email (or press enter to keep): ");
    clear_stdin();
    if (!fgets(newEmail, sizeof(newEmail), stdin)) newEmail[0] = '\0';
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Enter new address (or press enter to keep): ");
    if (!fgets(newAddress, sizeof(newAddress), stdin)) newAddress[0] = '\0';
    newAddress[strcspn(newAddress, "\n")] = 0;

    if (strlen(newEmail) > 0) {
        if (!strchr(newEmail, '@') || !strchr(newEmail, '.')) {
            printf("\n(System): Invalid email format. No changes made.\n");
            getch();
            return;
        }
        strncpy(acc->email, newEmail, sizeof(acc->email)-1);
        acc->email[sizeof(acc->email)-1] = '\0';
    }
    if (strlen(newAddress) > 0) {
        strncpy(acc->address, newAddress, sizeof(acc->address)-1);
        acc->address[sizeof(acc->address)-1] = '\0';
    }

    
    sanitize_for_csv(acc->email);
    sanitize_for_csv(acc->address);
    if (updateAccountInFile(acc)) {
        printf("\n(System): Profile updated successfully.\n");
    } else {
        printf("\n(System): Failed to update profile in file.\n");
    }
    printf("Press any key to return...");
    getch();
}

 

void showStudentProfile(struct Account *acc) {
    system("cls");
    printf("\033[36;5m");
      system("color E9");
    printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]             S   T   U   D   E   N   T     P   R   O   F   I   L   E                   [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]***************************************************************************************[-]\n");    
    printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                       NAME    : %s %s\n", acc->firstName, acc->lastName);
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                       USERNAME: %s\n", acc->username);                  
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                       EMAIL   : %s\n", acc->email);                     
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                       COURSE  : %s\n", acc->course);  
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                       DEPARTMENT: %s\n", acc->Department);     
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                          ID   : %s\n", acc->idNumber);
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                       ADDRESS : %s\n", acc->address);
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                   ROLE    : %s\n", acc->role);
	printf("                  [-]                                                                                       [-]\n");
    printf("                              ++      ++=========================================++      ++             \n");
 	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]                                                                                       [-]\n");    
	printf("                  [-]                                                                                       [-]\n");   
	printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n");    
    getch();
}

void showFacultyProfile(struct Account *acc) {
    system("cls");
    printf("\033[36;5m");
    system("color E9");
      printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]             F   A   C   U   L   T   Y     P   R   O   F   I   L   E                   [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]***************************************************************************************[-]\n");    
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]           Name    : %s %s\n", acc->firstName, acc->lastName);
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]           Username: %s\n", acc->username);
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]           Email   : %s\n", acc->email);
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]           Department: %s\n", acc->Department);
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]            ID      : %s\n", acc->idNumber);
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]           Address : %s\n", acc->address);
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
   	printf("                  [-]            Role    : %s\n", acc->role);
   	printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
   	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
   	printf("                  [-]                                                                                       [-]\n");
    printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n");   
    getch();
}

 

void studentDashboard(struct Account *acc) {
    char ch;
    while (1) {
        system("cls");
        printf("\033[36;5m");
        system("color E9");
     printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]          S   T   U   D   E   N   T     D   A   S   H   B   O   A   R   D              [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]           Welcome: %s %s   /n", acc->firstName, acc->lastName);
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]            Course : %s     /n", acc->course);
    printf("                  [-]                                                                                       [-]\n");    
	printf("                  [-]             ID     : %s     /n",  acc->idNumber);
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [1] VIEW SCHEDULE                                                 [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [2] VIEW PROFILE                                                  [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [3] EDIT PROFILE                                                  [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [4] ABOUT US                                                      [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]                     [5] CHANGE PASSWORD                                               [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]                     [6] LOGOUT                                                        [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
   	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
   	printf("                  [-]                                                                                       [-]\n");
    printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n");  
        ch = getch();
        printf("%c\n", ch);
        if (ch == '1') {
            system("cls");
            if (strcmp(acc->course, "BSCS") == 0) {
                
               
                BSCS1_Regular_Schedule();
            } else if (strcmp(acc->course, "BSOA") == 0) {
                BSOA_Regular_Schedule();
            } else if (strcmp(acc->course, "BSVTVTED") == 0) {
                EDUC_Regular_Schedule();
            } else {
                printf("No schedule available for %s\n", acc->course);
            }
            printf("\nPress any key to return to dashboard...");
            getch();
        } else if (ch == '2') {
            showStudentProfile(acc);
        } else if (ch == '3') {
            editProfile(acc);
        } else if (ch == '4'){
        	aboutUs(acc);
		}else if (ch == '5') {
            changePasswordAccount(acc);
        } else if (ch == '6') {
            printf("Logging out...\n");
            Sleep(600);
            return;
        } else {
        	system("cls");
             invalid_Option();
            getch();
        }
    }
}

void facultyDashboard(struct Account *acc) {
    char ch;
    while (1) {
        system("cls");
        printf("\033[36;5m");
        system("color E9");
        printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         F   A   C   U   L   T   Y     D   A   S   H   B   O   A   R   D               [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]***************************************************************************************[-]\n");    
    printf("                  [-]          Welcome Admin: %s %s                                                         [-]\n", acc->firstName, acc->lastName);
	printf("                  [-]            Department: %s                                                             [-]\n" , acc->Department);
	printf("                  [-]            ID: %s                                                                     [-]\n" , acc->idNumber);
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [1] VIEW TEACHING SCHEDULE                                        [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [2] VIEW PROFILE                                                  [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [3] EDIT PROFILE                                                  [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [4] ABOUT US                                                      [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]                     [5] CHANGE PASSWORD                                               [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]                     [6] LOGOUT                                                        [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n"); 
        printf("Enter choice: ");
        ch = getch();
        printf("%c\n", ch);
        if (ch == '1') {
            system("cls");
            printf("Teaching schedule (sample):\n");
            printf("- Monday 8:00-10:00  COMP101 (Main)\n");
            printf("- Wednesday 10:00-12:00  COMP102 (Annex)\n");
            printf("- Friday 1:00-3:00  LAB (Main)\n");
            printf("\nPress any key to return...");
            getch();
        } else if (ch == '2') {
            showFacultyProfile(acc);
        } else if (ch == '3') {
            editProfile(acc);
        } else if (ch == '4'){
        	aboutUs(acc);
		} else if (ch == '5') {
            changePasswordAccount(acc);
        } else if (ch == '6') {
            printf("Logging out...\n");
            Sleep(600);
            return;
        } else {
        	system("cls");
            invalid_Option();
            getch();
        }
    }
}

void viewAllAccounts() {
    FILE *fp = fopen(ACC_FILE, "r");
    if (!fp) {
        printf("\n(System): No accounts file found!\n");
        getch();
        return;
    }
    struct Account tmp;
    int idx = 0;
    system("cls");
    printf("\033[36;5m");
    printf("=====================================================\n");
    printf("|                  ALL ACCOUNTS                      |\n");
    printf("=====================================================\n");
    printf("No.  Username    |     Role   |   Course   | ID\n");
    printf("-----------------------------------------------------\n");
    while (fscanf(fp,
        "%49[^,],%99[^,],%19[^,],%49[^,],%49[^,],%49[^,],%99[^,],%29[^,],%99[^,],%199[^\n]\n",
        tmp.username, tmp.password, tmp.role, tmp.course, tmp.firstName,
        tmp.lastName, tmp.Department, tmp.idNumber, tmp.email, tmp.address) == 10) {
        idx++;
        printf("%-4d %-16s %-9s %-8s %s\n", idx, tmp.username, tmp.role, tmp.course, tmp.idNumber);
        if (idx % 20 == 0) {  
            printf("\nPress any key to continue...");
            getch();
            system("cls");
        }
    }
    fclose(fp);
    if (idx == 0) printf("No accounts found.\n");
    printf("\nPress any key to return...");
    getch();
}
void deleteAllUserData() {
    FILE *fp = fopen("accounts.txt", "w");
    if (!fp) {
        printf("\n(System): Failed to open accounts file.\n");
        getch();
        return;
    }
    fclose(fp);
    printf("\n(System): All user data deleted successfully!\n");
    getch();
}

void adminDashboard(struct Account *acc) {
    char ch;
    while (1) {
        system("cls");
        printf("\033[36;5m");
        system("color E9");
        printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]                A   D   M   I   N     D   A   S   H   B   O   A   R   D                [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]***************************************************************************************[-]\n");    
    printf("                  [-]          Welcome Admin: %s %s                                                         [-]\n", acc->firstName, acc->lastName);                     
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]            ID: %s                                                                     [-]\n" , acc->idNumber);                                                                
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [1] VIEW ALL ACOOUNT                                              [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [2] CHANGE PASSWORD                                               [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [3] LOGOUT                                                        [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]                                                                                       [-]\n");
    printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n");   
        printf("Enter choice: ");
        ch = getch();
        printf("%c\n", ch);
        if (ch == '1') {
            viewAllAccounts();
        } else if (ch == '2') {
            changePasswordAccount(acc);
        } else if (ch == '3') {
            printf("Logging out...\n");
            Sleep(600);
            return;
        } else {
        	system("cls");
             invalid_Option();
            getch();
        }
    }
}

 

void BSOA_Regular_Schedule() {
	printf("\n                   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                                              WEEKLY SCHEDULE                                                   |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                                              COURSE: BSOA FIRST YEAR                                           |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|          ?     ?     ?     ?     ?     ?     ?     ?      ?      ?      ?      ?      ?      ?      ?      ?      ?   |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|      TIME       |     MONDAY   |    TUESDAY    |   WEDNESDAY   |   THURSDAY    |     FRIDAY    |    SATURDAY   |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    7:00-8:00    |              |               |               |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    8:00-8:45    |              |               |               |               |               |  NSTP1 404-   |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                 |              |               |               |               |               |  ROOM  MAIN   |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");   
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    8:45-9:00    |                                  BREAK TIME                                                  |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|   9:00-10:00    |              |               |               |               |               |  NSTP1 404-   |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½  ROOM MAIN    |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|   10;00-10:45   |              |               |               |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|   10:45-11:15   |                                  LUNCH BREAK                                                 |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|   11:15-12:00   |              |               |               |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½  GE104 104-   ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½  GE101 404-   |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    12:00-1:00   |              |               |  ANNEX        |               |               |  MAIN.        |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½               ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    1:00-2:00    |              | QACC102LEC    |               |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½ 411-MAIN      |~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    2:00-2:45    |              |               | PATHFIT 104   |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                 |              |               | ANNEX         |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    2:45-3:00    |                                  BREAK TIME                                                  |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    3:00-4:00    |  PLS 102     |               | PATHFIT 104   |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                 |  ANNEX       | QACc102LEC    | ANNEX         |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½ CL2-MAIN      ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    4:00-4:45    | QACC101 102- |               | GE2 104       |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                 | ANNEX        |               | ANNEX         |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    4:45-5:15    |                                  BREAK TIME                                                  |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    5:15-6:00    | QACC101 102- | QACC102LEC    | GE2 104       |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                 | ANNEX        | ANNEX         | ANNEX         |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    6:00-7:00    |              |               |               |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");



    
    
    
    
    }
    

void EDUC_Regular_Schedule() {
printf("\n                   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                                              WEEKLY SCHEDULE                                                   |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                                              COURSE: EDUC FIRST YEAR                                          |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|          ?     ?     ?     ?     ?     ?     ?     ?      ?      ?      ?      ?      ?      ?      ?      ?      ?   |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|      TIME       |     MONDAY   |    TUESDAY    |   WEDNESDAY   |   THURSDAY    |     FRIDAY    |    SATURDAY   |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    7:00-8:00    |              |               |               |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    8:00-8:45    | TLE101 LAB   |               |               |               |               | FCC101 404    |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                 | CL2 MAIN     |               |               |               |               | MAIN          |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");   
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    8:45-9:00    |                                  BREAK TIME                                                  |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|   9:00-10:00    |              |               |               |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                 | TLE101 LAB   |               |               |               |               | FCC101 404    |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½ CL2 MAIN     ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½ MAIN          |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|   10;00-10:45   |              |               |               |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                 |              |               |               |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|   10:45-11:15   |                                  LUNCH BREAK                                                 |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|   11:15-12:00   |              |               |               |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                 |              |               | GE102 |104    |               |               | NSTP1 403     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½ ANNEX         ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½ MAIN          |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    12:00-1:00   |              |               |               |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½              ÃƒÂ¯Ã‚Â¿Ã‚Â½               ÃƒÂ¯Ã‚Â¿Ã‚Â½               ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    1:00-2:00    | TLE102 404     | GE102 403   |               |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½ MAIN         ÃƒÂ¯Ã‚Â¿Ã‚Â½ MAIN          |~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    2:00-2:45    |              |               | PATHFIT1 104  |               |               | FCC102 404    |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                 |              |               | ANNEX         |               |               | MAIN          |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    2:45-3:00    |                                  BREAK TIME                                                  |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    3:00-4:00    | PLS 102      |               | PATHFIT1 104  |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                 | ANNEX        | TLE101 LEC    | ANNEX         |               |               | FCC102 404    |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½ 403-MAIN      ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½ MAIN          |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    4:00-4:45    |              |               | GE103 104     |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|                 |              |               | ANNEX         |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    4:45-5:15    |                                  BREAK TIME                                                  |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    5:15-6:00    |              |               |               |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½ GE103 104     ÃƒÂ¯Ã‚Â¿Ã‚Â½               ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
    printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|    6:00-7:00    |              |               | ANNEX         |               |               |               |ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |ÃƒÂ¯Ã‚Â¿Ã‚Â½|~~~~~~~~~~~~~~~~~ÃƒÂ¯Ã‚Â¿Ã‚Â½~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|ÃƒÂ¯Ã‚Â¿Ã‚Â½|\n");
	printf("                     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");



    
}


void BSCS1_Regular_Schedule() {
	
	printf("\n                   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|                                              WEEKLY SCHEDULE                                                   |ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|                                              COURSE: BSCS1M1                                                   |ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|          ?     ?     ?     ?     ?     ?     ?     ?      ?      ?      ?      ?      ?      ?      ?      ?   |ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|      TIME       |     MONDAY   |    TUESDAY    |   WEDNESDAY   |   THURSDAY    |     FRIDAY    |    SATURDAY   |ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|    7:00-8:00    |              |               |               |               |               |               |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|    8:00-8:45    |              |               |               |               |               |  NSTP1 404    |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|                 |              |               |               |               |               |    MAIN       |ÃƒÆ’Ã¢â‚¬â€|\n");   
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|    8:45-9:00    |                      B    R    E   A   R   K   T   I   M   E                                 |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |A-|                                |               |               |               |               |               |A-|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|   9:00-10:00    |              |               |               |               |               |  NSTP1 404    |ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|     MAIN      |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|   10;00-10:45   |              |               |               |               |               |               |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|   10:45-11:15   |                    L   U   N   C   H   B   R   E   A   R   K                                 |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|                 | CC111  LEC   |               |               |               |               |               |ÃƒÆ’Ã¢â‚¬â€|\n"); 
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|   11:15-12:00   |  406-MAIN    |               |               |  CC112 LEC    |               |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|               |~~~~~~~~~~~~~~~|  405-MAIN     |  GE111 404    |ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|    12:00-1:00   |              |               |  GE113 104    |               |               |     MAIN      |ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~|              |~~~~~~~~~~~~~~~|    ANNEX      |~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|               |ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|                 |  CC112 CL1   |               |               |               | CC111 LEC     |               |ÃƒÆ’Ã¢â‚¬â€|\n"); 
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|    1:00-2:00    |    MAIN      |               |               |               |  406-MAIN     |               |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~|              |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|    2:00-2:45    |              |               |  PATHFIT 1    |               |               |               |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|                 |              |               |  104-ANNEX    |               |               |               |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|    2:45-3:00    |                        B   R   E   A   K   T   I   M   E                                     |ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|    3:00-4:00    |   PLS 102    |               |  PATHFIT 1    |               |               |               |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|                 |    MAIN      |               |  104-ANNEX    |               |               |               |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|    4:00-4:45    |              |               |  GE112 104    |               |               |               |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|                 |              |               |   ANNEX       |               |               |               |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|    4:45-5:15    |                                  BREAK TIME                                                  |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|    5:15-6:00    |              |               |  GE112 104    |               |               |               |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|                 |              |               |   ANNEX       |               |               |               |ÃƒÆ’Ã¢â‚¬â€|\n");
    printf("                     |ÃƒÆ’Ã¢â‚¬â€|    6:00-7:00    |              |               |               |               |               |               |ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |ÃƒÆ’Ã¢â‚¬â€|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|ÃƒÆ’Ã¢â‚¬â€|\n");
	printf("                     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");





}




void invalid_StudentID_Display() {
	printf("\033[36;5m");
	printf("                                               __-----_---__-----__-_---_-__----_-__--_-__---___-----__--_\n");
    printf("                                              |  _______________________________________________________  |\n");
    printf("                                              |:|                       ERROR!!!!!                      |:|\n");
    printf("                                              |:|        > Student ID not found! Please try again <     |:|\n");
    printf("                                              |:|_______________________________________________________|:|\n");
    printf("                                              |__-_-_---___----__--_--__-_____----___--___-----__--___--__|\n");
    printf("\033[0m");
    
}


void invalid_Display() {
	printf("\033[36;5m");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("                                                       __-----_---__-----__-_---_-__----_-__--_-__\n");
	printf("                                                      |  _______________________________________  |\n");
	printf("                                                      |:|           INVALID INPUTT!!!!!         |:|\n");
	printf("                                                      |:|   > Please select a valid option. <   |:|\n");
	printf("                                                      |:|_______________________________________|:|\n");
	printf("                                                      |__-_-_---___----__--_--__-_____----___--___|\n");
	printf("\033[0m");
}




void usernotfound(){
	printf("\033[36;5m");
	
	
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("                                                       __-----_---__-----__-_---_-__----_-__--_-__\n");
        printf("                                                      |  _______________________________________  |\n");
        printf("                                                      |:|               INVALID!!!!             |:|\n");
        printf("                                                      |:|    >       USERNAME NOT FOUND     <   |:|\n");
        printf("                                                      |:|_______________________________________|:|\n");
        printf("                                                      |__-_-_---___----__--_--__-_____----___--___|\n");
        printf("\033[0m");
        
}

void invalid_Option(){
	printf("\033[36;5m");
	
	
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("                                                       __-----_---__-----__-_---_-__----_-__--_-__\n");
        printf("                                                      |  _______________________________________  |\n");
        printf("                                                      |:|               INVALID!!!!             |:|\n");
        printf("                                                      |:|    >       Invalid Option         <   |:|\n");
        printf("                                                      |:|_______________________________________|:|\n");
        printf("                                                      |__-_-_---___----__--_--__-_____----___--___|\n");
        printf("\033[0m");
        
}




void invalidUser(){
	printf("\033[36;5m");
	
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("                                                       __-----_---__-----__-_---_-__----_-__--_-__\n");
        printf("                                                      |  _______________________________________  |\n");
        printf("                                                      |:|               INVALID!!!!             |:|\n");
        printf("                                                      |:|    > INVALID USERNAME OR PASSWORD <   |:|\n");
        printf("                                                      |:|_______________________________________|:|\n");
        printf("                                                      |__-_-_---___----__--_--__-_____----___--___|\n");
        printf("\033[0m");
        
}




void noaccfound() {
		printf("\033[36;5m");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		
        printf("                                                       __-----_---__-----__-_---_-__----_-__--_-__\n");
        printf("                                                      |  _______________________________________  |\n");
        printf("                                                      |:|               INVALID!!!!             |:|\n");
        printf("                                                      |:|    > INVALID USERNAME OR PASSWORD <   |:|\n");
        printf("                                                      |:|_______________________________________|:|\n");
        printf("                                                      |__-_-_---___----__--_--__-_____----___--___|\n");
        printf("\033[0m");
}



void loginAccount() {
    struct Account acc;
    char username[50], password[100], inputId[50];
    FILE *fp;
    int attempts = 0;

    while (attempts < 3) {
        system("cls");
        printf("\033[36;5m");
        system("color E9");
        fp = fopen(ACC_FILE, "r");
        if (fp == NULL) {
            printf("\n(System): No accounts found. Please create one first.\n");
            getch();
            return;
        }

        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                         ACCOUNT LOGIN SECTION                                                        |\n");
        printf("                  +======================================================================================================================+\n");

        printf("\n\n                                  Enter Username:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
       
        if (!fgets(username, sizeof(username), stdin)) username[0] = '\0';
        username[strcspn(username, "\n")] = 0;

        printf("\n\n                                  Enter Password:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        inputPassword(password);

        printf("\n\n                                  Enter Generated ID:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (!fgets(inputId, sizeof(inputId), stdin)) inputId[0] = '\0';
        inputId[strcspn(inputId, "\n")] = 0;

        int foundUser = 0, passwordMatch = 0, idMatch = 0;
        rewind(fp);
        while (fscanf(fp,
            "%49[^,],%99[^,],%19[^,],%49[^,],%49[^,],%49[^,],%99[^,],%29[^,],%99[^,],%199[^\n]\n",
            acc.username, acc.password, acc.role, acc.course, acc.firstName,
            acc.lastName, acc.Department, acc.idNumber, acc.email, acc.address) == 10) {

            if (strcmp(username, acc.username) == 0) {
                foundUser = 1;
                if (strcmp(password, acc.password) == 0)
                    passwordMatch = 1;
                if (strcmp(inputId, acc.idNumber) == 0)
                    idMatch = 1;
                break;
            }
        }
        fclose(fp);

        if (!foundUser) {
            system("cls");
            usernotfound();
            attempts++;
        } else if (!passwordMatch) {
            system("cls");
            usernotfound();
            attempts++;
        } else if (!idMatch) {
            system("cls");
            invalid_StudentID_Display();
            attempts++;
        } else {
            printf("\n(System): Logging in...");
            Sleep(700);
            system("cls");
            loadingScreen();
            system("cls");

            if (strcmp(acc.role, "Student") == 0) {
                studentDashboard(&acc);
            } else if (strcmp(acc.role, "Faculty") == 0) {
                facultyDashboard(&acc);
            } else if (strcmp (acc.role, "Admin")== 0){ 
                registrarDash(&acc);
            }else {
            	adminDashboard(&acc);
			}
            return;
        }

        if (attempts < 3) {
            printf("\nAttempts left: %d\n", 3 - attempts);
            printf("Press any key to try again...");
            getch();
        } else {
            printf("\nToo many failed attempts. Returning to main menu...");
            Sleep(1200);
            return;
        }
    }
}





void aboutUs(struct Account *acc) {
	char user;
	char Department, Admin;
	system("cls"); 
	printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
    printf("                  |                                                                                                                      |\n");
    printf("                  |                                                   P H I L T E C H                                                    |\n");
    printf("                  |                                                                                                                      |\n");
    printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
    printf("                  | Name: %s %s A B O U T   U S                                         [ 9 ] Back |\n", acc->firstName, acc->lastName);
    printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
    printf("                  |__-____--____-----___--____------___----_____---_---_---____-____-____--____------__--____-----___----_____---____--__|\n\n");
    
	printf("                   +---+--------------------------------------------------+(----)+---------------------------------------------------+---+\n");
    printf("                   || .|                                                  |  ||  |                                                   |.  |\n");
    printf("                   |  .|--------------------------------------------------|  ||  |---------------------------------------------------|.| |\n");
    printf("                   | |.| 1. BRIEF HISTORY OF PHILTECH                     |  ||  |  Educational Services                             |.| |\n");
    printf("                   | |.|                                                  |  ||  |                                                   |.  |\n");
    printf("                   |  .| Philippine Technological Institute of Science    |  ||  |  Additional programs accredited by the Technical  || ||\n");
    printf("                   | |.| Arts and Trade Inc. was founded in 2010 as a     |  ||  |  Education and Skills Development Authority -     |. ||\n");
    printf("                   || .| non-stock non-profit non-sectarian private       |  ||  |  Rizal. The first batch of graduates marched      |.| |\n");
    printf("                   | |.| Educational Institution to blaze the trail in    |  ||  |  onto their commencement exercises on April 5,    |.| |\n");
    printf("                   |  .| the field of technical education. Its eleven     |  ||  |  2013 with no less than the TESDA Rizal           |.  |\n");
    printf("                   | |.| founders were a mixture of engineers, a          |  ||  |  Provincial Office Director Velma A. Salazar as   |.| |\n");
    printf("                   | |.| scientist/inventor and practitioner in the IT    |  ||  |  their graduation guest of honor.                 |. ||\n");
    printf("                   |  .| industry, school administrators, managers, and   |  ||  |                                                   |. ||\n");
    printf("                   |  || academic professionals in both public and        |  ||  |  By November of 2012, the negotiation for         |.  |\n");
    printf("                   |  || private institutions. Today, the school is more  |  ||  |  additional branches went underway. The Board of  |.  |\n");
    printf("                   || .| popularly known as PHILTECH.                     |  ||  |  Trustees resolved that two new PHILTECH branches |.| |\n");
    printf("                   |  .|                                                  |  ||  |  should be established and operated in Sta. Rosa, |.| |\n");
    printf("                   | |.| The first school was established in November     |  ||  |  Laguna and General Mariano Alvarez, Cavite.      |.  |\n");
    printf("                   | |.| of 2010 and is presently located at F.T.         |  ||  |  Both branches opened in the first semester of    |. ||\n");
    printf("                   || .| Catapusan St. in Tanay, Rizal. In June 2011,     |  ||  |  school year 2013-2014.                           |.| |\n");
    printf("                   |  .| Philippine Technological Institute of Science    |  ||  |                                                   |.| |\n");
    printf("                   |  .| Arts and Trade Inc. opened and offered two-year  |  ||  |  With Tanay (560 students), Sta. Rosa branch (350 |.  |\n");
    printf("                   || .| programs in Information technology, hotel and    |  ||  |  students), and GMA branch (250 students), school |.| |\n");
    printf("                   | |.| restaurant services, and business outsourcing    |  ||  |  year 2013-2014 totaled at least 1160 students.   |. ||\n");
    printf("                   |  .| management.                                      |  ||  |                                                   |.  |\n");
    printf("                   | |.|                                                  |  ||  |  PHILTECH never tires from helping our Filipino   |.  |\n");
    printf("                   | |.| With every member of the Board of Trustees       |  ||  |  youth. It is patriotic. As educators, it is      || ||\n");
    printf("                   |  .| going out of their way to promote the school     |  ||  |  always fulfilling to mold young minds into       ||  |\n");
    printf("                   || .| and its program offerings, the first semester    |  ||  |  productive citizens. Indeed, it is always a      |.  |\n");
    printf("                   | |.| of school year 2011-2012 continued to provide    |  ||  |  blessing.                                        |.| |\n");
    printf("                   || .| the same.                                        |  ||  |                                                   |.| |\n");
    printf("                   |   +--------------------------------------------------+(----)+---------------------------------------------------+   |\n");
    printf("                   [__-___--__--____-----______---_________--------___________--________--___---______------____--____----____--__--___-_]");
    
    getch();
    
 	
}



void registrarDash(struct Account *acc){

    char ch;
    while (1) {
        system("cls");
        printf("\033[36;5m");
        system("color E9");
    printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]               R E G I S T R A R      D   A   S   H   B   O   A   R   D                [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]***************************************************************************************[-]\n");    
    printf("                  [-]          Welcome Resgistar: %s %s                                                     [-]\n", acc->firstName, acc->lastName);                     
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]            ID: %s                                                                     [-]\n" , acc->idNumber);                                                                
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [1] VIEW ALL ACOOUNT                                              [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [2] CHANGE PASSWORD                                               [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [3] LOGOUT                                                        [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]                                                                                       [-]\n");
    printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n");   
        printf("Enter choice: ");
        ch = getch();
        printf("%c\n", ch);
        if (ch == '1') {
            viewAllAccounts();
        } else if (ch == '2') {
            changePasswordAccount(acc);
        } else if (ch == '3') {
            printf("Logging out...\n");
            loadingScreen();
            Sleep(600);
            return;
        } else {
        	system("cls");
             invalid_Option();
            getch();
        }
    }

}
