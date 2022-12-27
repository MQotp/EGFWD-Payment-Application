/* #pragma once - Equivalent to the implemented file guard. */
#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "../Card/card.h"

/*                  Types Declarations                  */
typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

/*
 * [Function Name]: getTransactionDate
 * [Function Description]: This Function should get the transaction date and save it in a ST_terminalData_t structure.
 *
 * Inputs: Pointer to ST_terminalData_t structure.
 * Outputs: EN_terminalError_t enum value represents the status of the date format if it is okay or is it wrong.
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);

/*
 * [Function Name]: getTransactionDateTest
 * [Function Description]: This Function should test getTransactionDateTest.
 *
 * Inputs: No inputs.
 * Outputs: No outputs.
*/
void getTransactionDateTest(void);

/*
 * [Function Name]: isCardExpired
 * [Function Description]: This Function should check whether the card is expired or not.
 *
 * Inputs: Pointer to ST_terminalData_t structure and Pointer to ST_cardData_t structure.
 * Outputs: EN_terminalError_t enum value shows that the card is expired or not.
*/
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);

/*
 * [Function Name]: isCardExpriedTest
 * [Function Description]: This Function should test isCardExpired.
 *
 * Inputs: No inputs.
 * Outputs: No outputs.
*/
void isCardExpiredTest(void);

/*
 * [Function Name]: getTransactionAmount
 * [Function Description]: This Function should gets the required transaction amount and store it in ST_terminalData_t structure.
 *
 * Inputs: Pointer to ST_terminalData_t structure.
 * Outputs: EN_terminalError_t enum value shows that the amount is valid or not.
*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);

/*
 * [Function Name]: getTransactionAmountTest
 * [Function Description]: This Function should test getTransactionAmount.
 *
 * Inputs: No inputs.
 * Outputs: No outputs.
*/
void getTransactionAmountTest(void);

/*
 * [Function Name]: isBelowMaxAmount
 * [Function Description]: This Function checks whether the transaction amount is below the maximum amount or not.
 *
 * Inputs: Pointer to ST_terminalData_t structure.
 * Outputs: EN_terminalError_t enum value shows that the the transaction amount exceeded the maximum acount or not.
*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);

/*
 * [Function Name]: isBelowMaxAmountTest
 * [Function Description]: This Function should test isBelowMaxAmount.
 *
 * Inputs: No inputs.
 * Outputs: No outputs.
*/
void isBelowMaxAmountTest(void);

/*
 * [Function Name]: setMaxAmount
 * [Function Description]: This Function sets the maximum amount that can be withdrawn from the terminal in one time.
 *
 * Inputs: Pointer to ST_terminalData_t structure, and float value represents the maximum amount.
 * Outputs: EN_terminalError_t enum value shows that the the maximum amount is valid or not.
*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);

/*
 * [Function Name]: setMaxAmountTest
 * [Function Description]: This Function should test setMaxAmount.
 *
 * Inputs: No inputs.
 * Outputs: No outputs.
*/
void setMaxAmountTest(void);

#endif /* TERMINAL_H_ */
