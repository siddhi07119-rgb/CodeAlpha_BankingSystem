#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accountNumber;
    char name[50];
    double balance;
};

void saveAccount(struct Account acc) {
    FILE *fp = fopen("bank.dat", "wb");
    if (fp == NULL) {
        printf("Error saving account!\n");
        return;
    }
    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);
}

int loadAccount(struct Account *acc) {
    FILE *fp = fopen("bank.dat", "rb");
    if (fp == NULL) return 0;
    int result = fread(acc, sizeof(*acc), 1, fp);
    fclose(fp);
    return result == 1;
}

void deposit(struct Account *acc) {
    double amount;
    printf("Enter deposit amount: ");
    if (scanf("%lf", &amount) != 1) {
        printf("Invalid input!\n");
        return;
    }
    if (amount <= 0) {
        printf("Invalid amount!\n");
    } else {
        acc->balance += amount;
        saveAccount(*acc);
        printf("Deposit successful!\n");
    }
}

void withdraw(struct Account *acc) {
    double amount;
    printf("Enter withdrawal amount: ");
    if (scanf("%lf", &amount) != 1) {
        printf("Invalid input!\n");
        return;
    }
    if (amount <= 0) {
        printf("Invalid amount!\n");
    } else if (amount > acc->balance) {
        printf("Insufficient balance!\n");
    } else {
        acc->balance -= amount;
        saveAccount(*acc);
        printf("Withdrawal successful!\n");
    }
}

void balanceEnquiry(struct Account acc) {
    printf("\nAccount Number: %d\n", acc.accountNumber);
    printf("Account Holder: %s\n", acc.name);
    printf("Available Balance: %.2f\n", acc.balance);
}

int main(void) {
    struct Account acc;
    int choice;

    if (!loadAccount(&acc)) {
        acc.accountNumber = 1001;
        acc.balance = 0.0;

        printf("Enter account holder name: ");
        if (fgets(acc.name, sizeof(acc.name), stdin) == NULL) {
            strcpy(acc.name, "Account Holder");
        }
        acc.name[strcspn(acc.name, "\n")] = '\0';
        saveAccount(acc);
    }

    while (1) {
        printf("\n===== BANKING SYSTEM =====\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Balance Enquiry\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                deposit(&acc);
                break;
            case 2:
                withdraw(&acc);
                break;
            case 3:
                balanceEnquiry(acc);
                break;
            case 4:
                printf("Thank you for using our Banking System!\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
