#pragma warning(disable : 4996)
#include "server.h"
#include <stdio.h>
#include <string.h>


ST_accountsDB_t accountsDB[255] = {
    {2000.0, RUNNING, "8989374615436851"},
    {4000.0, BLOCKED, "8989374615436852"},
    {6000.0, RUNNING, "8989374615436853"},
    {0, BLOCKED, "8989374615436854"},
    {10000.0, RUNNING, "8989374615436855"}
};

ST_transaction_t transactionDB[255] = {0};



Valid_data isValidAccount(ST_cardData_t* cardData) {
    EN_serverError_t check = ACCOUNT_NOT_FOUND;
    ST_accountsDB_t* accountRefrence = NULL;
    for (int i = 0; i < 255; i++) {
        if (!strcmp(&cardData->primaryAccountNumber, &accountsDB[i].primaryAccountNumber)) {
            check=SERVER_OK;
            accountRefrence = &accountsDB[i];
            break;
        }
    }
    Valid_data my_data = { check,accountRefrence };
    return my_data;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	EN_serverError_t check = SERVER_OK;
	if (accountRefrence->state == BLOCKED) {
		check = BLOCKED_ACCOUNT;
	}
	return check;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	EN_serverError_t check = SERVER_OK;
	if (termData->transAmount > accountRefrence->balance) {
		check = LOW_BALANCE;
	}
	return check;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	EN_serverError_t  check = APPROVED;
	transData->transactionSequenceNumber += 1;
	for (int i = 0; i < 255; i++) {
		if (!strcmp(transactionDB[i].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName)) {
			transactionDB[i] = *transData;
			break;
		}
		else if (!strcmp(transactionDB[i].cardHolderData.cardHolderName, "")) {
			transactionDB[i] = *transData;
			break;
		}
		else {
			check = SAVING_FAILED;
		}
	}
	return check;
}
void listSavedTransactions(void) {
	for (int i = 0; i < 255; i++) {
		if (!strcmp(transactionDB[i].cardHolderData.cardHolderName, "")) {
			break;
		}
		else {
			EN_transState_t check = transactionDB[i].transState;
			char check_string[40];
			switch (check)
			{
			case APPROVED:
				strcpy(check_string, "APPROVED");
				break;
			case DECLINED_INSUFFECIENT_FUND:
				strcpy(check_string, "DECLINED_INSUFFECIENT_FUND");
				break;
			case DECLINED_STOLEN_CARD:
				strcpy(check_string, "DECLINED_STOLEN_CARD");
				break;
			case FRAUD_CARD:
				strcpy(check_string, "FRAUD_CARD");
				break;
			case INTERNAL_SERVER_ERROR:
				strcpy(check_string, "INTERNAL_SERVER_ERROR");
				break;
			}
			printf("################################\n");
			printf("Transaction Sequence Number:%d\nTransaction Date:%s\nTransaction Amount:%f\n", transactionDB[i].transactionSequenceNumber, transactionDB[i].terminalData.transactionDate, transactionDB[i].terminalData.transAmount);
			printf("Transaction State:%s\nTerminal Max Amount:%f\nCardholder Name:%s\nPAN:%s\nCard Expiration Date:%s\n", check_string, transactionDB[i].terminalData.maxTransAmount, transactionDB[i].cardHolderData.cardHolderName, transactionDB[i].cardHolderData.primaryAccountNumber, transactionDB[i].cardHolderData.cardExpirationDate);
			printf("################################\n\n\n");
		}
	}
}
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	EN_accountState_t check = APPROVED;
	Valid_data client_data;
	EN_serverError_t validation_check;
	client_data = isValidAccount(&transData->cardHolderData);
	if (client_data.check == ACCOUNT_NOT_FOUND) {
		check = FRAUD_CARD;
	}
	else {
		validation_check = isAmountAvailable(&transData->terminalData, client_data.accountRefrence);
		if (validation_check == LOW_BALANCE) {
			check = DECLINED_INSUFFECIENT_FUND;
		}
		else {
			validation_check = isBlockedAccount(client_data.accountRefrence);
			if (validation_check == BLOCKED_ACCOUNT) {
				check = DECLINED_STOLEN_CARD;
			}
			else {
				validation_check = saveTransaction(client_data.accountRefrence);
				if (validation_check == APPROVED) {
					check = APPROVED;
					client_data.accountRefrence->balance -= transData->terminalData.transAmount;
				}
				else {
					check = INTERNAL_SERVER_ERROR;
				}
			
					
				
			}
		}
	}
	return check;
}

