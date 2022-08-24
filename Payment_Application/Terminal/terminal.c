#include "terminal.h"

/*
this function will check if the PAN number entered by the user is a luhn number or not and will return true if true 
other wise it will return false.
*/
bool checkLuhn(uint8_t *cardNo)
{	
	int temp;
	int check_sum = 0, first_sum = 0, second_sum = 0;
	int length = strlen(cardNo);
	//the first for loop will add the numbers that won't be multiplied by 2 .
	for (int i = length - 1; i >= 0; i = i - 2)
	{
		first_sum += cardNo[i] - '0';
	}
	// the second for loop will add the numbers that will be mutliplied by 2 .
	for (int i = length - 2; i >= 0; i = i - 2)
	{
		temp = (cardNo[i] - '0') * 2;
		if (temp > 10)
			temp = temp - 9;
		second_sum += temp;
	}
	//check_sum will add the whole numbers after the calculations if the number is divisable by 10 it will return true else it will return falase.
	check_sum = first_sum + second_sum;
	return(check_sum % 10 == 0);
}
/*
The function will read the current date from your computer and store it into terminal data with the mentioned size and format.
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{	//storing the date in string of 9 char
	char datebuffer[9];
	_strdate(datebuffer);
	//copy the date to termdata
	strcpy_s(termData->transactionDate, sizeof(termData->transactionDate) / sizeof(termData->transactionDate[0]), datebuffer);
	//return OK as we get the data of the day of transiction 
	return GOOD;
}
/*
This function compares the card expiry date with the transaction date.
If the card expiration date is before the transaction date will return EXPIRED_CARD, else return OK.
*/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	//check year
	if (cardData.cardExpirationDate[3] < termData.transactionDate[6])
		return EXPIRED_CARD;
	else if (cardData.cardExpirationDate[3] == termData.transactionDate[6])
	{
		if (cardData.cardExpirationDate[4] < termData.transactionDate[7])
			return EXPIRED_CARD;
		else if (cardData.cardExpirationDate[4] == termData.transactionDate[7])
		{	//check month if the year is the same
			if (cardData.cardExpirationDate[0] < termData.transactionDate[0])
				return EXPIRED_CARD;
			else if (cardData.cardExpirationDate[0] == termData.transactionDate[0])
			{
				if (cardData.cardExpirationDate[1] < termData.transactionDate[1])
					return EXPIRED_CARD;
			}
		}
	}
	//nothing wrong return ok
	return GOOD;
}
/*

this function check if the primary card number is a luhn so it's a valid card or no.
*/

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	//applaying luhn algorithm to check for the card
	if (checkLuhn(&cardData->primaryAccountNumber))
		return GOOD;
	printf("\nNot a luhn number");
	return INVALID_CARD;
}

/*
This function asks for the transaction amount and saves it into terminal data.
If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return OK.
*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("\nPlease,enter the transaction amount:");
	scanf("%f",&termData->transAmount);
	if (termData->transAmount <= 0)
		return INVALID_AMOUNT;

	return GOOD;
}

/*
This function compares the transaction amount with the terminal max amount.
If the transaction amount is larger than the terminal max amount will return EXCEED_MAX_AMOUNT, else return OK.
*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	return GOOD;
}

/*

This function sets the maximum allowed amount into terminal data.
Transaction max amount is a float number.
If transaction max amount less than or equal to 0 will return INVALID_MAX_AMOUNT error, else return OK.
*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	//i will let the user to decide the max amount of to be entered.
	printf("\nPlease,enter the max amount of the transaction.");
	scanf("%f",&termData->maxTransAmount);
	if (termData->maxTransAmount <= 0)
		return INVALID_MAX_AMOUNT;
	return GOOD;
}