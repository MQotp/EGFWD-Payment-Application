#include "app.h"


/***					Global Variables					***/

ST_cardData_t card;
ST_terminalData_t terminal;

ST_transaction_t transactionData;
//ST_accountsDB_t* accountReference = NULL;

/***					Functions Definitions					***/
void appStart(void)
{
	/*Get card holder name*/
	/*getCardHolderName returns 1 in case of wrong name, and 0 in case of correct name.*/
	if (!getCardHolderName(&card))
	{
		/*Get card expiration date*/
		/*getCardExpiryDate returns 2 in case of wrong name, and 0 in case of correct name.*/
		if (!getCardExpiryDate(&card))
		{
			/*Get card PAN */
			/*getCardPAN returns 3 in case of wrong name, and 0 in case of correct name.*/
			if (!getCardPAN(&card))
			{
				/*Card data is all set by here.*/
				/*Set the maximum Amount to 4K*/
				if (!setMaxAmount(&terminal, MAXIMUM_AMOUNT))
				{
					/*Get Transaction Date*/
					if (!getTransactionDate(&terminal))
					{
						/*Check whether the card is expired or not.*/
						if (!isCardExpired(&card, &terminal))
						{
							/*If the card is not expired, get the transaction amount.*/
							if (!getTransactionAmount(&terminal))
							{
								/*Check if the transaction amount is less than the MAXIMUM_AMOUNT set.*/
								if (!isBelowMaxAmount(&terminal))
								{
									/*if the amount is below the maximum, go to the server*/
									/*Receive and Save All Transaction Data*/
									transactionData.cardHolderData = card;
									transactionData.terminalData = terminal;
									recieveTransactionData(&transactionData);
								}
							}
						}
					}
				}
			}
		}
	}

}


