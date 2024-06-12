// ask the user for entering his privte key and give him a generated public key. create_new_user.

// Basic Description about our project
// a user starts our service..
// he is prompted to make an account - to add a new user in user ADT.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_ADDRESS_LENGTH 100
#define MAX_USERS 1000
#define MAX_USERNAME 10
#define MAX_KEY 8
#define MAX_TRANSACTIONS 100
#define MAX_BLOCKS 100

// Structure to represent a transaction
typedef struct Transaction
{
  float amount;
  char sender_public_key[MAX_ADDRESS_LENGTH];
  char receiver_public_key[MAX_ADDRESS_LENGTH];
} Transaction;

typedef struct Wallet
{
  float balance;
  char *name;
  char *public_key;
} Wallet;

typedef struct Walletlist
{
  int size;
  int length;
  Wallet *wal;
} Walletlist; // Structure for blockchain technology. Frontend blockchain viewing and decentralization.

typedef struct User
{
  char *name;
  char *private_key;
  char *public_key;
  Wallet *w;

} User;

typedef struct Userlist
{
  int size;
  int length;
  User *Users;
} Userlist; // Function storing all users. Backend database for all our users.

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

// --- Transaction functions ---
void validate_transaction(User *a, char priv[]);                         // Function to validate a transaction
void deposit(User *a, float amount);                                     // Function to deposit funds into the wallet
void withdraw(User *a, float amount);                                    // Function to withdraw funds from the wallet
void transfer_funds_with_fee(User *a, User *b, float amount, float fee); // Function to transfer funds from one wallet to another

// --- Block Related Functions ---
Block *create_block(Wallet *wal, Transaction t);                       // Creating a block after making a transaction
void init_blockchain(Blockchain *chain);                               // Initializing linked list of blocks
void add_to_blockchain(Blockchain *chain, Wallet *wal, Transaction t); // Adding a block to the blockchain after it is validated - to update
void update_index(Blockchain *chain);                                  // Updating index of blocks in blockchain
void create_sha(Blockchain *chain);                                    // Creating sha256 hash of all the blocks in the blockchain, as they are the ones which are validated
void update_sha(Blockchain *chain);                                    // Updating previous sha of the blocks
void disp_chain(Blockchain *chain, User *a, char priv[]);              // Displaying the public distribution ledger - to update
void save_chain() {}                                                   // Saving a copy of the chain in a backend text file - to update

// --- User and Wallet related Functions ---
void create_user(char *, char *, Walletlist *, Userlist *);
void update_users(User); // Optional function.
void init_walletlist(Walletlist *w)
{
  w->size = MAX_USERS;
  w->length = 0;
  w->wal = (Wallet *)malloc(sizeof(Wallet) * w->size);
}
int iswalFull(Walletlist *w)
{
  return (w->length == w->size - 1);
}
void add_wallet_to_list(Wallet w, Walletlist *list)
{
  if (iswalFull(list))
    return;
  list->wal[list->length++] = w;
  return;
}
void init_userlist(Userlist *u)
{
  u->size = MAX_USERS;
  u->length = 0;
  u->Users = (User *)malloc(sizeof(User) * u->size);
}

int isusersFull(Userlist *u)
{
  return (u->length == u->size - 1);
}

void add_user_to_list(User *u, Userlist *list)
{
  if (isusersFull(list))
    return;
  list->Users[list->length] = *u;
  list->length++;
  return;
}

// Menu function
void display_menu();