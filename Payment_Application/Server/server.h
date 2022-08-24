#pragma once
/*server.h header guard and program*/

#ifndef SERVER_H
#define SERVER_H 

#include<stdio.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"

typedef unsigned int uint32_t;

int index_of_customer;
static uint32_t sequnce_start_number= 839446600;

typedef enum EN_serverError_t
{
	ALRIGHT, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t;

typedef struct ST_accountsDB_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;


typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;


static ST_accountsDB_t accountsDB[255]= {
	{ 155000, "6520403710037049" },
	{ 3000000, "1231763341964577"},
	{ 212000, "6829449208182993" },
	{ 7800, "5244089878027513" }
};
 static ST_transaction_t transaction[255]= {
	{ 0 },
	{ 0},
	{ 0 },
	{ 0 }
};

EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData);


#endif  /*end of server.h*/