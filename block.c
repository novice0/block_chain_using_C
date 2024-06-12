#include "new.c"
#include "block.h"
#include "sha256.c"
#include <time.h>

#define key 20
#define USERNAME_LENGTH 8

// Function to generate a random username
char *generateRandomUsername()
{
  char *username = (char *)malloc((USERNAME_LENGTH + 1) * sizeof(char)); // Extra space for '\0'
  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  srand((unsigned int)time(NULL)); // Seed for random number generation

  // Construct the random username by selecting characters randomly from the charset
  for (int i = 0; i < USERNAME_LENGTH; i++)
  {
    username[i] = charset[rand() % (sizeof(charset) - 1)];
  }

  username[USERNAME_LENGTH] = '\0'; // Null-terminate the string

  return username;
}

// After the transaction is made a block is created.

// Functions to include related to block

// Creating a block after making a transaction
Block *create_block(Wallet *wal, Transaction t)
{
  Block *nn;
  nn = (Block *)malloc(sizeof(Block));
  if (nn)
  {
    nn->index = 0;
    nn->wal = (Wallet *)malloc(sizeof(Wallet));
    nn->wal = wal;
    nn->t = t;
    nn->hash = (char *)malloc(sizeof(char) * 65);
    // nn->hash = "-1";
    nn->previous_hash = (char *)malloc(sizeof(char) * 65);
    // nn->previous_hash = "-1";
    nn->next = NULL;
  }
  return nn;
}

// Initializing linked list of blocks
void init_blockchain(Blockchain *chain)
{
  *chain = NULL;
  return;
}

// Adding a block to the blockchain after it is validated
void add_to_blockchain(Blockchain *chain, Wallet *wal, Transaction t)
{
  Block *b = create_block(wal, t);
  Block *p;
  if (!*chain)
  {
    *chain = b;
    return;
  }
  p = *chain;
  while (p->next)
  {
    p = p->next;
  }
  p->next = b;
  return;
}

// Updating index of blocks in blockchain
void update_index(Blockchain *chain)
{
  if (!*chain)
  {
    printf("\nSystem Blockchain Error - block chain doesn't exist!!\n");
    return;
  }
  Block *b = *chain;
  int i = 1;
  while (b)
  {
    b->index = i;
    i++;
    b = b->next;
  }
  return;
}

// Creating sha256 hash of all the blocks in the blockchain, as they are the ones which are validated
void create_sha(Blockchain *chain)
{
  if (!*chain)
  {
    printf("\nSystem Blockchain Error - block chain doesn't exist!!\n");
    return;
  }
  Block *b = *chain;
  char *str;
  str = (char *)malloc(sizeof(char));
  while (b)
  {
    sprintf(str, "%d", b->index);
    //  sha256_easy_hash_hex(str, strlen(str), b->hash);
    // char *str = ;
    char hash[65] = {0}; // Notice the additional null-byte
    sha256_easy_hash_hex(str, strlen(str), b->hash);
    b = b->next;
  }
}

// Updating previous sha of the blocks
void update_sha(Blockchain *chain)
{
  if (!*chain)
  {
    printf("\nSystem Blockchain Error - block chain doesn't exist!!\n");
    return;
  }
  Block *b1, *b2;
  b1 = *chain;

  while (b1)
  {
    b2 = b1;
    b1 = b1->next;
    if (b2 == *chain)
    {
      b2->previous_hash = "-1";
    }
    else
    {
      b1->previous_hash = b2->hash;
    }
  }
  return;
}

// Displaying the public distribution ledger
void disp_chain(Blockchain *chain) // update this after recieving ishan's code.
{
  if (!*chain)
  {
    printf("\nSystem Blockchain Error - block chain doesn't exist!!\n");
    return;
  }
  Block *b = *chain;
  while (b)
  {
    printf("\nBlock index: %d\n", b->index);
    printf("Name: %s\n", b->wal->name);
    printf("Balance: %f\n", b->wal->balance);
    printf("Hash Number: %s", b->hash); // Works as a time stamp
    b = b->next;
  }
}

// Saving a copy of the chain in a backend text file
void save_chain() {}

int main()
{
  const char *str = "1";
  char hash[65] = {0}; // Notice the additional null-byte
  sha256_easy_hash_hex(str, strlen(str), hash);
  printf("%s\n", hash);
  Transaction t;
  Wallet w;
  Block *b1 = create_block(&w, t);
  printf("done");
  Blockchain master;
  init_blockchain(&master);
  add_to_blockchain(&master, &w, t);
  add_to_blockchain(&master, &w, t);
  add_to_blockchain(&master, &w, t);
  update_index(&master);
  create_sha(&master);
  disp_chain(&master);
  // create_sha(&master);
  // update_sha(&master);
  // disp_chain(&master);
}

// Additional things to do:
// 1. Compile all three parts,
// 2. Add linked list of users feature
// 3. Add saving userdata in backend text file
// 4. Merkel Trees
// 3. Beautify terminal output