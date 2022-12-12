#include <stdio.h>
#include "server.h"

ST_accountsDB_t Account[255] = {{2000.0, RUNNING, "8989374615436851"},\
		{100000.0, BLOCKED, "5807007076043875"},\
		{125000.0, RUNNING, "1501597076060875"},\
		{1550.0, BLOCKED, "4701999976060875"},\
		{500000.0, RUNNING, "1231589476394775"},\
		{152250.0, RUNNING, "4404747976060825"},\
		{23000.0, RUNNING, "2304123472456873"},\
		{22440.0, BLOCKED, "2214123987456846"},\
		{23000.0, RUNNING, "2304123472452587"},\
		{98000.0, BLOCKED, "2989123472451479"},\
		{47200.0, RUNNING, "1401424747456875"}};

ST_transaction_t Transaction[255] = {0};

/* typedef struct ST_transaction_t
{
     ST_cardData_t cardHolderData;
     ST_terminalData_t terminalData;
     EN_transStat_t transState;
     uint32_t transactionSequenceNumber;
}ST_transaction_t; */

EN_transStat_t recieveTransactionData(ST_transaction_t *transData)
{

}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
	uint8_t i;
	for(i = 0; i < 255; i++)
	{

	}
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{

}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{

}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{

}

void listSavedTransactions(void)
{

}
