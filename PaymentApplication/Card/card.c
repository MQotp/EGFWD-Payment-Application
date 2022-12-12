#include <stdio.h>
#include <string.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) 
{
	uint8_t tempLen;
	printf("Enter Card Holder Name: ");
	gets(cardData->cardHolderName);
	tempLen = strlen(cardData->cardHolderName);
	if (tempLen >= 20 && tempLen <= 24)
	{
		return CARD_OK;
	}
	return WRONG_NAME;
}

void getCardHolderNameTest(void)
{
	uint8_t result;
	ST_cardData_t test;

	printf("Tester Name: Mahmoud Fathy Abolfadl\n");
	printf("Function Name: getCardHolderName\n");

	printf("Test Case1:\n");
	printf("input data: %s\n", "Mahmoud Fathy Abolfadl");
	printf("Expected Result: %d\n", CARD_OK);
	result = getCardHolderName(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	printf("Test Case2:\n");
	printf("input data: %s\n", "Mahmoud Fathy Kotb");
	printf("Expected Result: %d\n", WRONG_NAME);
	result = getCardHolderName(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	printf("Test Case3:\n");
	printf("input data: %s\n", "Mahmoud Fathey Abo elfadl");
	printf("Expected Result: %d\n", WRONG_NAME);
	result = getCardHolderName(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

}


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t tempLen;
	printf("Enter Card Expiry Date in the form MM/YY: ");
	gets(cardData->cardExpirationDate);
	tempLen = strlen(cardData->cardExpirationDate);
	if (tempLen != 5)
	{
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[2] != '/')
	{
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[0] < 48 || cardData->cardExpirationDate > 51)
	{
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[1] < 48 || cardData->cardExpirationDate > 57)
	{
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[3] < 48 || cardData->cardExpirationDate > 57)
	{
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[4] < 48 || cardData->cardExpirationDate > 57)
	{
		return WRONG_EXP_DATE;
	}
	return CARD_OK;
}

void getCardExpiryDateTest(void)
{
	uint8_t result;
	ST_cardData_t test;

	printf("Tester Name: Mahmoud Fathy Abolfadl\n");
	printf("Function Name: getCardExpiryDate\n");

	printf("Test Case1:\n");
	printf("input data: %s\n", "05/23");
	printf("Expected Result: %d\n", CARD_OK);
	result = getCardExpiryDate(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	printf("Test Case2:\n");
	printf("input data: %s\n", "74/56");
	printf("Expected Result: %d\n", WRONG_EXP_DATE);
	result = getCardExpiryDate(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	printf("Test Case3:\n");
	printf("input data: %s\n", "03*22");
	printf("Expected Result: %d\n", WRONG_EXP_DATE);
	result = getCardExpiryDate(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	printf("Test Case4:\n");
	printf("input data: %s\n", "y3/p2");
	printf("Expected Result: %d\n", WRONG_EXP_DATE);
	result = getCardExpiryDate(&test);
	printf("Actual result: %d\n", result);
	printf("\n");
}


EN_cardError_t getCardPAN(ST_cardData_t* cardData) /* To Accept 16 to 19 digits number. */
{
	uint8_t tempLen, i;
	printf("Enter Card PAN: ");
	gets(cardData->primaryAccountNumber);
	tempLen = strlen(cardData->cardExpirationDate);
	if (tempLen > 19 || tempLen < 16)
	{
		return WRONG_PAN;
	}
	for (i = 0; i < 20; i++)
	{
		/*if the character is not a digit or null, return WRONG_PAN.*/
		if ((cardData->cardExpirationDate[i] != '\0') || (cardData->cardExpirationDate[i] < 48) || (cardData->cardExpirationDate[i] > 57))
		{
			return WRONG_PAN;
		}
	}
	return CARD_OK;
}

void getCardPANTest(void)
{
	uint8_t result;
	ST_cardData_t test;

	printf("Tester Name: Mahmoud Fathy Abolfadl\n");
	printf("Function Name: getCardPAN\n");

	printf("Test Case1:\n");
	printf("input data: %s\n", "12345678911131517");
	printf("Expected Result: %d\n", CARD_OK);
	result = getCardPAN(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	printf("Test Case2:\n");
	printf("input data: %s\n", "12345678911131517190");
	printf("Expected Result: %d\n", WRONG_PAN);
	result = getCardPAN(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	printf("Test Case3:\n");
	printf("input data: %s\n", "1234567891113");
	printf("Expected Result: %d\n", WRONG_PAN);
	result = getCardPAN(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	printf("Test Case4:\n");
	printf("input data: %s\n", "123456789111315/*-");
	printf("Expected Result: %d\n", WRONG_PAN);
	result = getCardPAN(&test);
	printf("Actual result: %d\n", result);
	printf("\n");
}