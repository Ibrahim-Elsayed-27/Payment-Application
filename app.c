#pragma warning(disable : 4996)
#include "app.h"
#include "card.h"
#include "terminal.h"
#include "server.h"
#include <stdio.h>
#include <string.h>
void appStart(void) {
	struct ST_cardData_t new_card;
	struct ST_terminalData_t new_terminal;
	struct Valid_data user_Data;
	setMaxAmount(&new_terminal, 50000);
	printf("Enter The Cardholder Name:");
	gets(&new_card.cardHolderName);
	while (getCardHolderName(&new_card) == WRONG_NAME) {
		printf("Enter a Valid Cardholder Name:");
		gets(&new_card.cardHolderName);
	}
	printf("Enter The Expiration Date:");
	gets(&new_card.cardExpirationDate);
	while (getCardExpiryDate(&new_card) == WRONG_EXP_DATE) {
		printf("Enter a Valid Expiration Date:");
		gets(&new_card.cardExpirationDate);
	}
	printf("Enter The PAN Number:");
	gets(&new_card.primaryAccountNumber);
	while (getCardPAN(&new_card) == WRONG_PAN) {
		printf("Enter a Valid PAN Number:");
		gets(&new_card.primaryAccountNumber);
	}
	printf("Enter The Transaction Date:");
	gets(&new_terminal.transactionDate);
	while (getTransactionDate(&new_terminal) == WRONG_DATE) {
		printf("Enter a Valid Transaction Date:");
		gets(&new_terminal.transactionDate);
	}
	if (isCardExpired(&new_card, &new_terminal) == EXPIRED_CARD) {
		printf("Declined Expired Card");
	}
	else {
		printf("Enter The Transaction Amount:");
		scanf("%f", &new_terminal.transAmount);
		while (getTransactionAmount(&new_terminal) == INVALID_AMOUNT) {
			printf("Enter a Valid Transaction Amount:");
			scanf("%f", &new_terminal.transAmount);
		}
		if (isBelowMaxAmount(&new_terminal) == EXCEED_MAX_AMOUNT) {
			printf("Declined Amount Exceeding Limit");

		}
		else {
			struct ST_transaction_t new_trans = { new_card,new_terminal };
			switch (recieveTransactionData(&new_trans)) {
			case FRAUD_CARD:
				printf("Declined Invalid Account");
				break;
			case DECLINED_INSUFFECIENT_FUND:
				printf("DECLINED INSUFFECIENT FUND");
				break;
			case DECLINED_STOLEN_CARD:
				printf("DECLINED STOLEN CARD");
				break;
			case INTERNAL_SERVER_ERROR:
				printf("INTERNAL SERVER ERROR");
				break;
			case APPROVED:
				user_Data = isValidAccount(&new_card);
				printf("APPROVED\nNew Balanace:%f", user_Data.accountRefrence->balance);
				break;
			}
		}
	}

		printf("\n\n");

	}
