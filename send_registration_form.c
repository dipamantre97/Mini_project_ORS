#define _GNU_SOURCE

#include"registration.h"
#include"send_registration_form.h"

//*******************************************Send registration form**********************************************
int Form_option;
pthread_mutex_t lock;

void *thread_handler_1(void *first_field)
{
	pthread_mutex_lock(&lock); //Acquiring lock
	char form[COL_SIZE];
	char buffer[ROW_SIZE][COL_SIZE];
	Employee_training_data *temp = (Employee_training_data *)first_field;
	strcpy(form, Forms[Form_option - 1]); //Copy string from source to destination
	strcat(form, "_training.xlsx"); //string concatenation
	FILE *file_pointer1 = fopen(form, "r"); //To open file in read mode
	int index = 0,i = 0, j = 0;
	char buffer_id[ROW_SIZE][COL_SIZE], buffer1_id[ROW_SIZE][COL_SIZE];

	//To store all employee id into one buffer
	while(!feof(file_pointer1))
	{
		fscanf(file_pointer1, "%s\t", buffer_id[i]);
		if(buffer_id[i][0] == '0')
		{
			strcpy(buffer1_id[j], buffer_id[i]);
			j++;
		}
		i++;
	}
	fclose(file_pointer1); //To close file

	FILE *file_pointer = fopen(form, "a"); //To open file in append mode
	//To take user input for employee details
	while(temp != NULL)
	{
		char data[MAX_LEN];
		printf("Enter %s: ", temp->fields);
		__fpurge(stdin);
		scanf("%[^\n]%*c", data);

		//To take user inputs for Email-id
		if(strcasestr(temp->fields, "mail") != NULL) 
		{
			int index1 = 0, flag = 0;
			if(data[0] >= 97 && data[0] <= 122)
			{
				while(data[index1] != '@')
				{
					if(data[index1] == '.' || (data[index1] >= 65 && data[index1] <= 90) || (data[index1] >= 97 && data[index1] <= 122))
					{
						index1++;
					}
					else
					{
						flag = 1;
						break;
					}
				}
			}
			else
			{
				flag = 1;
			}

			//Condition to check whether Email-id has @thundersoft.com
			if(flag == 0 && (strstr(data, "@thundersoft.com") != NULL))
			{
				strcpy(buffer[index], data);
				temp = temp->link;
				index++;
				continue;
			}
			else
			{
				printf("\nINFO: Please enter valid Email-id\n\n");
				continue;
			}
		}

		//To take user input for Employee id
		else if(strcasestr(temp->fields, "id") != NULL)
		{
			int flag = 0, flag1 = 0, index1 = 0;

			//To check Employee-id is already present or not
			for(int i = 0;i < j;i++)
			{
				if(strcmp(data, buffer1_id[i]) == 0)
				{
					flag = 1;
					break;
				}
			}
			//Condition to check Employee id starts with '0'
			if(data[0] == '0' && data[1] == '2')
			{
				while(data[index1] != '\0')
				{
					if(data[index1] >= 48 && data[index1] <= 57)
					{
						index1++;
					}
					else
					{
						flag1 = 1;
						break;
					}
				}
			}
			else
			{
				flag1 = 1;
			}
			if(flag == 0)
			{
				if(flag1 == 0 && index1>6)
				{
					strcpy(buffer[index], data);
					index++;
					temp = temp->link;
					continue;
				}
				else
				{
					printf("\nINFO: Please enter valid Employee-id\n\n");
					continue;
				}
			}
			else
			{
				printf("\nINFO: Entered employee-id is already present\n\n");
				fclose(file_pointer); //To close file
				pthread_mutex_unlock(&lock); //To release the lock acquired
				pthread_exit(NULL); //To terminate the thread execution
			}
		}
		else
		{
			int index1 = 0, flag = 0;

			//To check string has no special characters other than space
			while(data[index1] != '\0')
			{
				if(data[index1] == ' ' || (data[index1] >= 65 && data[index1] <= 90) || (data[index1] >= 97 && data[index1] <=122))
				{
					index1++;
				}
				else
				{
					flag = 1;
					break;
				}
			}
			//Condition to check whether buffer size is not more than MAX_LEN
			if(index1 >= MAX_LEN)
			{
				printf("\nError: Buffer exceeded\n\n");
				continue;
			}
			if(flag == 0)
			{
				strcpy(buffer[index], data);
				index++;
				temp = temp->link;
				continue;
			}
			else
			{
				printf("\nError: No special characters allowed\n\n");
				continue;
			}
		}
	}
	//To store the employee details to excel sheet
	printf("\nInfo: Employee details entered successfully\n\n");
	for(int j = 0;j < index;j++)
	{
		fprintf(file_pointer, "%s\t", buffer[j]);
	}
	fprintf(file_pointer, "\n");
	fclose(file_pointer); //To close file
	pthread_mutex_unlock(&lock); //To release the acquired lock
}

void send_training_registration_form(Employee_training_data **first_field)
{
	//int form_option;
	int count = 0;
	if(Forms_count > 0)
	{
		// To list all the trainings available
		printf("\nAvailable trainings are: \n");
		for(int i = 0;i < Forms_count;i++)
		{
			printf("%d. %s\n", i+1, Forms[i]);
		}
		while(1)
		{
			printf("Enter the option to select particular training registration form: ");
			scanf("%d", &Form_option);
			if(Form_option <= Forms_count)
			{
				pthread_t thread[THREAD_COUNT];
				//Create threads and take three different user inputs
				pthread_create(&thread[0], NULL, thread_handler_1, (void *)first_field[Form_option - 1]);
				pthread_create(&thread[1], NULL, thread_handler_1, (void *)first_field[Form_option - 1]);
				pthread_create(&thread[2], NULL, thread_handler_1, (void *)first_field[Form_option - 1]);
				pthread_join(thread[0], NULL); //To wait until particular thread termaination
				pthread_join(thread[1], NULL);
				pthread_join(thread[2], NULL);
				main();
			}
			else
			{
				count++;
				if(count != 3)
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
		printf("No trainings available\n");
		main();
	}
}