void isValidAccountTest(void) {
	printf("Tester Name: Ibrahim Elsayed\nFunction Name : isValidAccountTest\n");

	struct Valid_data mydata;
	char results[4][20] = { "SERVER_OK","SERVER_OK","ACCOUNT_NOT_FOUND" ,"ACCOUNT_NOT_FOUND" };
	struct ST_cardData_t client1 = { "ahmed","8989374615436851" };
	struct ST_cardData_t client2 = { "ahmed mohammed mostafa" ,"8989374615436855" };
	struct ST_cardData_t client3 = { "" ,"" };
	struct ST_cardData_t client4 = { "Ahm1ed mohammed mostfa","11111111111111111" };
	struct ST_cardData_t clients[] = { client1,client2,client3,client4 };

	for (int i = 0; i < 4; i++) {
		printf("Test Case:%d\nInput Data:%s\nExpected Result:%s\nActual Result:", i, clients[i].primaryAccountNumber, results[i]);
		mydata = isValidAccount(&clients[i]);
		if (mydata.check == ACCOUNT_NOT_FOUND || !(strcmp(mydata.accountRefrence->primaryAccountNumber,""))) {
			printf("ACCOUNT_NOT_FOUND --> Refrence:NULL\n\n\n");
		}
		else {
			printf("SERVER_OK --> Refrence:%s\n\n\n", mydata.accountRefrence->primaryAccountNumber);
		}


	}
}





void isBlockedAccountTest(void){
	printf("Tester Name: Ibrahim Elsayed\nFunction Name : isBlockedAccountTest\n");
	EN_serverError_t check;
	char results[4][20] = { "SERVER_OK","BLOCKED_ACCOUNT","SERVER_OK" ,"BLOCKED_ACCOUNT" };
	char state[10];
	for (int i = 0; i < 4; i++) {
		if (accountsDB[i].state == RUNNING) {
			strcpy(state,"RUNNING");
		}
		else {
			strcpy(state,"BLOCKED");
		}
		printf("Test Case:%d\nInput Data:%s\nExpected Result:%s\nActual Result:", i, state, results[i]);
		check = isBlockedAccount(&accountsDB[i]);
		if (check == BLOCKED_ACCOUNT) {
			printf("BLOCKED_ACCOUNT\n\n\n");
		}
		else {
			printf("SERVER_OK\n\n\n");
		}
	}
}



void isAmountAvailableTest(void) {
	printf("Tester Name: Ibrahim Elsayed\nFunction Name : isAmountAvailableTest\n");
	EN_serverError_t  check = SERVER_OK;
	char results[3][15] = { "LOW_BALANCE","SERVER_OK" };
	struct ST_terminalData_t terminal1 = { 3000,0,"13/12/2022" };
	struct ST_terminalData_t terminal2 = { 2000,0,"13/12/2022" };
	struct ST_terminalData_t terminals[2] = { terminal1,terminal2};
	for (int i = 0; i < 2; i++) {
		printf("Test Case:%d\nInput Data:%f\nExpected Result:%s\nActual Result:", i, terminals[i].transAmount, results[i]);
		check = isAmountAvailable(&terminals[i],&accountsDB[0]);
		if (check == LOW_BALANCE) {
			printf("LOW_BALANCE\n\n\n");
		}
		else {
			printf("SERVER_OK\n\n\n");
		}
	}
}

