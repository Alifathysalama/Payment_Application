#include "app.h"
/*

this function will start the application by the order given in the flow chart 
1->>> take the card information: NAME,PAN,EXP_DATE
2->>> implement the terminal : set MAX_AMOUNT,check iscardexpired or not,check if the PAN is luhn number or not, transaction amount the customer want,
check if the amount available or not.
3->> implementing the server : check all the information entered by the customer with the database.

*/
ST_transaction_t transaction_customer;
ST_transaction_t* customer_test = { NULL };
void appStart(void)
{	//start the application	
	printf("Welcome,dear customer\n\n");
	//process #no.1
	getCardHolderName(&transaction_customer.cardHolderData);
	getCardExpiryDate(&transaction_customer.cardHolderData);
	getCardPAN(&transaction_customer.cardHolderData);
	//process #no.2
	getTransactionDate(&transaction_customer.terminalData);
	if (isCardExpired(transaction_customer.cardHolderData, transaction_customer.terminalData) == EXPIRED_CARD)
		return;
	isValidCardPAN(&transaction_customer.cardHolderData);
	setMaxAmount(&transaction_customer.terminalData);
	getTransactionAmount(&transaction_customer.terminalData);
	if (isBelowMaxAmount(&transaction_customer.terminalData) == EXCEED_MAX_AMOUNT)
		return;
	//process #no.3
	if (isValidAccount(&transaction_customer.cardHolderData)==DECLINED_STOLEN_CARD)
		return;
	if (isAmountAvailable(&transaction_customer.terminalData) == DECLINED_INSUFFECIENT_FUND)
		return;
	recieveTransactionData(&transaction_customer);
	getTransaction(839446600, &customer_test);
	//end the application
}

int main()
{
	appStart();
	

	
	return 0;

}