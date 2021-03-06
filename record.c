/* This program reads a random access file sequentially, updates data
 * already written to the file, creates new data to be placed in the
 * file, and deletes data previously in the file 
 */

#include <stdio.h>

/* clientData structure defintiion */
struct clientData
{
	int acctNum;	/* account number */
	char lastName[15];	/* account last name */
	char firstName[10];	/* account first name */
	double balance;	/* account balance */
};

int enterChoice(void);
void textFile(FILE *readPtr);
void updateRecord(FILE *fPtr);
void newRecord(FILE*fPtr);
void deleteRecord(FILE *fPtr);

int main()
{
	FILE *cfPtr;	/* credit.dat file pointer */
	int choice;	/* user's choice */

	/* fopen opens the file; exits if file cannot be opened */
	if ((cfPtr = fopen("credit.dat", "rb+")) == NULL)
	{
		printf("File could not be opened.\n");
	}
	else
	{
		/* enable user to specify action */
		while ((choice = enterChoice()) != 5)
		{
			switch (choice)
			{
				/* create text file from record file */
				case 1: textFile(cfPtr);
					break;

				/* update record */
				case 2: updateRecord(cfPtr);
					break;

				/* create record */
				case 3: newRecord(cfPtr);
					break;

				/* delete existing record */
				case 4: deleteRecord(cfPtr);
					break;
				/* display message if user does not select valid choice */
				default: printf("Incorrect choice\n");
					 break;
			}
		}

		fclose(cfPtr);
	}

	return 0;
}

/* create formatted text file for printing */
void textFile(FILE *readPtr)
{
	FILE *writePtr;	/* accounts.txt file pointer */

	/* create clientData with default information */
	struct clientData client = { 0, "", "", 0.0 };

	/* fopen opens the file; exits if file cannot be opened */
	if ((writePtr = fopen("accounts.txt", "w")) == NULL)
	{
		printf("File could not be opened.\n");
	}
	else
	{
		rewind(readPtr);	/* sets pointer to beginning of file */
		fprintf(writePtr, "%-6s%-16s%-11s%10s\n", "Acct", "Last Name", "First Name", "Balance");

		/* copy all records from randomaccess file into text file */
		while (!feof(readPtr))
		{
			fread(&client, sizeof(struct clientData), 1, readPtr);

			/* write single record to text file */
			if (client.acctNum != 0)
			{
				fprintf(writePtr, "%-6d%-16s%-11s%10.2f\n", client.acctNum, client.lastName, client.firstName, client.balance);
			}
		}

		fclose(writePtr);
	}
}

/* update balance in record */
void updateRecord(FILE *fPtr)
{
	int account;	/* account number */
	double transaction;	/* transaction amount */

	/* create clientData with no information */
	struct clientData client = { 0, "", "", 0.0 };

	/* obtain number of amount to update */
	printf("Enter account to update (1 - 100): ");
	scanf("%d", &account);

	/* move file pointer to correct record in file */
	fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);

	/* read record from file */
	fread(&client, sizeof(struct clientData), 1, fPtr);

	/* display error if account does not exist */
	if (client.acctNum == 0)
	{
		printf("Account #%d has no information.\n", account);
	}
	else	/* update record */
	{
		printf("%-6d%-16s%-11s%10.2f\n\n", client.acctNum, client.lastName, client.firstName, client.balance);

		/* request transaction amount from user */
		printf("Enter charge (+) on payment (-): ");
		scanf("%lf", &transaction);
		client.balance += transaction;	/* update record balance */

		printf("%-6d%-16s%-11s%10.2f\n", client.acctNum, client.lastName, client.firstName, client.balance);

		/* move file pointer to correct record in file */
		fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);

		/* write updated record over old record in file */
		fwrite(&client, sizeof(struct clientData), 1, fPtr);
	}
}

/* delete an existing record */
void deleteRecord(FILE *fPtr)
{
	struct clientData client;	/* stores record read from file */
	struct clientData blankClient = { 0, "", "", 0.0 };	/* blank client */

	int accountNum;	/* account number */

	/* obtain number of account to delete */
	printf("Enter account number to delete (1 - 100): ");
	scanf("%d", &accountNum);

	/* move file pointer to correct record in file */
	fseek(fPtr, (accountNum - 1) * sizeof(struct clientData), SEEK_SET);

	/* read record from file */
	fread(&client, sizeof(struct clientData), 1, fPtr);

	/* display error if record does not exist */
	if (client.acctNum == 0)
	{
		printf("Account #%d does not exist.\n", accountNum);
	}
	else	/* delete record */
	{
		/* move file pointer to correct record in file */
		fseek(fPtr, (accountNum - 1) * sizeof(struct clientData), SEEK_SET);

		/* replace existing record with blank record */
		fwrite(&blankClient, sizeof(struct clientData), 1, fPtr);
	}
}

/* create and insert record */
void newRecord(FILE *fPtr)
{
	/* create clientData with default information */
	struct clientData client = { 0, "", "", 0.0 };

	int accountNum;	/* account number */

	/* obtain number of account to create */
	printf("Enter new account number (1 - 100): ");
	scanf("%d", &accountNum);

	/* move file pointer to correct record in file */
	fseek(fPtr, (accountNum - 1) * sizeof(struct clientData), SEEK_SET);

	/* read record from file */
	fread(&client, sizeof(struct clientData), 1, fPtr);

	/* display error if account already exists */
	if (client.acctNum != 0)
	{
		printf("Account #%d already contains information.\n", client.acctNum);
	}
	else	/* create record */
	{
		/* user enters last name, first name and balance */
		printf("Enter last name, first name, balance\n? ");
		scanf("%s%s%lf", &client.lastName, &client.firstName, &client.balance);

		client.acctNum = accountNum;

		/* move file pointer to correct record in file */
		fseek(fPtr, (client.acctNum - 1) * sizeof(struct clientData), SEEK_SET);

		/* insert record in file */
		fwrite(&client, sizeof(struct clientData), 1, fPtr);
	}
}

/* enable user to input menu choice */
int enterChoice(void)
{
	int menuChoice;	/* variable to store user's choice */

	/* display available options */
	printf("\nEnter your choice\n"
			"1 - store a formatted text file og accounts called \"accounts.txt\" for printing\n"
			"2 - update an account\n"
			"3 - add a new account\n"
			"4 - delete an account\n"
			"5 - end program\n? ");

	scanf("%d", &menuChoice);	/* receive chouce from user */

	return menuChoice;
}

