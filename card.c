#include "card.h"
#include<stdio.h>
#include <ctype.h>
#include <string.h>
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	enum EN_cardError_t check= CARD_OK;
	uint8_t size = strlen(cardData->cardHolderName);
	if (size < 20 || size > 24) {
		check = WRONG_NAME;
	}
	else {
		for (int i = 0; i < 25; i++) {
			if (!isalpha(cardData->cardHolderName[i]) && cardData->cardHolderName[i] != NULL) {
				if (!isspace(cardData->cardHolderName[i])) {
					check = WRONG_NAME;
					break;
				}
			}
		}
	}

	//printf("%d",size);
	return check;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	enum EN_cardError_t check = CARD_OK;
	uint8_t size = 0;
	size = strlen(cardData->cardExpirationDate);
	if ((size !=5)) {
		check = WRONG_EXP_DATE;
	}
	else {
		if (cardData->cardExpirationDate[2] != 47){
			check = WRONG_EXP_DATE;
		}
		else {
			for (int i = 0; i < 5; i++) {
				if ((!isdigit(cardData->cardExpirationDate[i]) && i != 2)) {
					check = WRONG_EXP_DATE;
					break;
				}
			}
		}
		
	}
	return check;
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	enum EN_cardError_t check = CARD_OK;
	uint8_t size = strlen(cardData->primaryAccountNumber);

	if (size < 16 || size > 19) {
		check = WRONG_PAN;
	}
	else {
		for (int i = 0; i < size; i++) {
			if (!isdigit(cardData->primaryAccountNumber[i])) {
				check = WRONG_PAN;
				break;
			}
		}
	}

	return check;
}



void getCardHolderNameTest(void) {
	printf("Tester Name: Ibrahim Elsayed\nFunction Name : getCardHolderName\n");

	char results[4][15] = { "WRONG_NAME","CARD_OK","WRONG_NAME" ,"WRONG_NAME" };
	enum EN_cardError_t check;
	struct ST_cardData_t client1 = { "ahmed" };
	struct ST_cardData_t client2 = { "ahmed mohammed mostafa" };
	struct ST_cardData_t client3 = { "" };
	struct ST_cardData_t client4 = { "Ahm1ed mohammed mostfa" };
	struct ST_cardData_t clients[] = { client1,client2,client3,client4 };

	for (int i = 0; i < 4; i++) {
		printf("Test Case:%d\nInput Data:%s\nExpected Result:%s\nActual Result:", i, clients[i].cardHolderName, results[i]);
		check = getCardHolderName(&clients[i]);
		if (check == WRONG_NAME) {
			printf("WRONG_NAME\n\n\n");
		}
		else {
			printf("CARD_OK\n\n\n");
		}


	}
}

void getCardExpiryDateTest(void) {
		printf("Tester Name: Ibrahim Elsayed\nFunction Name : getCardExpiryDate\n");


		enum EN_cardError_t check;
		char results[4][15] = { "CARD_OK","WRONG_EXP_DATE","WRONG_EXP_DATE" ,"WRONG_EXP_DATE" };
		struct ST_cardData_t client1 = { "ahmed","***","01/23"};
		struct ST_cardData_t client2 = { "ahmed mohammed mostafa","***","0/23" };
		struct ST_cardData_t client3 = { "" ,"***","" };
		struct ST_cardData_t client4 = { "Ahm1ed mohammed mostfa","***","AA/23" };
		struct ST_cardData_t clients[] = { client1,client2,client3,client4 };

		for (int i = 0; i < 4; i++) {
			printf("Test Case:%d\nInput Data:%s\nExpected Result:%s\nActual Result:", i, &clients[i].cardExpirationDate, results[i]);
			check = getCardExpiryDate(&clients[i]);
			if (check == WRONG_EXP_DATE) {
				printf("WRONG_EXP_DATE\n\n\n");
			}
			else {
				printf("CARD_OK\n\n\n");
			}


		}
}

void getCardPANTest(void) {
	printf("Tester Name: Ibrahim Elsayed\nFunction Name : getCardPANTest\n");


	enum EN_cardError_t check;
	char results[4][15] = { "CARD_OK","WRONG_PAN","WRONG_PAN" ,"WRONG_PAN" };
	struct ST_cardData_t client1 = { "ahmed","1111111111111111"};
	struct ST_cardData_t client2 = { "ahmed mohammed mostafa" ,"11111111111111111111"};
	struct ST_cardData_t client3 = { "" ,""};
	struct ST_cardData_t client4 = { "Ahm1ed mohammed mostfa","1111aaaaa235"};
	struct ST_cardData_t clients[] = { client1,client2,client3,client4 };

	for (int i = 0; i < 4; i++) {
		printf("Test Case:%d\nInput Data:%s\nExpected Result:%s\nActual Result:", i, clients[i].primaryAccountNumber, results[i]);
		check = getCardPAN(&clients[i]);
		if (check == WRONG_PAN) {
			printf("WRONG_PAN\n\n\n");
		}
		else {
			printf("CARD_OK\n\n\n");
		}


	}
	
}
