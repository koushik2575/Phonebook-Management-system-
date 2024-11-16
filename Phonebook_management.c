#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

// Structure to represent a contact
struct person {
    char name[35];
    char mble_no[20];
};

// Structure to represent a recent call
struct recent_call {
    char number[20];
};

// Global variables
struct person contacts[100]; // Assuming maximum 100 contacts
int num_contacts = 0; // Initialize the number of contacts to 0

// Function prototypes
void start();
void menu();
void got(char *name);
int add();
void delete_contact();
void update();
void search();
void show();
void sort_contacts_by_letter();
void dial_call();
void play_dialing_tone();
void call_history();
void recent_call_list(); // New function for recent call list

int main() {
    system("color Bf");
    start();
    return 0;
}

void start() {
    menu();
}



void got(char *name) {
    int i = 0, j;
    char c, ch;
    do {
        c = getch();
        if (c != 8 && c != 13) {
            *(name + i) = c;
            putch(c);
            i++;
        }
        if (c == 8) {
            if (i > 0) {
                i--;
            }
            system("cls");
            for (j = 0; j < i; j++) {
                ch = *(name + j);
                putch(ch);
            }
        }
    } while (c != 13);
    *(name + i) = '\0';
}

void menu() {
    system("cls");
    printf("\n\n\t\t\t\t**WELCOME TO HOTASH PHONE\t\t\n");
    printf("\n\n\t\t\t\t\t\t\t\t  MENU \t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t\t  .....       \n\n");
    printf("\t\t\t1. Add Contact   \t\t\t2. Delete Contact   \t\t\t3. Update contact information  \n\t\t\t4. Search Contact \t\t\t5. Sort Contacts\t\t\t6. Show Contact\t\t\t\n\t\t\t7. Call History\t\t\t\t8. Dial Call\t\t\t\t9. Recent Call List\t\t\t\n\t\t\t0. Exit\n");

    switch (getch()) {
    case '1':
        add();
        break;
    case '2':
        delete_contact();
        break;
    case '3':
        update();
        break;
    case '4':
        search();
        break;
    case '5':
        sort_contacts_by_letter();
        break;
    case '6':
        show();
        break;
    case '7':
        call_history();
        break;
    case '8':
        dial_call();
        break;
    case '9':
        recent_call_list(); 
        break;
    case '0':
        exit(0);
        break;
    default:
        system("cls");
        printf("\nEnter 0 to 9 only");
        printf("\n Enter any key to return in main menu.");
        getch();
        menu();
    }
}

int add() {
    system("cls");
    FILE *f;
    struct person p;
    f = fopen("project.txt", "a+");
    if (f == NULL) {
        printf("\nError in opening file.");
        return -1;
    }

    printf("\n Enter name: ");
    got(p.name);
    printf("\nEnter phone no.: ");
    got(p.mble_no);

    fprintf(f, "%s,%s\n", p.name, p.mble_no);
    fflush(stdin);
    printf("\nRecord saved");

    fclose(f);

    printf("\n\nEnter any key");
    getch();
    system("cls");
    menu();
    return 0;
}

