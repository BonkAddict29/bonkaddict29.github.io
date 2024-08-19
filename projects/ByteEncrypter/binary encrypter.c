#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>  

int main() {
    char input[1500];
    char bitPositions[100];
    int bitArray[16];  // To store bit positions to flip
    int bitCount = 0;
    char output[1500] = ""; // To store concatenated result (assuming 100 bytes max)
    char flippedBits[100] = ""; // To store flipped bit positions
    int bitIndex = 0; // To keep track of the bit position in the overall output
    char choice;

    do {
         // Clear the screen at the beginning of each iteration
        #ifdef _WIN32
            system("cls");   // Clear on Windows
        #else
            system("clear"); // Clear on Unix-based
        #endif

        // Reset variables after loop
        memset(input, 0, sizeof(input));
        memset(bitPositions, 0, sizeof(bitPositions));
        memset(bitArray, 0, sizeof(bitArray));
        memset(output, 0, sizeof(output));
        memset(flippedBits, 0, sizeof(flippedBits));
        bitCount = 0;

        // Ask the user for input
        printf("Enter a series of 8-bit bytes separated by spaces: ");
        fgets(input, sizeof(input), stdin);

        // Remove newline character if present
        input[strcspn(input, "\n")] = '\0';

        // Ask which bits to flip
        printf("Enter bit positions to flip (1-8), separated by spaces: ");
        fgets(bitPositions, sizeof(bitPositions), stdin);

        // Process the bit positions
        char *bitToken = strtok(bitPositions, " ");
        while (bitToken != NULL && bitCount < 8) {
            int bit = atoi(bitToken);
            if (bit < 1 || bit > 8) {
                printf("Error: Bit positions must be between 1 and 8.\n");
                return 1;
            }
            bitArray[bitCount++] = bit - 1; // Convert to 0-based index
            bitToken = strtok(NULL, " ");
        }

        // Record flipped bit positions
        for (int i = 0; i < bitCount; i++) {
            char buffer[10];
            sprintf(buffer, "%d", bitArray[i] + 1); // Convert to 1-based index for display
            strcat(flippedBits, buffer);
        }

        // Process each byte
        char *token = strtok(input, " ");
        while (token != NULL) {

            // Ensure the token is 8 bits long
            if (strlen(token) == 8) {

                // Convert binary string to integer
                int byte = strtol(token, NULL, 2);

                // Flip the specified bits
                for (int i = 0; i < bitCount; i++) {
                    byte ^= (1 << bitArray[i]);
                }

                // Skip the frist bit (which should be "0")
                for (int i = 1; i < 8; i++) { 
                    output[strlen(output)] = (byte >> (7 - i)) & 1 ? '1' : '0';
                }
            } 
            // Get the next byte
            token = strtok(NULL, " ");
        }

        // Null-terminate the output string
        output[strlen(output)] = '\0';

        // Print the results
        printf("Output: 7~%s_%s\n", flippedBits, output);

        // Ask the user if they want to run again
        printf("Press 'R' to run again or any other key to exit: ");
        choice = getch(); 

    } while (choice == 'R' || choice == 'r'); 

    printf("Program terminated.\n");
    return 0;
}
