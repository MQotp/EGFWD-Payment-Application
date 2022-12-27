/* #pragma once - Equivalent to the implemented file guard. */
#ifndef CARD_H_
#define CARD_H_

#define uint8_t unsigned char

/*                  Types Declarations                  */
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;


/*
 * [Function Name]: getCardHolderName
 * [Function Description]: This Function should save the name of the card in a ST_cardData_t structure.
 *
 * Inputs: Pointer to ST_cardData_t structure.
 * Outputs: EN_cardError_t enum value represents the status of the name if it is okay or is it wrong.
*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);

/*
 * [Function Name]: getCardExpiryDate
 * [Function Description]: This Function should save the expiration date of the card in a ST_cardData_t structure.
 *
 * Inputs: Pointer to ST_cardData_t structure.
 * Outputs: EN_cardError_t enum value represents the status of the name if it is okay or is it wrong.
*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);

/*
 * [Function Name]: getCardPAN
 * [Function Description]: This Function should save the PAN of the card in a ST_cardData_t structure.
 *
 * Inputs: Pointer to ST_cardData_t structure.
 * Outputs: EN_cardError_t enum value represents the status of the name if it is okay or is it wrong.
*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

/*
 * [Function Name]: getCardHolderNameTest
 * [Function Description]: This Function should test getCardHolderName function.
 *
 * Inputs: No inputs.
 * Outputs: No outputs.
*/
void getCardHolderNameTest(void);

/*
 * [Function Name]: getCardExpiryDateTest
 * [Function Description]: This Function should test getCardExpiryDate function.
 *
 * Inputs: No inputs.
 * Outputs: No outputs.
*/
void getCardExpiryDateTest(void);

/*
 * [Function Name]: getCardPANTest
 * [Function Description]: This Function should test getCardPAN function.
 *
 * Inputs: No inputs.
 * Outputs: No outputs.
*/
void getCardPANTest(void);


#endif /* CARD_H_ */