
//Header files inclusion
#include"voting.h"  
#include"voting_request.h"
#include"voting_response.h"

/*****************************Creating Votig Menu *********************/	
void voting()
{
	char choice=0;                                                                   //local variable for user input
	int invalid_option = 0;                                                          //variable for counting invalid option
	static Vote *root[COL_SIZE];
	printf(" Voting Menu\n");

	printf(" 1.Voting request \n 2.Voting response\n *.Main menu\n");
	void (*fp[2])()={voting_request,voting_response};  //Array of function pointers

	while(1)
	{
		printf("Enter the option\n");
		scanf(" %c",&choice);		
				if(invalid_option < 3)
				{
					switch(choice)
					{
						case '1': fp[0](root);                                            // fun call for create_voting_req_form
							  break;
						case '2': fp[1](root);                                           // fun call for delete_voting_req_form
							  break;
						case '*': main();                                                // calling main menu fun
							  break;
						default:invalid_option++;
							printf("\nError:Invalid option\n\n");break;		// counting the invalid options
					}
				}
				else
				{
					printf("\nError: user entered invalid option three times\n\n");
					main();
				}
	}
}

