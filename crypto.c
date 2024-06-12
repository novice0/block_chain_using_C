#include "crypto.h"

// --- Transaction functions ---

// Function to validate a transaction
void validate_transaction(User *a, char priv[])
{
  for (int i = 0; i < MAX_KEY; i++)
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

// Function to deposit funds into the wallet
void deposit(User *a, float amount)
{
  if (amount <= 0)
  {
    printf("\nTransaction Failed!!");
    return; // Invalid input
  }
  a->w->balance += amount;
  return;
}

// Function to withdraw funds from the wallet
void withdraw(User *a, float amount)
{
  if (a->w->balance <= amount || amount <= 0)
  {
    printf("\nTransaction Failed!!");
    return; // Invalid input or insufficient balance
  }
  a->w->balance -= amount;
  return;
}

// Function to transfer funds from one wallet to another
void transfer_funds_with_fee(User *a, User *b, float amount, float fee)
{
  if (amount <= 0 || amount > a->w->balance)
  {
    printf("\nTransaction Failed!!");
    return; // Invalid input or insufficient balance
  }
  // Deduct funds from sender's wallet
  a->w->balance -= (amount + fee);
  // Add funds to receiver's wallet
  b->w->balance += amount;
  return;
}

// --- User and Wallet related Functions ---

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

void create_user(char *uname, char *priv, Walletlist *wlist, Userlist *ulist)
{
  User *a;
  a = (User *)malloc(sizeof(User));
  if (a)
  {
    a->name = (char *)malloc(sizeof(char) * MAX_USERNAME);
    a->name = uname;
    a->private_key = (char *)malloc(sizeof(char) * MAX_KEY);
    a->private_key = priv;
    a->public_key = (char *)malloc(sizeof(char) * MAX_KEY);
    a->public_key = generateRandomKey();
    a->w = (Wallet *)malloc(sizeof(Wallet));
    if (a->w)
    {
      a->w->name = (char *)malloc(sizeof(char) * MAX_USERNAME);
      a->w->name = a->name;
      a->w->public_key = (char *)malloc(sizeof(char) * MAX_KEY);
      a->w->public_key = a->public_key;
      a->w->balance = 0.0;
      add_wallet_to_list(*(a->w), wlist);
    }
    add_user_to_list(a, ulist);
    printf("Your public access key is: %s\n", a->public_key);
    printf("You will use this public access key to make transactions with other users on the network.\n");
    a = NULL;
  }
  else
  {
    printf("Error in user generation. Please try again!\n");
  }
}

// Menu function
void display_menu()
{

  printf("Please select an option to avail our services:\n");
  printf("1. Create a new account!\n");
  printf("2. Deposit Funds\n");
  printf("3. Withdraw Funds\n");
  printf("4. Exit\n");
  printf("Enter your choice: ");
}
