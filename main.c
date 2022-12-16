#pragma warning(disable : 4996)
#include<stdio.h>
#include "app.h"
#include <string.h>
#include "card.h"
int main() {
	
	while (1) {
		char trash[5];
		appStart();
		gets(trash);
	}
	//getCardExpiryDateTest();
	//getCardHolderNameTest();
	//getCardPANTest();
	//getTransactionDateTest();
	//isCardExpriedTest();
	//isBelowMaxAmountTest();
	//setMaxAmountTest();
	/*
	for (int i = 0; i < 5; i++) {
		char state[10];
		if (accountsDB[i].state == RUNNING) {
			strcpy(state, "RUNNING");
		}
		else { strcpy(state, "BLOCKED"); }
		printf("user%d--> balance:%f  state:%s  PAN:%s\n\n", i+1, accountsDB[i].balance, state, accountsDB[i].primaryAccountNumber);
	}*/
	//ST_transaction_t tra;
	//tra.transactionSequenceNumber = 16552;
	//EN_serverError_t check;
	//check=saveTransaction(&tra);
	//transactionDB[0] = tra;
	//listSavedTransactions();
	//isValidAccountTest();
	//getTransactionAmountTest();
	//isBlockedAccountTest();
	//isAmountAvailableTest();
	/*
	struct ST_terminalData_t trial ={1140,1140,"AA/AA/AAAA"};
	enum EN_terminalError_t check;
	check=getTransactionDate(&trial);
	if (check == WRONG_DATE) {
		printf("WRONG_DATE");
	}
	else if (check == TERMINAL_OK) {
		printf("TERMINAL_OK");
	}*/
	/*
	struct ST_cardData_t client = { "Ahmed11Ahmed11Ahmed11","5555","666666" };
	enum EN_cardError_t check;
	
	check=getCardHolderName(&client);
	if (check == WRONG_NAME) {
		printf("WRONG_NAME");
	}
	else if (check == CARD_OK) {
		printf("CARD_OK");
	}
	*/
}