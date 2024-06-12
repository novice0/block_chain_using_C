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
#define MAX_LINE_LENGTH 200
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Structure to represent a transaction
typedef struct Transaction
{
  float amount;
  char *sender_key;
  char *receiver_key;
} Transaction;

typedef struct Wallet
{
  float balance;
  char *name;
} Wallet;

typedef struct user
{
  char name[MAX_USERNAME];
  char private_key[MAX_KEY];
  char *public_key;
  Wallet w;
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

// --- User Related Functions ---
char *generateRandomKey(); // Function to generate a random username

// --- Transaction related functions ---
void oneTransact(Transaction *, user *, float);             // Function for transactions involving one user
void twoTransact(Transaction *, user *, user *, float);     // Function for transactions involving two users
void deposit(user *, float);                                // Function to deposit funds into the wallet
void withdraw(user *, float);                               // Function to withdraw funds from the wallet
void transfer_funds_with_fee(user *, user *, float, float); // Function to transfer funds from one wallet to another
bool validate_transaction(user *a, char priv[]);            // Function to validate a transaction

// --- Block Related Functions
Block *create_block(Wallet *, Transaction);    // Creation of block
void init_blockchain(Blockchain *);            // Initializing linked list of blocks
void add_to_blockchain(Blockchain *, Block *); // Adding a block to the blockchain after it is validated
void update_index(Blockchain *);               // Updating index of blocks in blockchain
void create_sha(Blockchain *);                 // Creating sha256 hash of all the blocks in the blockchain, as they are the ones which are validated
void update_sha(Blockchain *);                 // Updating previous sha of the blocks
void disp_chain_2(Blockchain *);               // Displaying the public distribution ledger