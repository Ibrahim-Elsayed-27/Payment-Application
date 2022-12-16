#pragma warning(disable : 4996)
#include "terminal.h"
#include <time.h>
#include <stdio.h>
#include<string.h>
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	enum EN_terminalError_t check = TERMINAL_OK;
	int size = strlen(termData->transactionDate);
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char date[11]="", day[10], month[10], year[10];
	sprintf(day, "%d", tm.tm_mday);
	sprintf(month, "%d", (tm.tm_mon + 1)); 
	sprintf(year, "%d", (tm.tm_year + 1900));
	strcat(date, day); strcat(date, "/"); strcat(date, month); strcat(date, "/"); strcat(date,year);
	if (size != 10) {
		check = WRONG_DATE;
	}
	else if (strcmp(termData->transactionDate,date)) {
		check = WRONG_DATE;
		
	}
	return check;
}


EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	char term_date[6] = { termData->transactionDate[3],termData->transactionDate[4],'/'  ,termData->transactionDate[8],termData->transactionDate[9] };
	enum EN_terminalError_t check = TERMINAL_OK;
	char comp_date[6];
	strcpy(comp_date, cardData->cardExpirationDate);

	if (comp_date[4] > term_date[4]) {
		;
	}
	else if (comp_date[4] == term_date[4]) {
		if (comp_date[3] > term_date[3]) {
			;
		}
		else if (comp_date[3] == term_date[3]) {
			if (comp_date[1] > term_date[1]) {
				;
			}
			else if (comp_date[1] == term_date[1]) {
				if (comp_date[0] >= term_date[0]) {
					;
				}
				else {
					check = EXPIRED_CARD;
				}
			}
			else {
				check = EXPIRED_CARD;

			}
		}
		else {
			check = EXPIRED_CARD;
		}
	}
	else {
		check = EXPIRED_CARD;
	}
	return check;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	enum EN_terminalError_t check = TERMINAL_OK;
	if (!(termData->transAmount > 0)) {
		check = INVALID_AMOUNT;
	}
	return check;

}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	enum EN_terminalError_t check = TERMINAL_OK;
	if (termData->maxTransAmount < termData->transAmount) {
		check = EXCEED_MAX_AMOUNT;
	}
	return check;
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
	enum EN_terminalError_t check = TERMINAL_OK;
	if (maxAmount > 0) {
		termData->maxTransAmount = maxAmount;
	}
	else {
		check = INVALID_MAX_AMOUNT;
	}
	return check;
}

