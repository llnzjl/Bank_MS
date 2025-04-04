#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    int accountNumber;
    char name[50];
    double balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int totalAccounts = 0;

void saveAccountsToFile() {
    FILE* file = fopen("accounts.dat", "wb");
    if (file == NULL) {
        printf("Error saving accounts!\n");
        return;
    }
    fwrite(&totalAccounts, sizeof(int), 1, file);
    fwrite(accounts, sizeof(Account), totalAccounts, file);
    fclose(file);
}

void loadAccountsFromFile() {
    FILE* file = fopen("accounts.dat", "rb");
    if (file == NULL) return;
    fread(&totalAccounts, sizeof(int), 1, file);
    fread(accounts, sizeof(Account), totalAccounts, file);
    fclose(file);
}

void createAccount() {
    if (totalAccounts >= MAX_ACCOUNTS) {
        printf("Cannot create more accounts. Limit reached!\n");
        return;
    }
    Account newAcc;
    newAcc.accountNumber = totalAccounts + 1000;
    printf("Enter name: ");
    scanf(" %[^\n]", newAcc.name);
    newAcc.balance = 0;
    accounts[totalAccounts++] = newAcc;
    saveAccountsToFile();
    printf("Account created successfully! Account No: %d\n", newAcc.accountNumber);
}
void deleteAccount() {
    int accNo;
    printf("Enter account number to delete: ");
    scanf("%d", &accNo);
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accNo) {
            for (int j = i; j < totalAccounts - 1; j++) {
                accounts[j] = accounts[j + 1]; 
            }
            totalAccounts--;
            saveAccountsToFile();
            printf("Account deleted successfully!\n");
            return;
        }
    }
    printf("Account not found!\n");
}
void depositMoney() {
    int accNo;
    double amount;
    printf("Enter account number: ");
    scanf("%d", &accNo);
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accNo) {
            printf("Enter amount to deposit: ");
            scanf("%lf", &amount);
            accounts[i].balance += amount;
            saveAccountsToFile();
            printf("Deposited successfully! New balance: %.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Account not found!\n");
}

void withdrawMoney() {
    int accNo;
    double amount;
    printf("Enter account number: ");
    scanf("%d", &accNo);
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accNo) {
            printf("Enter amount to withdraw: ");
            scanf("%lf", &amount);
            if (accounts[i].balance < amount) {
                printf("Insufficient balance!\n");
                return;
            }
            accounts[i].balance -= amount;
            saveAccountsToFile();
            printf("Withdrawn successfully! New balance: %.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Account not found!\n");
}

void checkBalance() {
    int accNo;
    printf("Enter account number: ");
    scanf("%d", &accNo);
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accNo) {
            printf("Account Holder: %s\nBalance: %.2f\n", accounts[i].name, accounts[i].balance);
            return;
        }
    }
    printf("Account not found!\n");
}

void listAccounts() {
    if (totalAccounts == 0) {
        printf("No accounts found!\n");
        return;
    }
    printf("\nList of Accounts:\n");
    printf("---------------------------------\n");
    for (int i = 0; i < totalAccounts; i++) {
        printf("Account No: %d | Name: %s | Balance: %.2f\n", accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
    }
}

void mainMenu() {
    int choice;
    do {
        printf("\n*** BANK MANAGEMENT SYSTEM ***\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. List Accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (scanf("%d", &choice) != 1) {
            printf("error");
            break;
        }
        else {

            switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: listAccounts(); break;
            case 6: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice! Try again.\n");
            }
        }
    } while (choice != 6);
}

int main() {
    loadAccountsFromFile();
    mainMenu();
    return 0;
}
