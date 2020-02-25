#pragma warning(disable : 4996)

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void getString(char prompt[], char* variable);
void getName(char* name);
void getAddress(char* address);
void getCreditCard(char* creditCard);
void printReceipt(char* name, char* address, char* selectedItem, int amount, char* creditCard);
int userWantsToReplay();
void getStringWithCondition(char prompt[], char* variable, int minLength, int maxLength);
int getInt(char prompt[]);
int getIntWithCondition(char prompt[], int min, int max);
void toLowerCase(char str[]);
int strcmpCaseInsensitive(char* str1, char* str2);

int main() {

	while (1) {

		char name[256];
		char address[256];
		char selectedItem[256];
		char creditCard[256];
		char* items[] = { "Powder", "Eye shadow", "Lip gloss", "Mascara", "Eye liner" };
		int length = sizeof(items) / sizeof(items[0]);

		getName(name);
		getAddress(address);
		
		/* Print items */
		puts("Store items:");
		for (int i = 0; i < length; i++) {
			int order = i + 1;
			printf("%d. %s\n", order, items[i]);
		}

		/* Get selected item */
		int inputtedItemIsValid = 0;
		while (!inputtedItemIsValid) {

			getString("Selected item name [Case insensitive]: ", selectedItem);

			for (int i = 0; i < length; i++) {
				char* item = items[i];

				if (strcmpCaseInsensitive(selectedItem, item) == 0) {
					inputtedItemIsValid = 1;
					break;
				}
			}

		}

		int amount = getIntWithCondition("Amount [1-100]: ", 1, 100);
		getCreditCard(creditCard);
		printReceipt(name, address, selectedItem, amount, creditCard);

		if (!userWantsToReplay()) {
			break;
		}

	}
}

int userWantsToReplay() {
	printf("Again? (Y/N): ");
	char input = getchar();

	char dump[256];
	scanf("%[^\n]", dump);
	getchar();

	return tolower(input) == 'y';
}

void printReceipt(char* name, char* address, char* selectedItem, int amount, char* creditCard) {
	puts("");
	puts("Receipt");
	puts("=======");
	printf("Name: %s\n", name);
	printf("Address: %s\n", address);
	printf("Ordered item: %s (QTY: %d)\n", selectedItem, amount);
	printf("Credit Card: %s\n", creditCard);
	puts("");
}

void getCreditCard(char* creditCard) {
	while (1) {

		int isCreditCard = 1;

		getString("Credit Card Number [14 digits]: ", creditCard, 14, 14);
		for (int i = 0; i < strlen(creditCard); i++) {
			isCreditCard = isCreditCard && isdigit(creditCard[i]);
		}

		isCreditCard = isCreditCard && strlen(creditCard) == 14;

		if (isCreditCard) {
			break;
		}

	}
}

void getAddress(char* address) {
	while (1) {

		getStringWithCondition("Address [1-50 characters & contains \"Street\"]: ", address, 1, 50);

		if (strstr(address, "Street")) {
			break;
		}

	}
}

void getName(char* name) {
	getStringWithCondition("Name [1-20 characters]: ", name, 1, 20);
}

void getString(char prompt[], char* variable) {
	printf("%s", prompt);
	scanf("%[^\n]", variable);
	getchar();
}

void getStringWithCondition(char prompt[], char* variable, int minLength, int maxLength) {

	while (1) {
		getString(prompt, variable);
		int length = strlen(variable);

		if (length >= minLength && length <= maxLength) {
			break;
		}
	}

}

int getInt(char prompt[]) {
	int input;

	printf("%s", prompt);
	scanf("%d", &input);
	getchar();

	return input;
}

int getIntWithCondition(char prompt[], int min, int max) {

	while (1) {
		int input = getInt(prompt);

		if (input >= min && input <= max) {
			return input;
		}
	}

}

void toLowerCase(char str[]) {
	for (int i = 0; str[i]; i++) {
		str[i] = tolower(str[i]);
	}
}

int strcmpCaseInsensitive(char* str1, char* str2) {
	char copy1[256];
	char copy2[256];

	strcpy(copy1, str1);
	strcpy(copy2, str2);

	toLowerCase(copy1);
	toLowerCase(copy2);

	return strcmp(copy1, copy2);
}
