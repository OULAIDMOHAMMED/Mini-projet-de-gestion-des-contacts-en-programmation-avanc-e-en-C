#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct {
    char district[8];
    char city[8];
    char territory[8];
    char region[10];
} Adresse;

typedef struct {
    char first_name[10];
    char last_name[10];
    char phone_number[10];
    char email[40];
    Adresse adr;
} Contact;

void add_contact(Contact* contacts, int* num_contacts) {
    Contact new_contact;
    
    printf("Enter the first name: ");
    scanf("%s", new_contact.first_name);
    
    printf("Enter the last name: ");
    scanf("%s", new_contact.last_name);
    for (int i = 0; new_contact.last_name[i]; i++) {
        if (new_contact.last_name[i] >= 'a' && new_contact.last_name[i] <= 'z') {
            new_contact.last_name[i] = new_contact.last_name[i] - 'a' + 'A';
        }
    }
    
    printf("Enter the phone number: ");
    scanf("%s", new_contact.phone_number);

    printf("Enter the adresse email: ");
    scanf("%s", new_contact.email);
    
    printf("Enter the address details:\n");
    printf("District: ");
    scanf("%s", new_contact.adr.district);
    
    printf("City: ");
    scanf("%s", new_contact.adr.city);
    
    printf("Territory: ");
    scanf("%s", new_contact.adr.territory);
    
    printf("Region: ");
    scanf("%s", new_contact.adr.region);

    contacts[*num_contacts] = new_contact;
    (*num_contacts)++;

    FILE* contact_file = fopen("contacts.txt", "a");
    if (contact_file == NULL) {
        fprintf(stderr, "Error opening the file: %s\n", "contacts.txt");
        exit(EXIT_FAILURE);
    }

    fprintf(contact_file, "%s %s %s %s %s %s %s %s\n", new_contact.first_name, new_contact.last_name, new_contact.phone_number, new_contact.adr.district, new_contact.adr.city, new_contact.adr.territory, new_contact.adr.region,new_contact.email);
    
    fclose(contact_file);
}

