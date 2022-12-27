#include <stdio.h>
#include <string.h>
#include "terminal.h"
#include "../Card/card.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    uint8_t tempLen;
    printf("Enter Transaction Date in the form DD/MM/YYYY: ");
    gets(termData->transactionDate);
    tempLen = strlen(termData->transactionDate);
    if (tempLen != 10)
    {
        printf("Wrong date format.\n");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[2] != '/') || (termData->transactionDate[5] != '/'))
    {
        printf("Wrong date format.\n");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[0] < '0') || (termData->transactionDate[0] > '3'))
    {
        printf("Wrong date format.\n");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[1] < '0') || (termData->transactionDate[1] > '9'))
    {
        printf("Wrong date format.\n");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[0] == '3') && (termData->transactionDate[1] > '1'))
    {
        printf("Wrong date format.\n");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[3] < '0') || (termData->transactionDate[3] > '1')) /*12 months*/
    {
        printf("Wrong date format.\n");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[4] < '0') || (termData->transactionDate[4] > '9'))
    {
        printf("Wrong date format.\n");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[3] == '1') && (termData->transactionDate[4] > '2'))
    {
        printf("Wrong date format.\n");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[6] < '0') || (termData->transactionDate[6] > '9'))
    {
        printf("Wrong date format.\n");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[7] < '0') || (termData->transactionDate[7] > '9'))
    {
        printf("Wrong date format.\n");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[8] < '0') || (termData->transactionDate[8] > '9'))
    {
        printf("Wrong date format.\n");
        return WRONG_DATE;
    }
    else if ((termData->transactionDate[9] < '0') || (termData->transactionDate[9] > '9'))
    {
        printf("Wrong date format.\n");
        return WRONG_DATE;
    }
    return TERMINAL_OK;
}

void getTransactionDateTest(void)
{

    uint8_t result;
    ST_terminalData_t test;

    printf("Tester Name: Mahmoud Fathy Abolfadl\n");
    printf("Function Name: getTransactionDate\n");

    printf("Test Case1:\n");
    printf("input data: %s\n", "05/12/2022");
    printf("Expected Result: %d\n", TERMINAL_OK);
    result = getTransactionDate(&test);
    printf("Actual result: %d\n", result);
    printf("\n");

    printf("Test Case2:\n");
    printf("input data: %s\n", "74/56");
    printf("Expected Result: %d\n", WRONG_DATE);
    result = getTransactionDate(&test);
    printf("Actual result: %d\n", result);
    printf("\n");

    printf("Test Case3:\n");
    printf("input data: %s\n", "44879/2019");
    printf("Expected Result: %d\n", WRONG_DATE);
    result = getTransactionDate(&test);
    printf("Actual result: %d\n", result);
    printf("\n");

    printf("Test Case4:\n");
    printf("input data: %s\n", "4487902019");
    printf("Expected Result: %d\n", WRONG_DATE);
    result = getTransactionDate(&test);
    printf("Actual result: %d\n", result);
    printf("\n");

    printf("Test Case5:\n");
    printf("input data: %s\n", "42/s9/2019");
    printf("Expected Result: %d\n", WRONG_DATE);
    result = getTransactionDate(&test);
    printf("Actual result: %d\n", result);
    printf("\n");
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
    /* card date format mm/yy, terminal date format dd/mm/yyyy*/
    // if the first string is less than the second string return negative
    uint8_t tempCardMonth[3], tempTermMonth[3], tempCardYear[3], tempTermYear[3];
    tempCardMonth[0] = cardData->cardExpirationDate[0];
    tempCardMonth[1] = cardData->cardExpirationDate[1];
    tempCardMonth[2] = '\0';

    tempCardYear[0] = cardData->cardExpirationDate[3];
    tempCardYear[1] = cardData->cardExpirationDate[4];
    tempCardYear[2] = '\0';

    tempTermMonth[0] = termData->transactionDate[3];
    tempTermMonth[1] = termData->transactionDate[4];
    tempTermMonth[2] = '\0';

    tempTermYear[0] = termData->transactionDate[8];
    tempTermYear[1] = termData->transactionDate[9];
    tempTermYear[2] = '\0';

    if (strcmp(tempCardYear, tempTermYear) < 0) /* Card Year is less than terminal year*/
    {
        printf("Expired card.\n");
        return EXPIRED_CARD;
    }
    else if (strcmp(tempCardYear, tempTermYear) == 0)
    {
        if (strcmp(tempCardMonth, tempTermMonth) < 0) /* Check if the card month is less than terminal month in the same year.*/
        {
            printf("Expired card.\n");
            return EXPIRED_CARD;
        }
    }
    return TERMINAL_OK;
}

