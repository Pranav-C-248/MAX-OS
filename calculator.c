#include "calculator.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/screen_driver.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/keyboard.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/util.h"


int evaluate_expression(char *expr) {
    int num1 = 0, num2 = 0;
    char op;
    char *ptr = expr;

    // Parse first number
    while (*ptr && (*ptr >= '0' && *ptr <= '9')) {
        num1 = num1 * 10 + (*ptr - '0');
        ptr++;
    }

    // Skip whitespace
    while (*ptr && *ptr == ' ') ptr++;

    // Operator
    op = *ptr++;

    // Skip whitespace
    while (*ptr && *ptr == ' ') ptr++;

    // Parse second number
    while (*ptr && (*ptr >= '0' && *ptr <= '9')) {
        num2 = num2 * 10 + (*ptr - '0');
        ptr++;
    }

    // Calculation based on the operator
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num2 != 0 ? num1 / num2 : 0; // Handle division by zero
        default: return 0;
    }
}

void run_calculator() {
    char input[256];
    print_string("Enter calculation (example: 12 + 34): ");
    read_string(input); // Ensure you have a method to read strings from the keyboard
    int result = evaluate_expression(input);
    print_string("Result: ");
    print_int(result);
    print_string("\n>");
}
