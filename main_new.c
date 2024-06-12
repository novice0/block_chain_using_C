#include "crypto_new.c"

int main()
{

  // End goal is to create a public distribution ledger which gets updated every time a transaction takes place in the system
  Blockchain master;
  FILE *f;
  init_blockchain(&master);
  int num_users = 2;
  user A[4];
  char key[MAX_KEY];
  float funds;
  FILE *file;
  char line[MAX_LINE_LENGTH];
  Block B[4];
  printf("\n");
  // Open the file for reading
  file = fopen("logo.txt", "r");
  if (file == NULL)
  {
    perror("Error opening file");
    return 1;
  }

  // Read and print each line of ASCII art
  while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
  {
    printf("%s", line); // Print the line
  }

  // Close the file
  fclose(file);
  printf("\n");
  printf(ANSI_COLOR_MAGENTA "Demonstration of Blockchain technology using CryptoCurrency!\n" ANSI_COLOR_RESET);
  printf("Setting up a system of 4 friends...\n");
  for (int i = 0; i < 4; i++)
  {
    printf("Enter username (Max length of username is 10 characters long): ");
    scanf("%s", A[i].name);
    printf("Enter private key(Never share your private key!): ");
    scanf("%s", A[i].private_key);
    A[i].public_key = generateRandomKey();
    printf("%s, your public key is: %s\n", A[i].name, A[i].public_key);
  }

  // In the Backend all users are given with a wallet which is also identified using their username
  printf("Entering initial funds into the users' wallet:\n");
  printf("To enter funds into one's wallet, private key is required.\n");
  for (int i = 0; i < 4; i++)
  {
    printf("Enter private key for %s's wallet: ", A[i].name);
    scanf("%s", key);
    if (strcmp(key, A[i].private_key) == 0)
    {
      printf("Enter funds into %s's wallet: ", A[i].name);
      scanf("%f", &A[i].w.balance);
      A[i].w.name = A[i].name;
    }
    else
    {
      printf("%s's wallet not accessed! Operation terminated.\n", A[i].name);
    }
  }

  // An array of wallets. This is essential for compartmentalization.
  Wallet w[4];
  for (int i = 0; i < 4; i++)
  {
    w[i] = A[i].w;
    // printf("%f\n", w[i].balance);
  }

  // Blockchain is relevant when there are transacions taking place
  Transaction t; // A transaction is recorded.
  printf("Suppose a number of transactions take place. And here we simulate all the possible conditions.\n");
  printf("After every transaction a block is created which has the details of the transaction as well as those of the user wallets'\n");
  printf("Case 1: Simple deposition of funds into one's own account.\n");
  for (int i = 0; i < 4; i++)
  {
    printf("Enter private key for %s's wallet: ", A[i].name);
    scanf("%s", key);
    if (strcmp(key, A[i].private_key) == 0)
    {
      printf("Enter funds into %s's wallet: ", A[i].name);
      scanf("%f", &funds);

      deposit(&A[i], funds);

      oneTransact(&t, &A[i], funds);
      // Wallets updated

      for (int i = 0; i < 4; i++)
      {
        w[i] = A[i].w;
        printf("%f\n", w[i].balance);
      }
      // printf("%f\n", w[i].balance);

      Block *a = create_block(w, t);
      add_to_blockchain(&master, a);
      // free(a);
      update_index(&master);
      create_sha(&master);
      // disp_chain_2(&master);
      disp_latest_block(&master);
      transfer_to_file(&master, f);
    }
    else
    {
      printf("%s's wallet not accessed! Operation terminated.\n", A[i].name);
    }
  }

  /*Block *a = create_block(&w[0], t); // A block is created.
  add_to_blockchain(&master, a);
  Block *b = create_block(&w[1], t); // A block is created.
  add_to_blockchain(&master, b);
  Block *c = create_block(&w[2], t); // A block is created.
  add_to_blockchain(&master, c);
  Block *d = create_block(&w[3], t); // A block is created.
  add_to_blockchain(&master, d);

  printf("funds stored!\n");
  update_index(&master);
  create_sha(&master);*/

  // printf("Displaying the public distribution ledger\n");
  // disp_chain_2(&master);

  printf("Case 2: Simple deduction of funds from one's own account.\n");
  for (int i = 0; i < 4; i++)
  {
    printf("Enter private key for %s's wallet: ", A[i].name);
    scanf("%s", key);
    if (strcmp(key, A[i].private_key) == 0)
    {
      printf("Enter funds into %s's wallet: ", A[i].name);
      scanf("%f", &funds);

      withdraw(&A[i], funds);

      oneTransact(&t, &A[i], funds);
      // Wallets updated
      for (int i = 0; i < 4; i++)
      {
        w[i] = A[i].w;
        // printf("%f\n", w[i].balance);
      }
      Block *b = create_block(w, t);
      add_to_blockchain(&master, b);
      update_index(&master);
      create_sha(&master);
      // disp_chain_2(&master);
      disp_latest_block(&master);
      transfer_to_file(&master, f);
    }
    else
    {
      printf("%s's wallet not accessed! Operation terminated.\n", A[i].name);
    }
  }
  printf("Displaying the public distribution ledger\n");
  disp_chain_2(&master);

  printf("Case 3: %s transferring fund to %s's wallet (The goal here is to use the private key to access self wallet and public key to access reciever's wallet)\n", A[1].name, A[3].name);
  printf("Enter private key for %s's wallet: ", A[1].name);
  scanf("%s", key);
  if (strcmp(key, A[1].private_key) == 0)
  {
    printf("Enter %s's public key: ", A[3].name);
    scanf("%s", key);
    if (strcmp(key, A[3].public_key) == 0)
    {
      printf("Enter funds into %s's wallet: ", A[3].name);
      scanf("%f", &funds);
      transfer_funds_with_fee(&A[1], &A[3], funds, 0.00000001 * funds);
      twoTransact(&t, &A[1], &A[2], funds);
      w[1] = A[1].w;
      w[3] = A[3].w; // Wallets updated
      Block *c = create_block(w, t);
      add_to_blockchain(&master, c);
      update_index(&master);
      create_sha(&master);
      // disp_chain_2(&master);
      disp_latest_block(&master);
      transfer_to_file(&master, f);
    }
    else
    {
      printf("%s's wallet not accessed! Operation terminated.\n", A[3].name);
    }
  }
  else
  {
    printf("%s's wallet not accessed! Operation terminated.\n", A[1].name);
  }
}