void search() {
    FILE *f;
    char name[100];

    f = fopen("project.txt", "r");
    if (f == NULL) {
        printf("\nError in opening file");
        return;
    }

    printf("\nEnter name of person to search: ");
    got(name);
    int found = 0;
    char line[100];
    while (fgets(line, sizeof(line), f) != NULL) {
        char *token = strtok(line, ",");
        if (token != NULL && strcmp(token, name) == 0) {
            printf("\nDetail Information About %s", name);
            printf("\nName: %s\nMobile no: %s\n", token, strtok(NULL, "\n"));
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record not found");
    }

    fclose(f);
    printf("\nPress any key to continue...");
    getch();
    system("cls");
    menu();
}

void show() {
    FILE *f;
    f = fopen("project.txt", "r");
    printf("\nPHONE RECORDS\n");
    if (f == NULL) {
        printf("\nfile opening error in listing :");
        exit(1);
    }
    system("cls");
    char line[100];
    while (fgets(line, sizeof(line), f) != NULL) {
        char *token = strtok(line, ",");
        if (token != NULL) {
            printf("\nName: %s\nMobile no: %s\n", token, strtok(NULL, "\n"));
        }
    }
    fclose(f);

    printf("\nEnter any key to back \n");
    getch();
    system("cls");
    menu();
}

void delete_contact() {
    struct person p;
    FILE *f, *ft;
    int flag = 0;
    char name[100];
    f = fopen("project.txt", "r");
    if (f == NULL) {
        printf("CONTACT'S DATA NOT ADDED YET.");
    } else {
        ft = fopen("temp", "w+"); // temporary file for delete
        if (ft == NULL) {
            printf("file opaning error");
            return;
        }

        printf("\n\n\tENTER CONTACT NAME TO DELETE: ");
        got(name);

        while (fscanf(f, "%[^,],%s\n", p.name, p.mble_no) != EOF) {
            if (strcmp(p.name, name) != 0) {
                fprintf(ft, "%s,%s\n", p.name, p.mble_no);
            } else {
                flag = 1;
            }
        }
        fclose(f);
        fclose(ft);
        if (flag != 1) {
            printf("\nNO CONACT'S RECORD TO DELETE.");
            remove("temp.txt");
        } else {
            remove("project.txt");
            rename("temp", "project.txt");
            printf("\nRECORD DELETED SUCCESSFULLY.");
        }
    }
    printf("\nPress any key to continue...");
    getch();
    system("cls");
    menu();
}

void update() {
    struct person p;
    FILE *f, *ft;
    int flag = 0;
    char name[100];
    f = fopen("project.txt", "r");
    if (f == NULL) {
        printf("CONTACT'S DATA NOT ADDED YET.");
        return;
    } else {
        ft = fopen("temp", "w+");
        if (ft == NULL) {
            printf("file opening error");
            return;
        }
        printf("\n\n\tENTER CONTACT NAME TO MODIFY:\n");
        got(name);

        while (fscanf(f, "%[^,],%s\n", p.name, p.mble_no) != EOF) {
            if (strcmp(p.name, name) != 0) {
                fprintf(ft, "%s,%s\n", p.name, p.mble_no);
            } else {
                flag = 1;
                printf("\n\t\t\t\tEnter name: ");
                got(p.name);
                printf("\n\t\t\t\tEnter phone no: ");
                got(p.mble_no);
                fprintf(ft, "%s,%s\n", p.name, p.mble_no);
            }
        }
        fclose(f);
        fclose(ft);
        if (flag != 1) {
            printf("\nNO CONTACT'S RECORD TO MODIFY.");
            remove("temp");
        } else {
            remove("project.txt");
            rename("temp", "project.txt");
            printf("\nRECORD MODIFIED SUCCESSFULLY.");
        }
    }
    printf("\nPress any key to continue...");
    getch();
    system("cls");
    menu();
}

void sort_contacts_by_letter() {
    FILE *f;
    struct person p;
    char letter;

    // Load all contacts from file into an array
    f = fopen("project.txt", "r");
    if (f == NULL) {
        printf("\nError in opening file");
        return;
    }

    int i = 0;
    while (fscanf(f, "%[^,],%s\n", contacts[i].name, contacts[i].mble_no) != EOF) {
        i++;
    }
    num_contacts = i;
    fclose(f);

    // Ask the user for the letter to filter contacts
    printf("Enter the first letter to filter by (A-Z): ");
    scanf(" %c", &letter);  // Note: Space before %c to consume any leftover newline in input buffer

    // Convert to uppercase if necessary
    if (letter >= 'a' && letter <= 'z') {
        letter -= 32; // Convert lowercase to uppercase
    }

    // Sort contacts by the first letter of the name (ignore case)
    for (i = 0; i < num_contacts - 1; i++) {
        for (int j = i + 1; j < num_contacts; j++) {
            char first_i = contacts[i].name[0];
            char first_j = contacts[j].name[0];
            // Convert to uppercase for comparison
            if (first_i >= 'a' && first_i <= 'z') {
                first_i -= 32; // Convert lowercase to uppercase
            }
            if (first_j >= 'a' && first_j <= 'z') {
                first_j -= 32; // Convert lowercase to uppercase
            }
            if (first_i > first_j) {
                p = contacts[i];
                contacts[i] = contacts[j];
                contacts[j] = p;
            }
        }
    }

    // Display contacts sorted by first letter and matching the user's input
    printf("\nContacts whose names start with '%c' or '%c':\n", letter, letter + 32);
    int found = 0;
    for (i = 0; i < num_contacts; i++) {
        char first = contacts[i].name[0];
        if ((first == letter) || (first == letter + 32)) {
            printf("\nName: %s - Mobile No: %s", contacts[i].name, contacts[i].mble_no);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo contacts found starting with the letter '%c' or '%c'.\n", letter, letter + 32);
    }

    printf("\n\nPress any key to continue...");
    getch();
    system("cls");
    menu();
}

void dial_call() {
    char number[20];
    printf("\nEnter the mobile number you want to call: ");
    got(number);
    
    // Check if the dialed number matches any saved contact
    FILE *f = fopen("project.txt", "r");
    if (f != NULL) {
        struct person p;
        int found = 0;
        while (fscanf(f, "%[^,],%s\n", p.name, p.mble_no) != EOF) {
            if (strcmp(p.mble_no, number) == 0) {
                printf("\nDialing call to\n%s (%s)...\n", p.name, number);
                found = 1;
                // Record the call to call history file
                FILE *history = fopen("call_history.txt", "a");
                if (history != NULL) {
                    fprintf(history, "Called %s (%s)\n", p.name, number);
                    fclose(history);
                } else {
                    printf("\nError in opening call history file.\n");
                }
                break;
            }
        }
        fclose(f);
        if (!found) {
            printf("\nDialing call to %s...\n", number);
            // Record the call to call history file
            FILE *history = fopen("call_history.txt", "a");
            if (history != NULL) {
                fprintf(history, "Called %s\n", number);
                fclose(history);
            } else {
                printf("\nError in opening call history file.\n");
            }
        }
    } else {
        printf("\nDialing call to %s...\n", number);
        // Record the call to call history file
        FILE *history = fopen("call_history.txt", "a");
        if (history != NULL) {
            fprintf(history, "Called %s\n", number);
            fclose(history);
        } else {
            printf("\nError in opening call history file.\n");
        }
    }
    
    // Record the dialed number to recent call list
    FILE *recent_calls = fopen("recent_calls.txt", "a");
    if (recent_calls != NULL) {
        fprintf(recent_calls, "%s\n", number);
        fclose(recent_calls);
    } else {
        printf("\nError in opening recent call list file.\n");
    }
    
    // Play the dialing tone continuously until a key is pressed
    while (!kbhit()) {
        play_dialing_tone();
        Sleep(500); // Sleep for 500 milliseconds between beeps
    }
    
    // Consume the key press
    getch();
    
    printf("\nCall ended.\n");
    
    // You can add more functionality here, such as connecting to a phone network or simulating a call.
    printf("\nPress any key to continue...");
    getch();
    system("cls");
    menu();
}

void play_dialing_tone() {
    Beep(1000, 500); // Example: Beep at 1000 Hz for 500 milliseconds
}

void call_history() {
    FILE *f;
    f = fopen("call_history.txt", "r");
    if (f == NULL) {
        printf("\nNo call history available.\n");
        printf("\nPress any key to continue...");
        getch();
        system("cls");
        menu();
        return;
    }
    
    printf("\nCALL HISTORY\n");
    char line[100];
    while (fgets(line, sizeof(line), f) != NULL) {
        printf("%s", line);
    }
    fclose(f);

    printf("\nPress any key to continue...");
    getch();
    system("cls");
    menu();
}

void recent_call_list() {
    FILE *f;
    f = fopen("recent_calls.txt", "r");
    if (f == NULL) {
        printf("\nNo recent calls available.\n");
        printf("\nPress any key to continue...");
        getch();
        system("cls");
        menu();
        return;
    }
    
    printf("\nRECENT CALL LIST\n");
    char number[20];
    while (fgets(number, sizeof(number), f) != NULL) {
        // Check if the number exists in contacts
        FILE *contactFile = fopen("project.txt", "r");
        if (contactFile != NULL) {
            struct person p;
            int found = 0;
            while (fscanf(contactFile, "%[^,],%s\n", p.name, p.mble_no) != EOF) {
                if (strcmp(p.mble_no, number) == 0) {
                    printf("Name: %s - Mobile No: %s", p.name, number);
                    found = 1;
                    break;
                }
            }
            fclose(contactFile);
            if (!found) {
                printf("Mobile No: %s", number);
            }
        } else {
            printf("Mobile No: %s", number);
        }
    }
    fclose(f);

    printf("\nPress any key to continue...");
    getch();
    system("cls");
    menu();
}