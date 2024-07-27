// Prevents the header file from being included multiple times during compilation
#ifndef DATA_OPERATIONS_H
#define DATA_OPERATIONS_H

// Includes necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Defines the structure for products
typedef struct
{
    int code;
    char name[50];
    double price;
    double weight;
} Product;

// Defines the structure for a purchase
typedef struct
{
    Product products[50]; // Array of products
    int quantityProducts;
    double priceProducts;
    double totalCost;
    double shippingCost;
    int region;
    char regionName[20];
    char purchaseDateTime[20];
    char estimatedArrival[20];
} Purchase;

// Function to clear the keyboard input buffer
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to clear the console
void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to calculate the shipping cost
void calculateShippingCost(Purchase *purchase)
{
    double standardShipping, weightShipping;

    // Calculates the shipping values based on the region
    switch (purchase->region)
    {
    case 1: // North
        standardShipping = 10.00;
        weightShipping = 15.00;
        break;
    case 2: // Northeast
        standardShipping = 15.00;
        weightShipping = 20.00;
        break;
    case 3: // South
        standardShipping = 8.00;
        weightShipping = 12.00;
        break;
    case 4: // Southeast
        standardShipping = 5.00;
        weightShipping = 10.00;
        break;
    default:
        printf("Invalid region\n");
        break;
    }
    // Sets the shipping cost based on the weight
    for (int i = 0; i < purchase->quantityProducts; i++)
    {
        if (purchase->products[i].weight > 4.41)
        {
            purchase->shippingCost = weightShipping;
            break;
        }
        else
        {
            purchase->shippingCost = standardShipping;
        }
    }
    purchase->totalCost += purchase->shippingCost;
}

// Function to display the list of available products
void displayProductList(Product productList[], int size)
{
    printf("\n----------------------------------------\n");
    printf("Shopping System");
    printf("\n----------------------------------------\n");
    printf("List of available products:");
    printf("\n----------------------------------------\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d - %s - %.02f lbs - $%.2f\n", productList[i].code, productList[i].name, productList[i].weight, productList[i].price);
    }
    printf("----------------------------------------\n");
}

// Function to request the region from the user
void requestRegion(Purchase *purchase)
{
    int region;
    printf("\n----------------------------------------\n");
    printf("Select the region:");
    printf("\n----------------------------------------\n");
    printf("1 - North\n");
    printf("standard shipping: $10.00\n");
    printf("shipping per weight: $15.00");
    printf("\n----------------------------------------\n");
    printf("2 - Northeast\n");
    printf("standard shipping: $15.00\n");
    printf("shipping per weight: $20.00");
    printf("\n----------------------------------------\n");
    printf("3 - South\n");
    printf("standard shipping: $8.00\n");
    printf("shipping per weight: $12.00");
    printf("\n----------------------------------------\n");
    printf("4 - Southeast\n");
    printf("standard shipping: $5.00\n");
    printf("shipping per weight: $10.00");
    printf("\n----------------------------------------\n");
    printf("\nRegion: ");
    scanf("%d", &region);
    clearInputBuffer();
    if (region < 1 || region > 4)
    {
        clearConsole();
        printf("Invalid region. Please try again.\n");
        return requestRegion(purchase); // Calls recursively if the region is invalid
    }
    else
    {
        switch (region)
        {
        case 1:
            sprintf(purchase->regionName, "North");
            break;
        case 2:
            sprintf(purchase->regionName, "Northeast");
            break;
        case 3:
            sprintf(purchase->regionName, "South");
            break;
        case 4:
            sprintf(purchase->regionName, "Southeast");
            break;
        }
        purchase->region = region;
    }
}
// Function to request product selection from the user
void selectProducts(Purchase *purchase, Product productList[], int size)
{
    int choice;
    printf("Select the products:\n(enter the product number, -1 to finish the purchase)\n\n");
    while (1)
    {
        printf("Product (-2 to view the list): ");
        int result = scanf("%d", &choice);

        if (result == 1)
        {
            if (choice == -1)
            {
                if (purchase->quantityProducts == 0)
                {
                    printf("No products selected.\n");
                    continue;
                }
                else
                {
                    break;
                }
            }
            else if (choice == -2)
            {
                displayProductList(productList, size);
                printf("(enter the product number or -1 to finish the purchase)\n\n");
            }
            else if (choice < 1 || choice > size)
            {
                printf("Invalid product number. Please try again.\n");
            }
            else if (purchase->quantityProducts == 50)
            {
                printf("Product limit reached.\n");
                break;
            }
            else
            {
                purchase->products[purchase->quantityProducts] = productList[choice - 1];
                purchase->priceProducts += productList[choice - 1].price;
                purchase->quantityProducts++;
                purchase->totalCost += productList[choice - 1].price;
                printf("Product %s added, Cart Value: $%.02f.\n", productList[choice - 1].name, purchase->priceProducts);
            }
        }
        else
        {
            printf("Invalid product number. Please try again.\n");
        }
        clearInputBuffer();
    }
}

// Function to set the current date and time
void currentDateTime(Purchase *purchase)
{
    // Get the current date and time
    time_t currentTime;
    struct tm *currentData;
    currentTime = time(NULL);
    currentData = localtime(&currentTime);

    // Format the purchase date and time
    char buffer[80];
    strftime(buffer, 80, "%m/%d/%Y %I:%M %p", currentData);
    strcpy(purchase->purchaseDateTime, buffer);

    // Add 7 days to the current date for the estimated arrival
    currentData->tm_mday += 7;
    mktime(currentData);

    // Format the estimated arrival date
    strftime(buffer, 80, "%m/%d/%Y", currentData);
    strcpy(purchase->estimatedArrival, buffer);
}

// Function to display the purchase summary
void PurchaseSummary(Purchase *purchase)
{
    currentDateTime(purchase);
    printf("\n----------------------------------------\n");
    printf("Purchase Summary");
    printf("\n----------------------------------------\n");
    printf("Region: %s", purchase->regionName);
    printf("\n----------------------------------------\n");
    printf("Selected Products:\n\n");
    // Displays the selected products
    for (int i = 0; i < purchase->quantityProducts; i++)
    {
        printf("id:%d - %s - %.2f lbs - $%.2f\n", purchase->products[i].code, purchase->products[i].name, purchase->products[i].weight, purchase->products[i].price);
    }
    printf("----------------------------------------\n");
    printf("Product Value: $%.2f", purchase->priceProducts);
    printf("\n----------------------------------------\n");
    printf("Shipping Cost: $%.2f", purchase->shippingCost);
    printf("\nTotal Cost: $%.2f", purchase->totalCost);
    printf("\n----------------------------------------\n");
    printf("Purchase Date and Time: %s\n", purchase->purchaseDateTime);
    printf("Estimated Arrival: %s", purchase->estimatedArrival);
    printf("\n----------------------------------------\n");
}

// Ends the conditional preprocessing
#endif