void getTransactionDateTest(void) {
	printf("Tester Name: Ibrahim Elsayed\nFunction Name : getTransactionDateTest\n");


	enum EN_cardError_t check;
	char results[4][15] = { "WRONG_DATE","TERMINAL_OK","WRONG_DATE" ,"WRONG_DATE" };
	struct ST_terminalData_t client1 = {0,0,""};
	struct ST_terminalData_t client2 = {0,0,"16/12/2022"};
	struct ST_terminalData_t client3 = {0,0,"03/12/2022"};
	struct ST_terminalData_t client4 = {0,0,"AA/12"};
	struct ST_terminalData_t clients[] = { client1,client2,client3,client4 };

	for (int i = 0; i < 4; i++) {
		printf("Test Case:%d\nInput Data:%s\nExpected Result:%s\nActual Result:", i, clients[i].transactionDate, results[i]);
		check = getTransactionDate(&clients[i]);
		if (check == WRONG_DATE) {
			printf("WRONG_DATE\n\n\n");
		}
		else {
			printf("TERMINAL_OK\n\n\n");
		}


	}
}


 void isCardExpriedTest(void) {
	printf("Tester Name: Ibrahim Elsayed\nFunction Name : isCardExpriedTest\n");
	enum EN_terminalError_t check;
	struct ST_cardData_t client1 = { "ahmed","***","01/23" };
	struct ST_cardData_t client2 = { "ahmed mohammed mostafa","***","05/23" };
	struct ST_cardData_t client3 = { "" ,"***","11/22" };
	struct ST_cardData_t client4 = { "Ahm1ed mohammed mostfa","***","12/22" };
	struct ST_cardData_t clients[] = { client1,client2,client3,client4 };
	struct ST_terminalData_t terminal1 = { 0,0,"13/12/2022" };
	char results[4][15] = { "TERMINAL_OK","TERMINAL_OK","EXPIRED_CARD" ,"TERMINAL_OK" };
	for (int i = 0; i < 4; i++) {
		printf("Test Case:%d\nInput Data:%s\nExpected Result:%s\nActual Result:", i, clients[i].cardExpirationDate, results[i]);
		check = isCardExpired(&clients[i],&terminal1);
	if (check == EXPIRED_CARD) {
		printf("EXPIRED_CARD\n\n\n");
	}
	else {
		printf("TERMINAL_OK\n\n\n");
	}

	}



}


 void getTransactionAmountTest(void) {
	 printf("Tester Name: Ibrahim Elsayed\nFunction Name : getTransactionAmountTest\n");
	 enum EN_terminalError_t check = TERMINAL_OK;
	 char results[4][15] = { "TERMINAL_OK","INVALID_AMOUNT","INVALID_AMOUNT" ,"INVALID_AMOUNT" };
	 struct ST_terminalData_t terminal1 = { 10,0,"13/12/2022" };
	 struct ST_terminalData_t terminal2 = { 0,0,"13/12/2022" };
	 struct ST_terminalData_t terminal3 = { -1,0,"13/12/2022" };
	 struct ST_terminalData_t terminals[3] = {terminal1,terminal2,terminal3};
	 for (int i = 0; i < 3; i++) {
		 printf("Test Case:%d\nInput Data:%f\nExpected Result:%s\nActual Result:", i, terminals[i].transAmount, results[i]);
		 check = getTransactionAmount(&terminals[i]);
		 if (check == INVALID_AMOUNT) {
			 printf("INVALID_AMOUNT\n\n\n");
		 }
		 else {
			 printf("TERMINAL_OK\n\n\n");
		 }
	 }
 }




 void isBelowMaxAmountTest(void) {
	 printf("Tester Name: Ibrahim Elsayed\nFunction Name : isBelowMaxAmountTest\n");
	 enum EN_terminalError_t check = TERMINAL_OK;
	 char results[3][20] = { "TERMINAL_OK","TERMINAL_OK","EXCEED_MAX_AMOUNT",};
	 struct ST_terminalData_t terminal1 = { 50,50,"13/12/2022" };
	 struct ST_terminalData_t terminal2 = { 40,50,"13/12/2022" };
	 struct ST_terminalData_t terminal3 = { 60,50,"13/12/2022" };
	 struct ST_terminalData_t terminals[3] = { terminal1,terminal2,terminal3 };
	 for (int i = 0; i < 3; i++) {
		 printf("Test Case:%d\nInput Data:%f\nExpected Result:%s\nActual Result:", i, terminals[i].transAmount, results[i]);
		 check = isBelowMaxAmount(&terminals[i]);
		 if (check == EXCEED_MAX_AMOUNT) {
			 printf("EXCEED_MAX_AMOUNT\n\n\n");
		 }
		 else {
			 printf("TERMINAL_OK\n\n\n");
		 }
	 }
 }


 void setMaxAmountTest(void) {
	 printf("Tester Name: Ibrahim Elsayed\nFunction Name : isBelowMaxAmountTest\n");
	 enum EN_terminalError_t check = TERMINAL_OK;
	 char results[3][20] = { "TERMINAL_OK","INVALID_MAX_AMOUNT","INVALID_MAX_AMOUNT", };
	 struct ST_terminalData_t terminal1 = { 50,50,"13/12/2022" };
	 float inputs[3] = {10,0,-10};
	 for (int i = 0; i < 3; i++) {
		 printf("Test Case:%d\nInput Data:%f\nExpected Result:%s\nActual Result:", i,inputs[i], results[i]);
		 check = setMaxAmount(&terminal1,inputs[i]);
		 if (check == INVALID_MAX_AMOUNT) {
			 printf("INVALID_MAX_AMOUNT\n\n\n");
		 }
		 else { 
			 printf("TERMINAL_OK\n\n\n");
		 }
	 }
 }