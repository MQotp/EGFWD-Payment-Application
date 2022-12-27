#include <stdio.h>
#include <string.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t tempLen, i;
	printf("Enter Card Holder Name: ");
	gets(cardData->cardHolderName);
	tempLen = strlen(cardData->cardHolderName);
	if (tempLen >= 20 && tempLen <= 24)
	{
		return CARD_OK;
	}
	else if (tempLen < 2)
	{
		gets(cardData->cardHolderName);
		tempLen = strlen(cardData->cardHolderName);
		if (tempLen >= 20 && tempLen <= 24)
		{
			return CARD_OK;
		}
	}
	printf("Wrong name format\n");
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
	printf("input data: %s\n", "Mahmoud Fathy Kotb"); /*Less than 20 characters*/
	printf("Expected Result: %d\n", WRONG_NAME);
	result = getCardHolderName(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	printf("Test Case3:\n");
	printf("input data: %s\n", "Mahmoud Fathey Abo elfadl"); /*More than 24 characters -> accessing forbidden memory*/
	printf("Expected Result: %d\n", WRONG_NAME);
	result = getCardHolderName(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

}


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t tempLen;
	printf("Enter Card Expiration Date in the form MM/YY: ");
	gets(cardData->cardExpirationDate);
	tempLen = strlen(cardData->cardExpirationDate);
	if (tempLen != 5)
	{
		printf("Wrong expiration date format\n");
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[2] != '/')
	{
		printf("Wrong expiration date format\n");
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[0] < '0' || cardData->cardExpirationDate[0] > '1')
	{
		printf("Wrong expiration date format\n");
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[1] < '0' || cardData->cardExpirationDate[1] > '9')
	{
		printf("Wrong expiration date format\n");
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[0] == '1' && cardData->cardExpirationDate[1] > '2')
	{
		printf("Wrong expiration date format\n");
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[3] < '0' || cardData->cardExpirationDate[3] > '9')
	{
		printf("Wrong expiration date format\n");
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[4] < '0' || cardData->cardExpirationDate[4] > '9')
	{
		printf("Wrong expiration date format\n");
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
	uint8_t tempLen, i = 0;
	printf("Enter Card PAN: ");
	gets(cardData->primaryAccountNumber);
	tempLen = strlen(cardData->primaryAccountNumber);
	if (tempLen > 19 || tempLen < 16)
	{
		printf("Wrong PAN format\n");
		return WRONG_PAN;
	}
	while (cardData->primaryAccountNumber[i] != NULL)
	{
		if (cardData->primaryAccountNumber[i] > '9' || cardData->primaryAccountNumber[i] < '0')
		{
			printf("Wrong PAN format\n");
			return WRONG_PAN;
		}
		i++;
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