void show_contacts(Contact* contacts, int num_contacts) {
    printf("Contacts:\n");
    for (int i = 0; i < num_contacts; i++) {
        printf("Name: %s %s\n", contacts[i].first_name, contacts[i].last_name);
        printf("Phone Number: %s\n", contacts[i].phone_number);
        printf("email: %s\n", contacts[i].email);
        printf("Address: %s %s %s %s\n", contacts[i].adr.district, contacts[i].adr.city, contacts[i].adr.territory, contacts[i].adr.region);
        printf("_____________________\n");
    }
}
int search_contact(Contact* contacts, int num_contacts, const char* name) {
    for (int i = 0; i < num_contacts; i++) {
        if (strcmp(contacts[i].first_name, name) == 0) {
            printf("Name: %s %s\n", contacts[i].first_name, contacts[i].last_name);
            printf("Phone Number: %s\n", contacts[i].phone_number);
            printf("email: %s\n", contacts[i].email);
            printf("Address: %s %s %s %s\n", contacts[i].adr.district, contacts[i].adr.city, contacts[i].adr.territory, contacts[i].adr.region);
            printf("_____________________\n");
            return i;
        }
    }
    printf("Contact not found.\n");
    return -1;
}
void edit_contact(Contact* contacts, int num_contacts, int index) {
    if (index != -1) {
        printf("Enter the new first name: ");
        scanf("%s", contacts[index].first_name);

        printf("Enter the new last name: ");
        scanf("%s", contacts[index].last_name);
        for (int i = 0; contacts[index].last_name[i]; i++) {
            if (contacts[index].last_name[i] >= 'a' && contacts[index].last_name[i] <= 'z') {
                contacts[index].last_name[i] = contacts[index].last_name[i] - 'a' + 'A';
            }
        }
        printf("Enter the new phone number: ");
        scanf("%s", contacts[index].phone_number);

        printf("Enter the new email : ");
        scanf("%s", contacts[index].email);

        printf("Enter the new address details:\n");
        printf("District: ");
        scanf("%s", contacts[index].adr.district);

        printf("City: ");
        scanf("%s", contacts[index].adr.city);

        printf("Territory: ");
        scanf("%s", contacts[index].adr.territory);

        printf("Region: ");
        scanf("%s", contacts[index].adr.region);

        FILE* contact_file = fopen("contacts.txt", "w");
        if (contact_file == NULL) {
            fprintf(stderr, "Error opening the file: %s\n", "contacts.txt");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < num_contacts; i++) {
            fprintf(contact_file, "%s %s %s %s %s %s %s %s\n", contacts[i].first_name, contacts[i].last_name, contacts[i].phone_number, contacts[i].adr.district, contacts[i].adr.city, contacts[i].adr.territory, contacts[i].adr.region,contacts[i].email);
        }

        fclose(contact_file);

        printf("Contact edited successfully.\n");
    } else {
        printf("Contact not found.\n");
    }
}
void delete_contact(Contact* contacts, int* num_contacts, int index) {
    if (index != -1) {
        for (int i = index; i < (*num_contacts) - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        (*num_contacts)--;

        FILE* contact_file = fopen("contacts.txt", "w");
        if (contact_file == NULL) {
            fprintf(stderr, "Error opening the file: %s\n", "contacts.txt");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < *num_contacts; i++) {
            fprintf(contact_file, "%s %s %s %s %s %s %s %s\n", contacts[i].first_name, contacts[i].last_name, contacts[i].phone_number, contacts[i].adr.district, contacts[i].adr.city, contacts[i].adr.territory, contacts[i].adr.region,contacts[i].email);
        }

        fclose(contact_file);

        printf("Contact deleted successfully.\n");
    } else {
        printf("Contact not found.\n");
    }
}
void selection_sort_contacts(Contact* contacts, int num_contacts) {
    int i, j;
    for (i = 0; i < num_contacts - 1; i++) {
        int min_index = i;
        for (j = i + 1; j < num_contacts; j++) {
            if (strcmp(contacts[j].last_name, contacts[min_index].last_name) < 0) {
                min_index = j;
            }
        }
        Contact temp = contacts[i];
        contacts[i] = contacts[min_index];
        contacts[min_index] = temp;
    }
}
void load_contacts_from_file(Contact* contacts, int* num_contacts) {
    FILE* contact_file = fopen("contacts.txt", "r");
    if (contact_file == NULL) {
        fprintf(stderr, "Error opening the file: %s\n", "contacts.txt");
        exit(EXIT_FAILURE);
    }

    while (fscanf(contact_file, "%s %s %s %s %s %s %s %s",
                  contacts[*num_contacts].first_name,
                  contacts[*num_contacts].last_name,
                  contacts[*num_contacts].phone_number,
                  contacts[*num_contacts].adr.district,
                  contacts[*num_contacts].adr.city,
                  contacts[*num_contacts].adr.territory,
                  contacts[*num_contacts].adr.region,
                  contacts[*num_contacts].email) == 8) {
        (*num_contacts)++;
    }
    selection_sort_contacts(contacts, *num_contacts);
    fclose(contact_file);
}    
void displayNamesFromLoginFile() {
    char user[30],pes[30],usrname[30];
    char k;
    FILE *file = fopen("login.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%s %s  %c", user,pes,&k) == 3) {
        printf("Account name: %s\n", user);
    }

    fclose(file);
    printf("Enter the account name for validation:");
    scanf("%s",usrname);
     FILE *fil = fopen("login.txt", "r+");
     if (fil == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
     }
     while (fscanf(fil, "%s %s %c", user, pes,&k) == 3) {
        if (strcmp(user, usrname) == 0) {
            fseek(file, -1, SEEK_CUR); 
            fprintf(file, "V");

            printf("The account '%s' has been successfully validated.\n", usrname);
            fclose(fil);
        }
    }


}

