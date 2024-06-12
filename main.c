#include "crypto.c"

void press_any_key_to_continue()
{
  printf("Press any key to continue...");
  fflush(stdout);
  while (getchar() != '\n')
    ;
  getchar(); // Wait for user input
}

bool secure_string_compare(const char *s1, const char *s2)
{
  size_t len1 = strlen(s1);
  size_t len2 = strlen(s2);

  // Early return if lengths are different
  if (len1 != len2)
  {
    return false;
  }

  // Constant-time comparison to avoid timing attacks
  int result = 0;
  for (size_t i = 0; i < len1; ++i)
  {
    result |= s1[i] ^ s2[i];
  }

  return result == 0; // If result is 0, strings are equal
}

/*int main()
{
  int mode;
  char username[MAX_USERNAME];
  char *privkey;
  char pkey[MAX_KEY];
  User *tempuser;
  double amount;

  Walletlist wlist;
  init_walletlist(&wlist);
  Userlist ulist;
  init_userlist(&ulist);

  printf("Welcome to _____ Services\n");
  do
  {
    display_menu();
    scanf("%d", &mode);
    switch (mode)
    {
    case 1:
      privkey = (char *)malloc(sizeof(char) * MAX_KEY);
      printf("You want to create a new account!\n");
      printf("Please enter a Username (max 8 char long!): ");
      scanf("%s", username);
      printf("Please set your private key (Never share your private key with others.\nOur service takes utmost care in maintaining isolation of user private keys) :");
      scanf("%s", privkey);
      create_user(username, privkey, &wlist, &ulist);
      free(privkey);
      press_any_key_to_continue();
      break;
    case 2:
      tempuser = NULL;
      printf("You want to deposit funds to your wallet\n");
      printf("Enter username: ");
      scanf("%s", username);
      for (int i = 0; i < ulist.length; i++)
      {
        if (strcmp(username, ulist.Users[i].name) == 0)
        {
          tempuser = &ulist.Users[i];
          break;
        }
      }
      if (tempuser == NULL)
      {
        printf("User does not exist!\n");
      }
      else
      {
        printf("Enter your private key: ");
        scanf("%s", pkey);
        if (pkey == tempuser->private_key)
        {
          printf("Enter amount to be deposited!\n");
          scanf("%lf", &amount);
          deposit(tempuser, amount);
        }
        else
        {
          printf("Incorrect private key. Operation terminated!\n");
        }
      }
      for (int i = 0; i < MAX_KEY; i++)
      {
        pkey[i] = '\0';
      }
      press_any_key_to_continue();
      break;
    case 3:
    case 4:
      printf("Exiting program...\n");
      break;
    case 5:
      // Test mode
      for (int i = 0; i < ulist.length; i++)
      {
        printf("%s\n", ulist.Users[i].name);
      }
      break;
    default:
      printf("Invalid choice! Please try again.\n");
    }
  } while (mode != 4);
  return 0;
}*/
int main()
{
  // Other variable declarations and initializations...

  int mode;
  char username[MAX_USERNAME];
  char privkey[MAX_KEY]; // Modified to avoid dynamic memory allocation
  User *tempuser;
  double amount;

  Walletlist wlist;
  init_walletlist(&wlist);
  Userlist ulist;
  init_userlist(&ulist);

  printf("Welcome to _____ Services\n");
  do
  {
    display_menu();
    scanf("%d", &mode);

    switch (mode)
    {
    case 1:
      printf("You want to create a new account!\n");
      printf("Please enter a Username (max 8 char long!): ");
      scanf("%s", username);
      printf("Please set your private key: ");
      scanf("%s", privkey);
      create_user(username, privkey, &wlist, &ulist);
      press_any_key_to_continue();
      break;
    case 2:
      // Deposit funds to wallet...
      break;
    case 3:
    case 4:
      printf("Exiting program...\n");
      break;
    case 5:
      // Test mode...
      for (int i = 0; i < ulist.length; i++)
      {
        printf("%s\n", ulist.Users[i].name);
      }
      break;
    default:
      printf("Invalid choice! Please try again.\n");
    }

  } while (mode != 4);

  return 0;
}
