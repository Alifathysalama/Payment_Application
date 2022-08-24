#include "server.h"

/*
This function will take card data and validate these data.
It checks if the PAN exists or not in the server's database.
If the PAN doesn't exist will return DECLINED_STOLEN_CARD, else will return OK
*/

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{	//iterate for the whole array to check if available of not  
	for (int i = 0; i < 4; i++)
	{	
		if (strcmp(cardData->primaryAccountNumber,accountsDB[i].primaryAccountNumber)==0)
		{	//the index will be used to check the information of the customer if foun in DataBase.
			index_of_customer = i;
			return ALRIGHT;
		}
	}
	return DECLINED_STOLEN_CARD;
}
/*
This function will take terminal data and validate these data.
It checks if the transaction's amount is available or not.
If the transaction amount is greater than the balance in the database will return LOW_BALANCE, else will return OK
*/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (termData->transAmount > accountsDB[index_of_customer].balance)
		return LOW_BALANCE;
	return ALRIGHT;
}
/*
This function will take all transaction data into the transactions database.
It gives a sequence number to a transaction, this number is incremented once a transaction is processed into the server.
If saves any type of transaction, APPROVED or DECLINED, with the specific reason for declining/transaction state.
If transaction can't be saved will return SAVING_FAILED, else will return OK
*/
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	
			transaction[index_of_customer].transactionSequenceNumber = sequnce_start_number;
			sequnce_start_number++;
			transaction[index_of_customer].cardHolderData = transData->cardHolderData;
			transaction[index_of_customer].terminalData = transData->terminalData;
			transaction[index_of_customer].transState = APPROVED;
			return APPROVED;
}
/*

This function will take a transaction sequence number and search for this transaction in the database.
If the transaction can't be found will return TRANSACTION_NOT_FOUND, else will return OK and store the transaction in a structure
*/
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	
	for (int i = 0; i < 4; i++)
	{
		if (transactionSequenceNumber == transaction[i].transactionSequenceNumber)
		{
			printf("\nThe process was saved successfully.\n\nThe process sequence number is: %d", transactionSequenceNumber);
			transData->cardHolderData=transaction[i].cardHolderData;
			transData->terminalData = transaction[i].terminalData;
			transData->transState = transaction[i].transState;
			transData->transactionSequenceNumber = transaction[i].transactionSequenceNumber;
			printf("\n\nCustomer's name:");
			puts(transaction[i].cardHolderData.cardHolderName);
			printf("\nCustomer's card expiration date is:");
			puts(transaction[i].cardHolderData.cardExpirationDate);
			printf("\nCustomer's PAN number is :");
			puts(transaction[i].cardHolderData.primaryAccountNumber);
			printf("\nCustomer's transaction amount is :");
			printf("%f", transaction[i].terminalData.transAmount);
			printf("\n\nCustomer's new balance is :%f", accountsDB[i].balance);
			printf("\n\nThanks for choosing us.\n\n");
			exit;
			return ALRIGHT;
		}
	}
	return TRANSACTION_NOT_FOUND;
}
/*
This function will take all transaction data and validate its data.
It checks the account details and amount availability.
If the account does not exist return DECLINED_STOLEN_CARD, if the amount is not available will return DECLINED_INSUFFECIENT_FUND,
if a transaction can't be saved will return INTERNAL_SERVER_ERROR and will not save the transaction, else returns APPROVED.
It will update the database with the new balance.
*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if(isValidAccount(&transData->cardHolderData) == ALRIGHT)
	{
		if (isAmountAvailable(&transData->terminalData) == ALRIGHT)
		{
			accountsDB[index_of_customer].balance = accountsDB[index_of_customer].balance - transData->terminalData.transAmount;
			
			if (saveTransaction(transData) == APPROVED)
				return APPROVED;
			return INTERNAL_SERVER_ERROR;
		}
		return DECLINED_STOLEN_CARD;
	}
	return DECLINED_INSUFFECIENT_FUND;
}