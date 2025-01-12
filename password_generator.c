#include <openssl/rand.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate a password
void generate_password(char *password, int length, int use_special_chars) {
    const char charset_basic[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const char charset_special[] = "!@#$%^&*()";
    char charset[128]; // Final charset to use
    strcpy(charset, charset_basic); // Start with basic charset

    if (use_special_chars) {
        strcat(charset, charset_special); // Add special characters if requested
    }

    size_t charset_size = strlen(charset);

    for (int i = 0; i < length; i++) {
        unsigned char random_byte;
        if (RAND_bytes(&random_byte, 1)) {
            password[i] = charset[random_byte % charset_size];
        } else {
            printf("Failed to generate random byte.\n");
            password[0] = '\0'; // Return an empty string if random byte generation fails
            return;
        }
    }
    password[length] = '\0'; // Null-terminate the string
}

// Function to evaluate password security
int evaluate_password_security(const char *password) {
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;

    // Check each character in the password
    for (int i = 0; i < strlen(password); i++) {
        if (isupper(password[i])) has_upper = 1;
        else if (islower(password[i])) has_lower = 1;
        else if (isdigit(password[i])) has_digit = 1;
        else has_special = 1;
    }

    // Evaluate security criteria
    if (strlen(password) >= 8 && has_upper && has_lower && has_digit && has_special) {
        return 1; // Password is secure
    } else {
        return 0; // Password is not secure
    }
}

int main() {
    int choice;
    int password_length;
    int use_special_chars;
    char password[256]; // Buffer for the password (max length 255)
    char user_password[256]; // Buffer for the user's password

    while (1) {
        // Display menu
        printf("\n=== Password Generator Menu ===\n");
        printf("1. Generate a secure password\n");
        printf("2. Check your own password for security\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // Ask user for password length
            printf("Enter password length (8-255): ");
            scanf("%d", &password_length);
            if (password_length < 8 || password_length > 255) {
                printf("Invalid password length. Must be between 8 and 255.\n");
                continue;
            }

            // Ask if special characters should be included
            printf("Include special characters? (1 for yes, 0 for no): ");
            scanf("%d", &use_special_chars);

            // Generate a secure password using a loop
            for (int attempts = 1; ; attempts++) {
                generate_password(password, password_length, use_special_chars);

                if (evaluate_password_security(password)) {
                    printf("\nGenerated secure password: %s\n", password);
                    printf("Password generated in %d attempt(s).\n", attempts);
                    break;
                }
            }
        } else if (choice == 2) {
            // Check user's own password
            printf("Enter your password: ");
            scanf("%s", user_password);

            // Evaluate the user's password
            if (evaluate_password_security(user_password)) {
                printf("Your password is secure!\n");
            } else {
                printf("Your password is not secure. Consider making it longer or adding uppercase letters, digits, or special characters.\n");
            }
        } else if (choice == 3) {
            printf("Exiting... Goodbye!\n");
            break; // Exit the loop
        } else {
            printf("Invalid choice. Please select 1, 2, or 3.\n");
        }
    }

    return 0;
}