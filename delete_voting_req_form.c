#include"voting_request.h"

/****************fun defination for deleting voting req form*****************************/

void delete_voting_req_form(Vote **root)
{
	int form_option;                                                // user choice for form deletion
	char form[FORM_LEN];
	int count=0;

	if(Count_forms > 0)                                                   // is threre any form exists or not
	{
		printf("Available voting forms are: \n");
		for(int i = 0;i < Count_forms;i++)                            // to display list of existing form
		{
			printf("%d. %s\n", i+1, Forms[i]);
		}

		while(1)
		{
			printf("Enter the option: ");
			scanf("%d", &form_option);                                    //scan the form option
			if(form_option == 0 || form_option <= Count_forms) //To check condition for invalid option
			{
				strcpy(form, Forms[form_option-1]);     // becoz array started with zero,getting the name of form to deleting file
				strcat(form,"_request.xlsx");
				char ch;
				printf("\nAre you sure you want to delete the final: [y] or [n] ?");
				__fpurge(stdin);
				scanf("%c",&ch);
				if(ch=='y' ||ch=='Y')
				{
					if(remove(form)==0)                            // to remove given file
					{                                     
						printf("File deleted successfully\n");
						for(int i = form_option;i < Count_forms;i++)                 //to maintain sequence of form list
						{
							strcpy(Forms[i-1], Forms[i]);
							root[i-1] = root[i];

						}
						Count_forms--; 
						main();
					}  
				}
				else
				{
					printf("File is not deleted\n");
					main();
				}
			}
			else
			{
				count++;
				if(count != 3) //To check condition for invalid option for three times
				{
					printf("\nError: Invalid option\n\n");

				}
				else
				{
					printf("\nError: User entered invalid option for three times\n\n");
					main();
				}
			}
		}
	}
	else
	{
		printf("No voting file has created\n");
		main();
	}

}