void admin(){
    Contact contacts[100];
    int num_contacts = 0;
    int choice;
    int sec;
    load_contacts_from_file(contacts, &num_contacts);
    while (1) {
        printf("____________________________________\n");
        printf(" 1- add new contact \n");
        printf("____________________________________\n");
        printf(" 2- show all contact \n");
        printf("____________________________________\n");
        printf(" 3- search contact \n");
        printf("____________________________________\n");
        printf(" 4- edit un contact \n");
        printf("____________________________________\n");
        printf(" 5- delete a contact \n");
        printf("____________________________________\n");
        printf(" 6- To secure the information: \n");
        printf("____________________________________\n");
        printf(" 7- quit \n");
        printf("____________________________________\n");
        printf(" 8- Return to the menu \n");
        printf("____________________________________\n");
        printf(" 9- Validate accounts \n");
        printf("____________________________________\n");


        while(1){
        printf("choose a choice from 1 to 9 : ");
        scanf("%d",&choice);
        printf("____________________________________\n");
        switch (choice)
        {
        case 1: add_contact(contacts, &num_contacts);
            break;
        case 2: show_contacts(contacts, num_contacts);
            break;
        case 3: {
                char name[20];
                printf("Enter the name to search: ");
                scanf("%s", name);
                search_contact(contacts, num_contacts, name);
                break;
            }
            break;
        case 4: {
                char edit_name[10];
                printf("Enter the name to edit: ");
                scanf("%s", edit_name);
                int index = search_contact(contacts, num_contacts, edit_name);
                edit_contact( contacts, num_contacts, index);}
            break;
        case 5:{
                char delete_name[10];
                printf("Enter the name to delete: ");
                scanf("%s", delete_name);
                int index = search_contact(contacts, num_contacts, delete_name);
                delete_contact(contacts, &num_contacts, index);}
            break;
        case 6: {
            printf("____________________________________\n");
            printf(" 1- To secure the information: \n");
            printf("____________________________________\n");
            printf(" 2- To allow other accounts to view the information: \n");
            printf("____________________________________\n");
            printf("choose a choice from 1 ou 2 : ");
            scanf("%d",&sec);
            FILE *valeur = fopen("valeur.txt", "w");
            if (valeur == NULL) {
             printf("Erreur lors de l'ouverture du fichier\n");
             exit(EXIT_FAILURE);
            }
            fprintf(valeur, "%d ", sec);
            fclose(valeur);
            admin();
        }
            break;  
        case 7: exit(EXIT_SUCCESS);
            break;
        case 8: login();
        break;
        case 9: displayNamesFromLoginFile();
          break;      
        default: printf("this choice doesn't exist, try again\n");
            break;
        }
        getch();
        system("cls");
    }
  }
}
void autre(){
    Contact contacts[100];
    int num_contacts = 0;
    int choice;
    load_contacts_from_file(contacts, &num_contacts);
    while (1) {
        printf("____________________________________\n");
        printf(" 1- add new contact \n");
        printf("____________________________________\n");
        printf(" 2- show all contact \n");
        printf("____________________________________\n");
        printf(" 3- search contact \n");
        printf("____________________________________\n");
        printf(" 4- quit \n");
        printf("____________________________________\n");

        while(1){
        printf("choose a choice from 1 to 4 : ");
        scanf("%d",&choice);
        printf("____________________________________\n");
        switch (choice)
        {
        case 1: add_contact(contacts, &num_contacts);
            break;
        case 2: show_contacts(contacts, num_contacts);
            break;
        case 3: {
                char name[20];
                printf("Enter the name to search: ");
                scanf("%s", name);
                search_contact(contacts, num_contacts, name);
                autre();
                break;
            }
            break;
        case 4: exit(EXIT_SUCCESS);
            break;
        default: {
          printf("this choice doesn't exist, try again\n");
          autre();
        } 
            break;
        }
    getch();
    system("cls");
    }
    }
}
void compte(){
    char k[100],F[100];
    char name[30],mot[30],H;
    FILE* login_file;
     printf("____________________________________\n");
     printf("  Enter the name: \n");
     scanf("%s", k);
     printf("____________________________________\n");
     printf("  Enter the password: \n");
     scanf("%s", F);
     login_file = fopen("login.txt", "r");
     if (login_file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s\n", "login.txt");
        exit(EXIT_FAILURE);
     }

     while (fscanf(login_file, "%s %s %c", name, mot, &H) == 3) {
        if (strcmp(k, name) == 0) {
            printf("The name '%s' already exists. Please choose another name.\n", k);
            fclose(login_file);
            return;
        }
     }
     login_file = fopen("login.txt", "a");
     if (login_file == NULL) {
        fprintf(stderr, "Error opening the file: %s\n", "login.txt");
        exit(EXIT_FAILURE);
        }
     fprintf(login_file, "%s %s F\n", k, F);
     fclose(login_file);
}
void login(){
    int b,sec;
    char k[100],F[100],valide;
    char name[30],pass[30];
     int c;
     while (1) {
        printf("____________________________________\n");
        printf(" 1- admin \n");
        printf("____________________________________\n");
        printf(" 2- others \n");
        printf("____________________________________\n");
        printf(" 3-Create an account for others \n");
        printf("____________________________________\n");
        while(1){
        printf("choose a choice from 1 to 3 : ");
        scanf("%d",&b);
        printf("____________________________________\n");
        switch (b)
        {
        case 1: while (1) {
        printf("____________________________________\n");
        printf("  Enter the password: \n");
        scanf("%d",&c);
        if(c==0000){
            admin();
            break;
        }
        else{
           login(); 
        }
        }
            break;
        case 2:
        printf("____________________________________\n");
        printf("  Enter the name:\n");
        scanf("%s", k);
        printf("____________________________________\n");
        printf("  Enter the password:\n");
        scanf("%s", F);

        FILE *login_file = fopen("login.txt", "r");
        if (login_file == NULL) {
            fprintf(stderr, "Error opening the file: %s\n", "login.txt");
            exit(EXIT_FAILURE);
          }
        int authentificationReussie = 0;

        while (fscanf(login_file, "%s %s %c", name, pass,&valide) == 3) {
        if (strcmp(k, name) == 0 && strcmp(F, pass) == 0) {
            authentificationReussie = 1; 
            break;
        }
        }

        fclose(login_file);

        if (authentificationReussie) {
            FILE *valeur = fopen("valeur.txt", "r");
            if (valeur == NULL) {
              printf("Erreur lors de l'ouverture du fichier\n");
              exit(EXIT_FAILURE);
            }
            fscanf(valeur, "%d", &sec);
            fclose(valeur);
            if(sec==1)
            {
             printf("  Admin secures the information.\n"); 
            }
            else{
                if (valide == 'V') {
                 printf("Authentication successful, admin has validated your account.\n");
                 autre();
                }
                
                else if (valide == 'F') {
                 printf("Authentication successful, but admin has not validated this account.\n");
                 login();
                }
            }  
            }   
        else {
         login();
        }

         break;

        case 3:compte();
           break; 
        }
        getch();
        system("cls");
        }
    }
} 
void createFileIfNotExists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        file = fopen(filename, "w");
        if (file == NULL) {
            fprintf(stderr, "Error creating the file: %s\n", filename);
            exit(EXIT_FAILURE);
        }
        fclose(file);
    } else {
        fclose(file);
    }
}
void createValeurFileIfNotExists() {
    const char* filename = "valeur.txt";
    const char* defaultContent = "2";

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        file = fopen(filename, "w");
        if (file == NULL) {
            fprintf(stderr, "Error creating the file: %s\n", filename);
            exit(EXIT_FAILURE);
        }
        fprintf(file, "%s", defaultContent);
        fclose(file);
    } else {
        fclose(file);
    }
}
int main(){
    createValeurFileIfNotExists();
    createFileIfNotExists("contacts.txt");
    createFileIfNotExists("login.txt");
    login();

}