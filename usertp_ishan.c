#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define USERNAME_LENGTH 8 // Length of the generated public key

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

int main()
{
    char private_key[50];
    char *public_key;
    float balance;
    char user_name[20];

    while (1)
    {
        printf("Please enter user's name: ");
        scanf("%s", &user_name);

        // Prompt the user to enter a password
        printf("Enter your Private Key (or type 'exit' to quit): ");
        scanf("%s", private_key);

        if (strcmp(private_key, "exit") == 0)
        {
            printf("Exiting...\n");
            break;
        }

        // Generate a random username
        public_key = generateRandomUsername();

        // Display the generated username
        printf("The public key generated for %s is: %s\n", user_name, public_key);

        // Free dynamically allocated memory
        free(public_key);
        printf("Enter the amount of cryptocurrency you would like to invest: ");
        scanf("%f", &balance);
        return 1;
    }

    return 0;
}
