#include"registration.h"
#include"create_registration_form.h"
#include"delete_registration_form.h"
#include"send_registration_form.h"

//*******************************************Training resgistration*****************************************

void registration()
{
	char choice;

	static Employee_training_data *first_field[COL_SIZE]; //An array of pointer to store the address of first field in each training registration form
	int count_option = 0;
	//Array of Function pointers to call functions
	void (*fp[3])(Employee_training_data **) = {create_training_registration_form, delete_training_registration_form, send_training_registration_form};
	while(1)
	{
		printf("1. Create Training Registration form\n2. Delete Training Registration form\n3. Send Training Registration form\n*. Main menu");
		printf("\nEnter the option: ");
		scanf(" %c", &choice);
		//To call functions based on user choice
		switch(choice)
		{
			case '1': fp[choice - 49](first_field);
				  break;
			case '2': fp[choice - 49](first_field);
				  break;
			case '3': fp[choice - 49](first_field);
				  break;
			case '*': main();
				  break;
			default:  count_option++;
				  if(count_option == 3)
				  {
					  printf("\nError: User entered invalid option for three times\n\n");
					  main();
				  }
				  else
				  {
					  printf("\nError: Invalid option\n");
				  }
				  break; 
		}
	}
}
