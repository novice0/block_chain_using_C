// ask the user for entering his privte key and give him a generated public key. create_new_user.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TRANSACTIONS 100
#define MAX_ADDRESS_LENGTH 100
#define MAX_BLOCKS 100
#define KEY 20

// Structure to represent a transaction
typedef struct
{
    float amount;
    char sender_key[MAX_ADDRESS_LENGTH];
    char receiver_key[MAX_ADDRESS_LENGTH];
} Transaction;

typedef struct
{
    float balance;
    char name[KEY];
} Wallet;

typedef struct
{
    Wallet w;
    char private_key[KEY];
    char public_key[KEY];
    int num_transactions;
} user;

typedef struct
{
    int index; // the block number
    Wallet wal[KEY];
    Transaction t;
    char previous_hash[65]; // SHA-256 hash of the previous block
    char hash[65];          // SHA-256 hash of the current block
    struct Block *b;
} Block;

typedef Block *Blockchain;

void init_blockchain(Blockchain *b)
{
    *b = NULL;
    return;
}

// Function to deposit funds into the wallet
void deposit(user *a, float amount)
{
    if (amount <= 0)
    {
        printf("\nTransaction Failed!!");
        return; // Invalid input
    }
    a->w.balance += amount;
    return;
}

// Function to withdraw funds from the wallet
void withdraw(user *a, float amount)
{
    if (a->w.balance <= amount || amount <= 0)
    {
        printf("\nTransaction Failed!!");
        return; // Invalid input or insufficient balance
    }
    a->w.balance -= amount;
    return;
}

// Function to transfer funds from one wallet to another
void transfer_funds_with_fee(user *a, user *b, float amount, float fee)
{
    if (amount <= 0 || amount > a->w.balance)
    {
        printf("\nTransaction Failed!!");
        return; // Invalid input or insufficient balance
    }
    // Deduct funds from sender's wallet
    a->w.balance -= (amount + fee);
    // Add funds to receiver's wallet
    b->w.balance += amount;
    return;
}

// Function to validate a transaction
void validate_transaction(user *a, char priv[])
{
    for (int i = 0; i < KEY; i++)
    {
        if (a->private_key[i] != priv[i])
        {
            printf("\nAccess Denied!!");
            return; // Invalid input or insufficient balance
        }
    }
    printf("\nWelcome!!");
    return;
}

void oneTransact(Transaction *t, user *a, float funds)
{
    t->amount = funds;
    t->receiver_key = a->public_key;
    t->sender_key = a->public_key;
}

int main()
{
    Transaction t;
    user a;
    float amount;
    deposit(&a, amount);
    oneTransact(&t, &a, amount);
}