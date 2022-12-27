#include "server.h"

ST_accountsDB_t Account[255] = { {2000.0, RUNNING, "8989374615436851"},\
		{100000.0, BLOCKED, "5807007076043875"},\
		{125000.0, RUNNING, "1501597076060875"},\
		{1550.0, BLOCKED, "4701999976060875"},\
		{500000.0, RUNNING, "1231589476394775"},\
		{152250.0, RUNNING, "4404747976060825"},\
		{23000.0, RUNNING, "2304123472456873"},\
		{22440.0, BLOCKED, "2214123987456846"},\
		{23000.0, RUNNING, "2304123472452587"},\
		{98000.0, BLOCKED, "2989123472451479"},\
		{47200.0, RUNNING, "1401424747456875"} };


uint32_t transactionProceed = 0;
ST_transaction_t Transaction[255] = { 0 };

ST_accountsDB_t* accountReference = NULL;

/* typedef struct ST_transaction_t
{
	 ST_cardData_t cardHolderData;
	 ST_terminalData_t terminalData;
	 EN_transStat_t transState;
	 uint32_t transactionSequenceNumber;
}ST_transaction_t; */

EN_transStat_t recieveTransactionData(ST_transaction_t* transData)
{
	if (isValidAccount(&transData->cardHolderData, &accountReference)) /*if Account Not Found*/
	{
		transData->transState = FRAUD_CARD;
		printf("Fraud card.\n");
		return FRAUD_CARD;
	}
	if (isBlockedAccount(&accountReference)) /*Case of Blocked Account*/
	{
		transData->transState = DECLINED_STOLEN_CARD;
		printf("Declined. Blocked account.\n");
		return DECLINED_STOLEN_CARD;
	}

	if (isAmountAvailable(&transData->terminalData, &accountReference)) /*case of Low Balance*/
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		printf("Declined. Insufficient fund.\n");
		return DECLINED_INSUFFECIENT_FUND;
	}

	transData->transState = APPROVED;
	accountReference->balance -= transData->terminalData.transAmount;

	if (saveTransaction(transData)) /*Case of Saving Failed*/
	{
		transData->transState = INTERNAL_SERVER_ERROR;
		printf("Internal server error.\n");
		return INTERNAL_SERVER_ERROR;
	}
	/*By here, Account Validation is done, Amount validation is done, and the transaction had been saved.*/
	/*Update account balance..*/
	/*Set the transaction state*/
	return APPROVED;
}

