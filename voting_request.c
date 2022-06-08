
//Header files inclusion
#include"voting_request.h"  
#include"create_voting_req_form.h"
#include"delete_voting_req_form.h"

/******************Function definition to choose creation and deletion form*************************/

void voting_request(Vote **root)
{
	char choice=0;                                                                   //local variable for user input
	int invalid_option = 0;                                                          //variable for counting invalid option
	void (*fp[2])(Vote **) = {create_voting_req_form, delete_voting_req_form};      // Array of fun pointer initialization

	while(1)
	{		
		if(invalid_option < 3)
		{

			printf("1. Create voting form\n2. Delete voting form\n*. Main menu");
			printf("\nEnter the option: ");
			scanf(" %c", &choice);
			switch(choice)
			{
				case '1': fp[0](root);                               // fun call for create_voting_req_form
					  break;
				case '2': fp[1](root);                               // fun call for delete_voting_req_form
					  break;
				case '*': main();                                   // calling main menu fun
					  break;
				default: invalid_option++;                         //invalid option counting
					 printf("Error: invalid option\n\n");
					 break;
			}
		}
		else
		{
			printf("\nError: User entered Invalid Option for three times\n\n");
			main();                                                 // calling main fun after 3 invalide input
		}
	}
}



