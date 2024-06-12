#include "crypto_new.h"
#include "sha256.c"

// --- User Related Functions ---

// Function to generate a random username
char *generateRandomKey()
{
  char *username = (char *)malloc((MAX_KEY + 1) * sizeof(char)); // Extra space for '\0'
  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  srand((unsigned int)time(NULL)); // Seed for random number generation

  // Construct the random username by selecting characters randomly from the charset
  for (int i = 0; i < MAX_KEY; i++)
  {
    username[i] = charset[rand() % (sizeof(charset) - 1)];
  }

  username[MAX_KEY] = '\0'; // Null-terminate the string

  return username;
}

// --- Transaction related functions ---

// Function for transactions involving one user
void oneTransact(Transaction *t, user *a, float funds)
{
  t->amount = funds;
  t->receiver_key = a->public_key;
  t->sender_key = a->public_key;
}

// Function for transactions involving two users
void twoTransact(Transaction *t, user *sender, user *reciever, float funds)
{
  t->amount = funds;
  t->sender_key = sender->public_key;
  t->receiver_key = reciever->public_key;
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
bool validate_transaction(user *a, char priv[])
{
  for (int i = 0; i < MAX_KEY; i++)
  {
    if (a->private_key[i] != priv[i])
    {
      printf("\nAccess Denied!!");
      return false; // Invalid input or insufficient balance
    }
  }
  return true;
}

// --- Block Related Functions

// Creation of block
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
void add_to_blockchain(Blockchain *chain, Block *block)
{
  Block *b = block;
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
void disp_chain(Blockchain *chain)
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
    printf("Hash Number: %s\n", b->hash); // Works as a time stamp
    b = b->next;
  }
}

void disp_chain_2(Blockchain *chain)
{
  if (!*chain)
  {
    printf("\nSystem Blockchain Error - block chain doesn't exist!!\n");
    return;
  }
  Block *b = *chain;
  while (b)
  {
    printf(ANSI_COLOR_MAGENTA "  +--------+\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA " /        /|\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "+--------+ |\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "|   %d    | +\n" ANSI_COLOR_RESET, b->index);
    printf(ANSI_COLOR_MAGENTA "|        |/\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "+--------+\n" ANSI_COLOR_RESET);
    printf("Transaction addresses and amount\n");
    printf("From: %s\n", b->t.sender_key);
    printf("To: %s\n", b->t.receiver_key);
    printf("Amount: %f\n", b->t.amount);
    for (int i = 0; i < 4; i++)
    {
      printf("Name: %s\n", b->wal[i].name);
      printf("Balance: %f\n", b->wal[i].balance);
    }
    printf("Hash Number: %s\n", b->hash); // Works as a time stamp
    b = b->next;
  }
}

void disp_latest_block(Blockchain *chain)
{
  if (!*chain)
  {
    printf("\nSystem Blockchain Error - block chain doesn't exist!!\n");
    return;
  }
  Block *b = *chain;
  while (b->next)
  {
    b = b->next;
  }
  printf(ANSI_COLOR_MAGENTA "  +--------+\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_MAGENTA " /        /|\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_MAGENTA "+--------+ |\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_MAGENTA "|   %d    | +\n" ANSI_COLOR_RESET, b->index);
  printf(ANSI_COLOR_MAGENTA "|        |/\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_MAGENTA "+--------+\n" ANSI_COLOR_RESET);
  printf("Transaction addresses and amount\n");
  printf("From: %s\n", b->t.sender_key);
  printf("To: %s\n", b->t.receiver_key);
  printf("Amount: %f\n", b->t.amount);
  for (int i = 0; i < 4; i++)
  {
    printf("Name: %s\n", b->wal[i].name);
    printf("Balance: %f\n", b->wal[i].balance);
  }
  printf("Hash Number: %s\n", b->hash); // Works as a time stamp
}

void transfer_to_file(Blockchain *chain, FILE *f)
{
  char filename[] = "block_chain.txt";
  f = fopen(filename, "a");
  if (f == NULL)
  {
    fprintf(stderr, "Error opening file %s\n", filename);
    return;
  }
  if (!*chain)
  {
    fprintf(f, "\nSystem Blockchain Error - block chain doesn't exist!!\n");
    return;
  }
  Block *b = *chain;
  while (b->next)
  {
    b = b->next;
  }
  fprintf(f, "  +--------+\n");
  fprintf(f, " /        /|\n");
  fprintf(f, "+--------+ |\n");
  fprintf(f, "|   %d    | +\n", b->index);
  fprintf(f, "|        |/\n");
  fprintf(f, "+--------+\n");
  fprintf(f, "Transaction addresses and amount\n");
  fprintf(f, "From: %s\n", b->t.sender_key);
  fprintf(f, "To: %s\n", b->t.receiver_key);
  fprintf(f, "Amount: %f\n", b->t.amount);
  for (int i = 0; i < 4; i++)
  {
    fprintf(f, "Name: %s\n", b->wal[i].name);
    fprintf(f, "Balance: %f\n", b->wal[i].balance);
  }
  fprintf(f, "Hash Number: %s\n", b->hash); // Works as a time stamp
  fclose(f);
  return;
}