void recieveTransactionDataTest(void)
{
	uint8_t result;
	ST_cardData_t cardTest = { "Mahmoud Fathy Abolfadl","1501597076060875","05/23"},\
		cardTest2 = { "Mahmoud Fathy Abolfadl","1501597015970875","05/23" },\
		cardTest3 = { "Mahmoud Fathy Abolfadl","8989374615436851","05/23" },\
		cardTest4 = { "Mahmoud Fathy Abolfadl","2989123472451479","05/23" };
	ST_terminalData_t terminalTest = {3000,4000,"11/11/2022"};
	ST_transaction_t test;
	test.cardHolderData = cardTest;
	test.terminalData = terminalTest;

	/*APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR*/
	printf("Tester Name: Mahmoud Fathy Abolfadl\n");
	printf("Function Name: recieveTransactionData\n");

	/*Approved Case*/
	printf("Test Case1:\n");
	printf("input data: %s\n", "Card: Mahmoud Fathy Abolfadl - 1501597076060875 - 05/23\n");
	printf("\t \t%s\n", "Terminal: 3000 - 4000 - 11/11/2022\n");
	printf("Expected Result: %d\n", APPROVED);
	result = recieveTransactionData(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	/*Declined due to insuffecient fund - Amount is not available Case*/
	test.cardHolderData = cardTest3;
	printf("Test Case2:\n");
	printf("input data: %s\n", "05/23");
	printf("Expected Result: %d\n", DECLINED_INSUFFECIENT_FUND);
	result = recieveTransactionData(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	/*Stolen Card - Blocked Account Case*/
	test.cardHolderData = cardTest4;
	printf("Test Case3:\n");
	printf("input data: %s\n", "05/23");
	printf("Expected Result: %d\n", DECLINED_STOLEN_CARD);
	result = recieveTransactionData(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	/*Fraud Card - Not valid Card Case*/
	test.cardHolderData = cardTest2;
	printf("Test Case4:\n");
	printf("input data: %s\n", "05/23");
	printf("Expected Result: %d\n", FRAUD_CARD);
	result = recieveTransactionData(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	/*Server Error - Can't save the transaction Case*/
	transactionProceed = 300; /*Invalid number to transaction*/
	test.cardHolderData = cardTest;
	printf("Test Case5:\n");
	printf("input data: %s\n", "05/23");
	printf("Expected Result: %d\n", INTERNAL_SERVER_ERROR);
	result = recieveTransactionData(&test);
	printf("Actual result: %d\n", result);
	printf("\n");
}


EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t** accountRefrence)
{
	uint8_t i;
	for (i = 0; i < 255; i++)
	{
		if (strcmp(cardData->primaryAccountNumber, Account[i].primaryAccountNumber) == 0)
		{
			*accountRefrence = &Account[i];
			return SERVER_OK;
		}
	}
	*accountRefrence = NULL;
	return ACCOUNT_NOT_FOUND;
}

void isValidAccountTest(void)
{
	ST_cardData_t test = { "","8989374615436851",""}; /*Valid PAN*/
	ST_cardData_t test2 = { "" ,"8989334666636851", ""}; /*inValid PAN*/
	ST_accountsDB_t* testAccount = NULL; /*Assigning Valid PAN*/
	uint8_t result;
	printf("Tester Name: Mahmoud Fathy Abolfadl\n");
	printf("Function Name: isValidAccount\n");
	printf("Test Case1:\n");
	printf("input data: %s\n", "8989374615436851");
	printf("Expected Result: %d\n", SERVER_OK);
	result = isValidAccount(&test, &testAccount);
	printf("Actual result: %d\n", result);
	printf("\n");

	testAccount = NULL;
	printf("Test Case2:\n");
	printf("input data: %s\n", "8989334666636851");
	printf("Expected Result: %d\n", ACCOUNT_NOT_FOUND);
	result = isValidAccount(&test2, &testAccount);
	printf("Actual result: %d\n", result);
	printf("\n");
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t** accountRefrence)
{
	uint8_t i;
	for (i = 0; i < 255; i++)
	{
		if ((*accountRefrence)->state == RUNNING)
		{
			return SERVER_OK;
		}
	}
	return BLOCKED_ACCOUNT;
}

void isBlockedAccountTest(void)
{
	ST_accountsDB_t* testAccount = &Account[0]; /*running account*/
	uint8_t result;
	printf("Tester Name: Mahmoud Fathy Abolfadl\n");
	printf("Function Name: isBlockedAccount\n");

	printf("Test Case1:\n");
	printf("input data: %s\n", "2000.0, RUNNING, 8989374615436851");
	printf("Expected Result: %d\n", SERVER_OK);
	result = isBlockedAccount(&testAccount);
	printf("Actual result: %d\n", result);
	printf("\n");

	testAccount = &Account[1]; /*Blocked Account*/
	printf("Test Case2:\n");
	printf("input data: %s\n", "100000.0, BLOCKED, 5807007076043875");
	printf("Expected Result: %d\n", BLOCKED_ACCOUNT);
	result = isBlockedAccount(&testAccount);
	printf("Actual result: %d\n", result);
	printf("\n");
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t** accountRefrence)
{
	if (termData->transAmount > (*accountRefrence)->balance)
	{
		return LOW_BALANCE;
	}
	return SERVER_OK;
}

void isAmountAvailableTest(void)
{
	uint8_t result;
	ST_terminalData_t test = {3000,4000,0};
	ST_accountsDB_t* testAccount = &Account[4]; /*500k Available Amount !0.0!*/
	printf("Tester Name: Mahmoud Fathy Abolfadl\n");
	printf("Function Name: isAmountAvailable\n");

	printf("Test Case1:\n");
	printf("input data: %s\n", "500k Balance Acocunt, 3k Transaction Amount");
	printf("Expected Result: %d\n", SERVER_OK);
	result = isAmountAvailable(&test, &testAccount);
	printf("Actual result: %d\n", result);
	printf("\n");

	testAccount = &Account[0];
	printf("Test Case2:\n");
	printf("input data: %s\n", "2k Balance Account, 3k Transaction Amount");
	printf("Expected Result: %d\n", LOW_BALANCE);
	result = isAmountAvailable(&test, &testAccount);
	printf("Actual result: %d\n", result);
	printf("\n");
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	transactionProceed++;
	if (transactionProceed < 255)
	{
		transData->transactionSequenceNumber = transactionProceed;
		Transaction[transactionProceed] = *transData;
		listSavedTransactions();
		return SERVER_OK;
	}
	printf("Saving failed.\n");
	return SAVING_FAILED;
}

void saveTransactionTest(void)
{
	uint8_t result;
	ST_transaction_t test = {0,0,0,0};
	printf("Tester Name: Mahmoud Fathy Abolfadl\n");
	printf("Function Name: saveTransaction (without listSavedTransaction Part)\n");
	transactionProceed = 200; /*Valid saving case.*/
	printf("Test Case1:\n");
	printf("input data: %s\n", "transactionProceed = 200");
	printf("Expected Result: %d\n", SERVER_OK);
	result = saveTransaction(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	transactionProceed = 300; /*Saving Failed due to exceed the number of possible transactions.*/
	printf("Test Case2:\n");
	printf("input data: %s\n", "transactionProceed = 300");
	printf("Expected Result: %d\n", SAVING_FAILED);
	result = saveTransaction(&test);
	printf("Actual result: %d\n", result);
	printf("\n");

	transactionProceed = 0;
}

void listSavedTransactions(void)
{
	printf("\n#########################\n");
	printf("Transaction Sequence Number : %d\n", Transaction[transactionProceed].transactionSequenceNumber); /*for better UI.*/
	printf("Transaction Date : %s\n", Transaction[transactionProceed].terminalData.transactionDate);
	printf("Transaction Amount: %f\n", Transaction[transactionProceed].terminalData.transAmount);
	switch (Transaction[transactionProceed].transState)
	{
	case DECLINED_INSUFFECIENT_FUND:
		printf("Transaction State : DECLINED INSUFFECIENT FUND. \n");
		break;
	case DECLINED_STOLEN_CARD:
		printf("Transaction State: DECLINED STOLEN CARD. \n");
		break;
	case FRAUD_CARD:
		printf("Transaction State: FRAUD CARD. \n");
		break;
	case INTERNAL_SERVER_ERROR:
		printf("Transaction State: INTERNAL SERVER ERROR. \n");
		break;
	default:
		printf("Transaction State: APPROVED. \n");
	}
	printf("Terminal Max Amount: %f\n", Transaction[transactionProceed].terminalData.maxTransAmount);
	printf("Cardholder Name: %s\n", Transaction[transactionProceed].cardHolderData.cardHolderName);
	printf("The remaining Balance: %f\n", accountReference->balance);
	printf("PAN: %s\n", Transaction[transactionProceed].cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date: %s\n", Transaction[transactionProceed].cardHolderData.cardExpirationDate);
	printf("#########################\n\n");
}
