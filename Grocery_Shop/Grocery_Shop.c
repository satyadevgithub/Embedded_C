#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int manu();
int vegetable_product();
int dairy_product();
int total_d=0;
int total_v=0;

void main() {   
    printf("***** Welcome to the Grocery Store *****\n");
    FILE *fp = fopen("Receipt.txt", "w");
    if(fp==NULL){
    printf("Error opening file!\n"); }
    fclose(fp);   
    manu();
}
int manu()
{
    int choose;
    char ch,name[50];
    printf("***** Main Menu *****\n");
    printf("What do you want ?\n");
    printf("1. Vegetable Product\n2. Dairy Product\n3. Checkout \n4. Bill Print\n");
    printf("Choose-> ");
    scanf("%d", &choose);
    
    switch (choose) {
        case 1:
            vegetable_product();
            break;
        case 2:
            dairy_product();
            break;
        case 3:
            printf("Do you really want to checkout? -> ");
            getchar();
            scanf("%c",&ch);
            if((ch=='y' || ch=='Y')==0) { manu();}
        case 4:
            printf("Your Name-> ");
            getchar();
            scanf("%[^\n]s",name);
            printf("\n\n***********Payment Receipt***********\n");
            printf("Thanks '%s'  to visit our Grocery Shop.\n",name);
            printf("Your purchased Vegetables total cost is = %d\n",total_v);
            printf("Your purchased Dairy Product total cost is = %d\n",total_d);
            printf("Your final payment amount is = %d\n",total_v+total_d);
            printf("***********Thank You***********\n");
            printf("**********Visit Again**********\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            manu();
            break;
    }

    return 0;
}


int vegetable_product() {
    int choice;
    const char *vegetable[] = {"Tomato", "Potato", "Onion", "Pumpkin", "Ladyfinger"};
    int veg_price[] = {50, 40, 50, 30, 60};

    printf("***** Vegetable Menu *****\n");
    printf("1. Tomato\n2. Potato\n3. Onion\n4. Pumpkin\n5. Ladyfinger\n6. Return to Main Menu\n");

    FILE *fp = fopen("Receipt.txt", "a+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1; // Exit if file cannot be opened
    }

    do {
        do {
            printf("Choose -> ");
            scanf("%d", &choice);
            if (choice < 1 || choice > 6) {
                printf("Wrong choice! Try again ->\n");
            }
        } while (choice < 1 || choice > 6);

        if (choice != 6) {
            fprintf(fp, "%s -> %d\n", vegetable[choice - 1], veg_price[choice - 1]);
            total_v+=veg_price[choice - 1];
        }
    } while (choice != 6);
    fclose(fp);
    printf("Your purchased Vegetables total cost is = %d\n",total_v);
    manu();
    return 0;
}

int dairy_product() {
    int choice;
    const char *dairy[] = {"Milk","Cheese","Sweet","Curd","Ice cream"};
    int dairy_price[] = {65,250,800,80,20};

    printf("***** Dairy Product Menu *****\n");
    printf("1. Milk\n2. Cheese\n3. Sweet\n4. Curd\n5. Ice cream\n6. Return to Main Menu\n");

    FILE *fp = fopen("Receipt.txt", "a+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1; // Exit if file cannot be opened
    }

    do {
        do {
            printf("Choose -> ");
            scanf("%d", &choice);
            if (choice < 1 || choice > 6) {
                printf("Wrong choice! Try again ->\n");
            }
        } while (choice < 1 || choice > 6);

        if (choice != 6) {
            fprintf(fp, "%s -> %d\n", dairy[choice - 1], dairy_price[choice - 1]);
            total_d+=dairy_price[choice - 1];
        }
    } while (choice != 6);

    fclose(fp);
    printf("Your purchased Dairy Product total cost is = %d\n",total_d);
    manu();
    return 0;
}
