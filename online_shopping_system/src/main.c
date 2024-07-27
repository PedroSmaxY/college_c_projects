// File 2:
// Includes the header file containing necessary libraries, definitions, and functions
#include "../Include/data_operations.h"

// Main function of the program
int main()
{
    // List of available products with their codes, names, prices, and weights
    Product productList[] = {
        {1, "Rice", 2.99, 2.2},
        {2, "Beans", 1.99, 2.2},
        {3, "Pasta", 0.99, 1.1},
        {4, "Flour", 1.99, 1.1},
        {5, "Tuna", 4.99, 5.5},
        {6, "Coffee", 5.99, 1.32},
        {7, "Oil", 2.99, 2.2},
        {8, "Salt", 1.99, 5.5},
        {9, "Milk", 0.99, 2.2},
        {10, "Butter", 3.99, 1.1}};

    // Clears the console
    clearConsole();

    // Initializes the Purchase structure
    Purchase purchase = {.quantityProducts = 0, .totalCost = 0.0, .shippingCost = 0.0};

    // Displays the list of available products
    displayProductList(productList, sizeof(productList) / sizeof(productList[0]));

    // Asks the customer to select the desired products
    selectProducts(&purchase, productList, sizeof(productList) / sizeof(productList[0]));

    // Clears the keyboard input buffer
    clearInputBuffer();

    // Clears the console
    clearConsole();

    // Asks for the region from the customer
    requestRegion(&purchase);

    // Calculates the shipping cost based on the product weight and customer region
    calculateShippingCost(&purchase);

    // Clears the console once again
    clearConsole();

    // Displays the purchase summary
    PurchaseSummary(&purchase);

    getchar();

    return 0;
}
