#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Patient {
    char name[50];
    int age;
    char problem[100];
    char doctor[50];
};
void addPatient();
void displayPatients();
void searchPatient();
void updatePatient();
void deletePatient();
void sort();
int main() {
    int choice;
    do{
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("       *** HOSPITAL MANAGEMENT SYSTEM ***\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("1. Add Patient\n");
        printf("2. Display All Patients\n");
        printf("3. Search Patient by Name\n");
        printf("4. update Patient\n");
        printf("5. delete Patient\n");
        printf("6. Sort Patient\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addPatient(); break;
            case 2: displayPatients(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: deletePatient(); break;
            case 6: sort(); break;
            case 7: printf("Exiting program Thank you...\n"); exit(0);
            default: printf("Invalid choice! Try again...\n");
        }
    }while(1);
    return 0;
}
void addPatient() {
    struct Patient p;
    FILE *fp = fopen("hospital.txt", "a");
    printf("Enter patient name : ");
    scanf("%s", &p.name);
    printf("Enter age : ");
    scanf("%d", &p.age);
    printf("Enter Problem : ");
    scanf("%s",p.problem);
    printf("Enter assigned doctor : ");
    scanf("%s", &p.doctor);
    fprintf(fp, "%s %d %s %s\n", p.name, p.age, p.problem, p.doctor);
    fclose(fp);
    printf("Patient added successfully!\n");
}
void displayPatients() {
    FILE *fp = fopen("hospital.txt", "r");
    if(fp == NULL) printf("No records found!\n");
    struct Patient p;
    printf("\n=======================================================\n");
    printf("               Patient Record");
    printf("\n=======================================================\n");
    printf("%-15s  %-4s  %-15s  %-15s", "Name", "Age", "Problem", "Doctor");
    printf("\n=======================================================\n");
    while (fscanf(fp, "%s %d %s %s", p.name, &p.age, p.problem, p.doctor) == 4) {
        printf("%-15s  %-4d  %-15s  %-15s\n", p.name, p.age, p.problem, p.doctor);
    }
    printf("=======================================================\n");
    fclose(fp);
}
void searchPatient() {
    FILE *fp = fopen("hospital.txt", "r");
    if (fp == NULL) printf("No records found!\n");
    struct Patient p;
    char pname[50];
    int flag = 0;
    printf("Enter name to search: ");
    scanf("%s", &pname);
    while (fscanf(fp, "%s %d %s %s", p.name, &p.age, p.problem, p.doctor) == 4) {
        if (strcmp(p.name,pname) == 0) {
            printf("\nRecord Found:\n");
            printf("Name : %s\nAge : %d\nProblem : %s\nDoctor : %s\n", p.name, p.age, p.problem, p.doctor);
            flag = 1;
            break;
        }
    }
    if (!flag)
        printf("No record found with the name '%s'\n", pname);

    fclose(fp);
} 
void updatePatient(){
    struct Patient p;
    int flag = 0;
    FILE *fp, *temp;
    fp = fopen("hospital.txt", "r");
    temp = fopen("hospital1.txt", "w");
    if(fp==NULL) printf("Patient records not found\n"); 
    char pname[50];
    printf("Enter the Patient name to update : ");
    scanf("%s", &pname);
    while(fscanf(fp, "%s %d %s %s", p.name, &p.age, p.problem, p.doctor)==4){
        if(strcmp(p.name, pname)==0){
            printf("Enter New Doctor : ");
            scanf("%s", &p.doctor);
            printf("Enter Condition : ");
            scanf("%s", &p.problem);
            flag = 1;
        }
        fprintf(temp, "%s %d %s %s\n", p.name, p.age, p.problem, p.doctor);
    }
    fclose(fp);
    fclose(temp);
    remove("hospital.txt");
    rename("hospital1.txt", "hospital.txt");
    if(flag){
        printf("Patient record updated succesfully");
    }
}
void deletePatient(){
    struct Patient p;
    int flag = 0;
    FILE *fp, *temp;
    fp = fopen("hospital.txt", "r");
    temp = fopen("hospital1.txt", "w");
    if(fp == NULL) printf("Patient records not found\n");
    char pname[50];
    printf("Enter patient name to delete : ");
    scanf("%s", &pname);
    while(fscanf(fp, "%s %d %s %s", p.name, &p.age, p.problem, p.doctor)==4){
        if(strcmp(p.name,pname)==0){
            flag = 1;
            continue;
        }
        fprintf(temp, "%s %d %s %s\n", p.name, p.age, p.problem, p.doctor);
    }
    fclose(fp);
    fclose(temp);
    remove("hospital.txt");
    rename("hospital1.txt", "hospital.txt");
    if(flag){
        printf("Patient record deleted succesfully");
    }
}
void sort(){
    struct Patient p[100], temp;
    int choice, count=0;
    FILE *fp = fopen("hospital.txt", "r");
    while(fscanf(fp, "%s %d %s %s", p[count].name, &p[count].age, p[count].problem, p[count].doctor)==4){
        count++;
    }
    if(count==0) printf("No data to sort add first\n");
    printf("Sort by\n1. Patient name(ascending)\n2. Patient age(descending)\n3. Doctor name(ascending)\nEnter choice : ");
    scanf("%d", &choice);
    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++){
            int s = 0;
            if(choice == 1 && strcmp(p[i].name,p[j].name)>0) s = 1;
            else if(choice == 2 && p[i].age<p[j].age) s = 1;
            else if(choice == 3 && strcmp(p[i].doctor, p[j].doctor)>0) s = 1;
            else printf("Enter valid choice\n");
            if(s){
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    printf("\n=======================================================\n");
    printf("          Patient Record");
    printf("\n=======================================================\n");
    printf("%-15s  %-4s  %-15s  %-15s", "Name", "Age", "Problem", "Doctor");
    printf("\n=======================================================\n");
    for(int i=0;i<count;i++){
        printf("%-15s  %-4d  %-15s  %-15s\n", p[i].name, p[i].age, p[i].problem, p[i].doctor);
    }
    printf("========================================================\n");
    fclose(fp);
} 