void isCardExpiredTest(void)
{

    EN_terminalError_t result;
    ST_cardData_t cardTest = { "Dummy Name","Dummy PAN","05/22" };

    ST_terminalData_t termTest1 = { 1234,1234,"13/11/2020" }, \
        termTest2 = { 1234,1234,"13/11/2022" }, \
        termTest3 = { 1234,1234,"13/05/2022" }, \
        termTest4 = { 1234,1234,"13/05/2023" };

    printf("Tester Name: Mahmoud Fathy Abolfadl\n");
    printf("Function Name: isCardExpried\n");

    printf("Test Case1:\n");
    printf("input data: %s\n", "Card date: 05/22, Terminal date: 13/11/2020");
    printf("Expected Result: %d\n", TERMINAL_OK);
    result = isCardExpired(&cardTest, &termTest1);
    printf("Actual result: %d\n", result);
    printf("\n");

    printf("Test Case2:\n");
    printf("input data: %s\n", "Card date: 05/22, Terminal date: 13/11/2022");
    printf("Expected Result: %d\n", EXPIRED_CARD);
    result = isCardExpired(&cardTest, &termTest2);
    printf("Actual result: %d\n", result);
    printf("\n");

    printf("Test Case3:\n");
    printf("input data: %s\n", "Card date: 05/22, Terminal date: 13/05/2022");
    printf("Expected Result: %d\n", TERMINAL_OK);
    result = isCardExpired(&cardTest, &termTest3);
    printf("Actual result: %d\n", result);
    printf("\n");

    printf("Test Case4:\n");
    printf("input data: %s\n", "Card date: 05/22, Terminal date: 13/05/2023");
    printf("Expected Result: %d\n", EXPIRED_CARD);
    result = isCardExpired(&cardTest, &termTest4);
    printf("Actual result: %d\n", result);
    printf("\n");
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    printf("Enter the Transaction Amount: ");
    scanf_s(" %f", &termData->transAmount);

    if (termData->transAmount <= 0)
    {
        printf("Invalid amount.\n");
        return INVALID_AMOUNT;
    }
    return TERMINAL_OK;
}

void getTransactionAmountTest(void)
{
    EN_terminalError_t result;
    ST_terminalData_t termTest;
    printf("Tester Name: Mahmoud Fathy Abolfadl\n");
    printf("Function Name: getTransactionAmount\n");

    printf("Test Case1:\n");
    printf("input data: %s\n", "520");
    printf("Expected Result: %d\n", TERMINAL_OK);
    result = getTransactionAmount(&termTest);
    printf("Actual result: %d\n", result);
    printf("\n");

    printf("Test Case2:\n");
    printf("input data: %s\n", "-200");
    printf("Expected Result: %d\n", INVALID_AMOUNT);
    result = getTransactionAmount(&termTest);
    printf("Actual result: %d\n", result);
    printf("\n");

    printf("Test Case3:\n");
    printf("input data: %s\n", "0");
    printf("Expected Result: %d\n", INVALID_AMOUNT);
    result = getTransactionAmount(&termTest);
    printf("Actual result: %d\n", result);
    printf("\n");
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    if (termData->transAmount > termData->maxTransAmount)
    {
        printf("Exceed maximum amount.\n");
        return EXCEED_MAX_AMOUNT;
    }
    return TERMINAL_OK;
}

void isBelowMaxAmountTest(void)
{
    EN_terminalError_t result;
    ST_terminalData_t termTest = { 123, 200, "22/22/2222" };
    printf("Tester Name: Mahmoud Fathy Abolfadl\n");
    printf("Function Name: isBelowMaxAmount\n");

    printf("Test Case1:\n");
    printf("input data: %s\n", "transAmount = 123, maxTransAmount = 200");
    printf("Expected Result: %d\n", TERMINAL_OK);
    result = isBelowMaxAmount(&termTest);
    printf("Actual result: %d\n", result);
    printf("\n");

    termTest.transAmount = 300;
    printf("Test Case2:\n");
    printf("input data: %s\n", "transAmount = 300, maxTransAmount = 200");
    printf("Expected Result: %d\n", EXCEED_MAX_AMOUNT);
    result = isBelowMaxAmount(&termTest);
    printf("Actual result: %d\n", result);
    printf("\n");
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
    if (maxAmount <= 0)
    {
        printf("Invalid maximum amount.\n");
        return INVALID_MAX_AMOUNT;
    }
    termData->maxTransAmount = maxAmount;
    return TERMINAL_OK;
}

void setMaxAmountTest(void)
{
    EN_terminalError_t result;
    ST_terminalData_t termTest;
    printf("Tester Name: Mahmoud Fathy Abolfadl\n");
    printf("Function Name: setMaxAmount\n");

    printf("Test Case1:\n");
    printf("input data: %s\n", "maxAmount = 300");
    printf("Expected Result: %d\n", TERMINAL_OK);
    result = setMaxAmount(&termTest, 300);
    printf("Actual result: %d\n", result);
    printf("\n");

    printf("Test Case2:\n");
    printf("input data: %s\n", "maxAmount = 0");
    printf("Expected Result: %d\n", INVALID_MAX_AMOUNT);
    result = setMaxAmount(&termTest, 0);
    printf("Actual result: %d\n", result);
    printf("\n");

    printf("Test Case2:\n");
    printf("input data: %s\n", "maxAmount = -200");
    printf("Expected Result: %d\n", INVALID_MAX_AMOUNT);
    result = setMaxAmount(&termTest, -200);
    printf("Actual result: %d\n", result);
    printf("\n");
}
