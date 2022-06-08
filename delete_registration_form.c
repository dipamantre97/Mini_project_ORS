#include"registration.h"
#include"delete_registration_form.h"

//****************************Delete training registration form********************************

void delete_training_registration_form(Employee_training_data **first_field)
{
	int form_option; //Integer variable to select one training from available trainings
	int count = 0;
	char form_name[COL_SIZE];
	//To display trainings available
	if(Forms_count > 0)
	{
		printf("\nAvailable trainings are: \n");
		for(int i = 0;i < Forms_count;i++)
		{
			printf("%d. %s\n", i+1, Forms[i]);
		}
		while(1)
		{
			printf("Enter the option to delete training registration form: ");
			scanf("%d", &form_option);
			if(form_option == 0 || form_option <= Forms_count) //To check condition for invalid option
			{
				strcpy(form_name,Forms[form_option-1]);

				strcat(form_name,"_training.xlsx"); //concatenate two strings

				//To delete the file selected from the user
				char ch;
				printf("\nAre you sure, you want to delete the file:([y] or [n])? ");
				__fpurge(stdin);
				scanf("%c",&ch);
				if(ch=='y' ||ch=='Y')
				{
					if(remove(form_name)==0)
					{
						printf("\nInfo: File deleted successfully\n\n");
						for(int i = form_option;i < Forms_count;i++)
						{
							strcpy(Forms[i-1], Forms[i]);
							first_field[i-1] = first_field[i];

						}
						Forms_count--; //To decrement forms count
						main();
					}
					else
					{
						printf("\nInfo: File is not deleted\n\n");
						main();
					}
				}
				else
				{
					printf("\nInfo: File is not deleted\n\n");
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
		printf("\nError: No training registration forms available\n\n");
		main();
	}
}
