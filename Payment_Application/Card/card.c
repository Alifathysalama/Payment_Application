#include"card.h"

/*This function will ask for the cardholder's name and store it into card data.
Card holder name is 24 characters string max and 20 min.
If the cardholder name is NULL, less than 20 characters or more than 24 will return WRONG_NAME error, else return OK.
*/
EN_cardError_t getCardHolderName(ST_cardData_t * cardData)
{	//helping the customer with the some required tips to enter the name correctly
	printf("Some tips for name\n1-It's a must for a name to be more than 20 character and less than 25 character\n2-The name should not contain any numbers at any case\n3-You can not enter a null name\n\n");
	printf("Please,Enter your name:");
	uint8_t temp[25];
	gets(temp);
	//check if the name meets the requirements which is that the name not null ,not less than 20 character and not more than 24 character
	if (strlen(temp) == 0 || strlen(temp) <= 20 || strlen(temp) > 24)
	{
		printf("Invalid name\n");
		return WRONG_NAME;
	}
	//check if the entered name is a real name not just some letters with numbers included
	for (int i = 0; i < strlen(temp); i++)
	{

		if (isdigit(temp[i]))
		{
			printf("Invalid name\n");
			return WRONG_NAME;
		}
	}
	strcpy_s(cardData->cardHolderName, sizeof(cardData->cardHolderName) / sizeof(cardData->cardHolderName[0]), temp);
	//if all is well then return ok
	return OK;
}
/*
This function will ask for the card expiry date and store it in card data.
Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".
If the card expiry date is NULL, less or more than 5 characters, or has the wrong format will return WRONG_EXP_DATE error, else return OK.
*/
EN_cardError_t getCardExpiryDate(ST_cardData_t * cardData)
{	//assigning the expiry date to temp and check befor assigning it to the cardData.
	uint8_t temp[6];
	//helping the customer with the some required tips to enter the expiration date correctly
	printf("\nHelping you in case you don't know the correct format,the correct format is MM/YY, eg '03/24'\n");
	printf("\nPlease,Enter your card expiration date:");
	gets(temp);
	printf("\n");
	//to check if he entered the right slash not any other specail character in the right place
	if (temp[2] != '/')
	{
		printf("\nWrong format");
		return WRONG_EXP_DATE;
	}
	//checking that the entered is numbers alone no alphapets
	for (int i = 0; i < 5; i++)
	{
		if (isdigit(temp[i]) || i == 2)
			continue;
		printf("\nNot a number");
		return WRONG_EXP_DATE;
	}
	//as speaking in 21th century from 2000 to 2099
	//this is stored later to compare between the transation date and expiry date
	if (temp[0] > '1')
		return WRONG_EXP_DATE;
	else if (temp[0] == '1')
	{
		if (temp[1] > '2')
			return WRONG_EXP_DATE;
	}
	//if all is well then return ok
	strcpy_s(cardData->cardExpirationDate, sizeof(cardData->cardExpirationDate) / sizeof(cardData->cardExpirationDate[0]), temp);
	return OK;
}
/*
This function will ask for the card's Primary Account Number and store it in card data.
PAN is 20 characters alphanumeric only string 19 character max, and 16 character min.
If the PAN is NULL, less than 16 or more than 19 characters, will return WRONG_PAN error, else return OK.
*/
EN_cardError_t getCardPAN(ST_cardData_t * cardData)
{
	uint8_t temp[20];
	//get PAN from customer
	printf("Please,Enter your card's primary account number (PAN):");
	gets(temp);
	//checking for wrong inputs
	if (strlen(temp) == 0 || strlen(temp) < 16 || strlen(temp) > 19)
	{
		return WRONG_PAN;
	}
	for (int i = 0; i < strlen(temp); i++)
	{
		if (isdigit(temp[i]))
			continue;
		return WRONG_PAN;
	}
	//if all is well then return ok
	strcpy_s(cardData->primaryAccountNumber, sizeof(cardData->primaryAccountNumber) / sizeof(cardData->primaryAccountNumber[0]), temp);
	return OK;
}