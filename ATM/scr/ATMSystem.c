#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertCard();
void greetUser(const char* name);
void displayMenu();
void checkBalance(float balance);
float depositMoney(float balance);
float withdrawMoney(float balance);
float transferMoney(float balance);
void askBalanceDisplay(float balance);
int verifyPin();
int validateIbank(const char* ibank);
void exitATM();


#define PIN 1234  
#define MAX_ATTEMPTS 3

int main() {
    float balance = 1000.00;  
    int pinVerified = 0;
    int attempts = 0;
    int choice;
    char continueTransaction;
    char cardholderName[30] = "Anagnostou";  

    insertCard();
  
    greetUser(cardholderName);

    while (attempts < MAX_ATTEMPTS && !pinVerified) {
        if (verifyPin()) {
            pinVerified = 1;
            printf("PIN verified successfully.\n\n");
        } else {
            attempts++;
            printf("Incorrect PIN. Attempts left: %d\n\n", MAX_ATTEMPTS - attempts);
        }
    }

    if (!pinVerified) {
        printf("Too many incorrect attempts. Exiting.\n\n");
        return 1;
    }
    
    printf( "What transaction would you like to perform?\n\n");

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(balance);
                break;
            case 2:
                balance = depositMoney(balance);
                break;
            case 3:
                balance = withdrawMoney(balance);
                askBalanceDisplay(balance);  
                break;
            case 4:
                balance = transferMoney(balance);
                break;
            case 5:
                exitATM();
                return 0;
            default:
                printf("Invalid choice! Please try again.\n\n");
        }

        while (1) {
            printf("\nWould you like to make another transaction? (y/n): ");
            scanf(" %c", &continueTransaction);

            if (continueTransaction == 'y' || continueTransaction == 'Y' || 
                continueTransaction == 'n' || continueTransaction == 'N') {
                break;  
            } else {
                printf("\nInvalid selection!\nPlease enter 'y' for Yes or 'n' for No.\n\n");
            }
        }

    } while (continueTransaction == 'y' || continueTransaction == 'Y');

  
    printf("\nThank you for using our ATM. Please remove your card.\n\n");

    return 0;
}

void insertCard() {
    printf("===== Welcome to the ATM System =====\n");
    printf("Please insert your card (Press Enter to continue)...\n\n");
    getchar();  // Wait for Enter to simulate card insertion
}

void greetUser(const char* name) {
    printf("Hello, Mr/Mrs. %s!\n\n", name);
}

void displayMenu() {
    printf("\n==== ATM Menu ====\n");
    printf("1. Check Balance\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Transfer Money\n");
    printf("5. Exit\n\n");
}

void checkBalance(float balance) {
    printf("Your current balance is: $%.2f\n\n", balance);
}

float depositMoney(float balance) {
    float depositAmount;
    printf("Enter amount to deposit: $");
    scanf("%f", &depositAmount);

    if (depositAmount <= 0) {
        printf("Invalid deposit amount.\n\n");
    } else {
        balance += depositAmount;
        printf("$%.2f deposited successfully.\n\n", depositAmount);
        checkBalance(balance);
    }
    return balance;
}

float withdrawMoney(float balance) {
    float withdrawAmount;
    printf("Enter amount to withdraw: $");
    scanf("%f", &withdrawAmount);

    if (withdrawAmount <= 0) {
        printf("Invalid withdrawal amount.\n\n");
    } else if (withdrawAmount > balance) {
        printf("Insufficient balance. Transaction canceled.\n\n");
    } else {
        balance -= withdrawAmount;
        printf("$%.2f withdrawn successfully.\n\n", withdrawAmount);
    }
    return balance;
}

float transferMoney(float balance) {
    char ibank[20];
    float transferAmount;

    //Another user's iBank--> US1234567890
    printf("Enter the recipient's iBank number : ");
    scanf("%s", ibank);
    if (!validateIbank(ibank)) {
        printf("Invalid iBank number. Transaction canceled.\n\n");
        return balance;
    }

    printf("Enter amount to transfer: $");
    scanf("%f", &transferAmount);

    if (transferAmount <= 0) {
        printf("Invalid transfer amount. Transaction canceled.\n\n");
    } else if (transferAmount > balance) {
        printf("Insufficient balance. Transaction canceled.\n\n");
    } else {
        balance -= transferAmount;
        printf("$%.2f transferred successfully to iBank %s.\n\n", transferAmount, ibank);
    }

    return balance;
}

void askBalanceDisplay(float balance) {
    char displayChoice;
    printf("Would you like to display the remaining balance on (s)creen or (r)eceipt? ");
    scanf(" %c", &displayChoice);

    if (displayChoice == 's' || displayChoice == 'S') {
        checkBalance(balance);
    } else if (displayChoice == 'r' || displayChoice == 'R') {
        printf("Printing receipt... Your remaining balance is: $%.2f\n\n", balance);
    } else {
        printf("Invalid choice. Returning to main menu.\n\n");
    }
}

int verifyPin() {
    int enteredPin;
    printf("Please enter your PIN: ");
    scanf("%d", &enteredPin);

    if (enteredPin == PIN) {
        return 1;
    } else {
        return 0;
    }
}

int validateIbank(const char* ibank) {
  
    if (strlen(ibank) == 12 && ibank[0] == 'U' && ibank[1] == 'S') {
        return 1;
    } else {
        return 0;
    }
}

void exitATM() {
    printf("Thank you for using our ATM. Goodbye!\n\n");
}