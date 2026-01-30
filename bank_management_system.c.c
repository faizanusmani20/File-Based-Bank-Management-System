#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account
{
    char name[50];
    int accNo;
    float balance;
    char pin[5];
};

void addAccount();
void viewAccount();
void checkBalance();
void deposite();
void withdraw();

int main()
{
    int choice;
    do
    {
        printf("\n====Bank Management====\n");
        printf("1.Add Account\n");
        printf("2.View Account\n");
        printf("3.Check Balance\n");
        printf("4.Withdraw Amount\n");
        printf("5.Deposite Amount\n");
        printf("6.Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addAccount();
            break;
        case 2:
            viewAccount();
            break;
        case 3:
            checkBalance();
            break;
        case 4:
            withdraw();
            break;
        case 5:
            deposite();
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid Choice!\n");
        }
    } while (choice != 6);

    return 0;
}

void addAccount()
{
    FILE *fp;
    struct Account acc;
    acc.balance = 0;

    fp = fopen("data.dat", "ab");
    if (fp == NULL)
    {
        printf("Could Not Open!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %49[^\n]", acc.name);

    printf("Account Number: ");
    scanf("%d", &acc.accNo);

    // clear input buffer before PIN
    while (getchar() != '\n');

    printf("Set 4-Digit Pin: ");
    for (int i = 0; i < 4; i++)
    {
        acc.pin[i] = getchar();
        printf("*");
    }
    acc.pin[4] = '\0';

    printf("\nPin Successfully Set!\n");

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("Account Added Successfully!!\n");
}

void viewAccount()
{
    struct Account acc;
    FILE *fp;
    int found = 0, accNo;

    fp = fopen("data.dat", "rb");
    if (fp == NULL)
    {
        printf("No Record Found!\n");
        return;
    }

    printf("Enter Account No: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accNo == accNo)
        {
            printf("\n======Account Details======\n");
            printf("Name       : %s\n", acc.name);
            printf("Account No : %d\n", acc.accNo);
            printf("Balance    : %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Exist!\n");

    fclose(fp);
}

void deposite()
{
    struct Account acc;
    FILE *fp;
    int found = 0, accNo;
    float amount;

    fp = fopen("data.dat", "rb+");
    if (fp == NULL)
    {
        printf("No Record Found!\n");
        return;
    }

    printf("Enter Account No: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accNo == accNo)
        {
            printf("Enter Amount To Deposite: ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Invalid Amount!\n");
                found = 1;
                break;
            }

            acc.balance += amount;
            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("$%.2f Deposited Successfully!\n", amount);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Exist!\n");

    fclose(fp);
}

void withdraw()
{
    struct Account acc;
    FILE *fp;
    int found = 0, accNo;
    float amount;

    fp = fopen("data.dat", "rb+");
    if (fp == NULL)
    {
        printf("No Record Found!\n");
        return;
    }

    printf("Enter Account No: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accNo == accNo)
        {
            printf("Enter Amount To Withdraw: ");
            scanf("%f", &amount);

            if (acc.balance < amount)
            {
                printf("Insufficient Balance!\n");
                found = 1;
                break;
            }

            acc.balance -= amount;
            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("$%.2f Withdrawn Successfully!\n", amount);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Exist!\n");

    fclose(fp);
}

void checkBalance()
{
    struct Account acc;
    FILE *fp;
    int accNo, found = 0;

    fp = fopen("data.dat", "rb");
    if (fp == NULL)
    {
        printf("No Record Found!\n");
        return;
    }

    printf("Enter Account No: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accNo == accNo)
        {
            printf("Current Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Exist!\n");

    fclose(fp);
}