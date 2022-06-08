#include"registration.h"
#include"create_registration_form.h"

//****************************Create training registration form********************************

void create_training_registration_form(Employee_training_data **first_field)
{
	char form[COL_SIZE]; //Array of character to store name of one form
	int flag = 0;
	FILE *file_pointer = NULL; 
	printf("Enter the training name: ");
	__fpurge(stdin); //To clear the input buffer
	scanf("%[^\n]%*c", form);
	//Loop to check whether the training name is already present or not
	for(int i = 0;i < Forms_count; i++)
	{
		if(strcasecmp(Forms[i], form) == 0)
		{
			flag = 1;
		}
	}
	strcpy(Forms[Forms_count], form); //Copy the content of form to Forms[Forms_count])
	if(flag == 0)
	{
		strcat(form, "_training.xlsx"); 
		file_pointer = fopen(form, "w");// To open the file in write mode 
		if(file_pointer == NULL)
		{
			printf("File open not successfull\n");
		}
		int field_count; //Integer variable to take user input for number of fields
		printf("Enter the number of fields required: ");
		scanf("%d", &field_count);
		Employee_training_data *lastnode = NULL;
		first_field[Forms_count] = NULL;

		//To take user input for field name and store it to excel sheet
		for(int i = 0;i < field_count;i++)
		{
			//Allocating dynamic memory for each field in training registration form
			Employee_training_data *newnode = (Employee_training_data *)malloc(sizeof(Employee_training_data));
			__fpurge(stdin);
			printf("Enter field name: ");
			scanf("%[^\n]%*c", newnode->fields);
			newnode->link = NULL;
			fprintf(file_pointer, "%s\t", newnode->fields);//To store content of newnode->fields to file

			//To create linked list between each fields of one training regsitration form
			if(first_field[Forms_count] == NULL)
			{
				first_field[Forms_count] = newnode;
			}
			else
			{
				lastnode->link = newnode;
			}
			lastnode = newnode;
		}
		fprintf(file_pointer, "\n");
		fclose(file_pointer); //To close the file
		Forms_count++; //To increment Forms_count
		main();
	}
	else
	{
		printf("\nInfo: File is already present with given name\n\n");
		main();
	}
}
