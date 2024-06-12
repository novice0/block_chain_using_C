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
typedef struct Transaction
{
    float amount;
    char sender_key[MAX_ADDRESS_LENGTH];
    char receiver_key[MAX_ADDRESS_LENGTH];
} Transaction;

typedef struct Wallet
{
    float balance;
    char name[KEY];
} Wallet;

typedef struct user
{
    Wallet w;
    char private_key[KEY];
    char public_key[KEY];
} user;

typedef struct Block
{
    int index; // the block number
    Wallet *wal;
    Transaction t;
    char *previous_hash; // SHA-256 hash of the previous block - if block is first in block chain - previous_hash = '-1'
    char *hash;          // SHA-256 hash of the current block
    struct Block *next;
} Block;

typedef Block *Blockchain; // This describes the public distribution ledger.
