#define _GNU_SOURCE

//Header files inclusion
#include"voting_response.h"

/******************************Function definition of voting_response()***************************************************************************/

pthread_mutex_t lock;                                                            //mutex lock declarartion
int form_option;                                                                 //global variable for selecting voting forms

void *thread_handler(void *root)
{
	pthread_mutex_lock(&lock);                                               //acquiring the lock

	char form[FORM_LEN];                                                      //for storing form name
	strcpy(form, Forms[form_option - 1]);                                    //copy forms of particular index name to form character array
	strcat(form, "_request.xlsx");                                           //concatenate the form name with .xlsx

	char buffer_id[ROW_SIZE][COL_SIZE], buffer1_id[ROW_SIZE][COL_SIZE];      //buffers for storing all user id's
	int i = 0, j = 0; 	                                                 //for storing index value of Buffers
	FILE *file_pointer1 = fopen(form, "r");                                  //opens a particular file in read mode

	while(!feof(file_pointer1))                                              //loop until it reaches end of file
	{
		fscanf(file_pointer1, "%s\t", buffer_id[i]);                     //reading all content file to buffer
		if(buffer_id[i][0] =='0')                                        //checking whether fields have id
		{
			strcpy(buffer1_id[j], buffer_id[i]);                     //if id present copy all id's to another buffer
			j++;
		}
		i++;
	}
	fclose(file_pointer1);                                                   //close file opened in read mode

	char buffer[ROW_SIZE][COL_SIZE];                                         //Buffer to store the user details after every thread execution
	int buf_index = 0;                                                       //To store index value of buffers
	FILE *file_pointer = fopen(form, "a");                                   //opens a particular form in append mode 
	Vote *temp = (Vote *)root;                                               //typecasting from void* to int*

	while( temp != NULL)                                                     //Looping untill temp not equal to NULL
	{
		char str[FIELD_LEN];                                            //To take user inputs for created fields
		printf("Enter %s: ", temp->fields);
		__fpurge(stdin);
		scanf("%[^\n]%*c", str);

		if(strcasestr(temp->fields, "mail") != NULL)                    //condition to check user created fields has employee mail id
		{
			int i = 0, flag = 0;
			if(str[0] >= 97 && str[0] <= 122)                       //condition to check user entered mail id starts with lower case letter
			{
				while(str[i] != '@')
				{
					if(str[i] == '.' || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))  //condition to check whether mail-id has only letters and ., no special characters
					{
						i++;
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
			if(flag == 0 && (strstr(str, "@thundersoft.com") != NULL))        //Condition to check whether Email-id has @thundersoft.com
			{
				strcpy(buffer[buf_index], str);                          //copying user input to buffer
				temp = temp->link;                                       //move to next node
				buf_index++;                                             //incrementing value of buffer index
				continue;                                               //will check the condition again for next filed
			}
			else
			{
				printf("\nINFO: Please enter valid Email-id\n\n");
				continue;
			}
		}

		else if(strcasestr(temp->fields, "id") != NULL)                          //condition to check user created fields has employee id
		{
			int flag = 0, flag1 = 0, index = 0;
			for(int i = 0;i < j;i++)                                        //To check Employee-id is already present or not
			{
				if(strcmp(str, buffer1_id[i]) == 0)
				{
					flag = 1;
					break;
				}
			}
			if(str[0] == '0' && str[1] == '2')                             //condition to check employee id starts with 0 and then 2
			{
				while(str[index] != '\0')
				{
					if(str[index] >= 48 && str[index] <= 57)     //Condition to check Employee id has special characters
					{
						index++;
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
				if(flag1 == 0 && index>6)
				{
					strcpy(buffer[buf_index], str);                          //copying user input to buffer
					temp = temp->link;                                       //move to next node 
					buf_index++;                                             //incrementing value of buffer index
					continue;                                               //will check the condition again for next filed
				}
				else
				{
					printf("\nINFO: Please enter valid Employee-id\n\n");
					continue;
				}
			}
			else
			{
				printf("\nINFO: Current user already given response\n\n");
				fclose(file_pointer);                                           //for closing a file opened in append mode
				pthread_mutex_unlock(&lock);                                    //for releasing the mutex lock acquired
				pthread_exit(NULL);                                            //forterminating the thread execution
			}
		}

		else
		{
			int index = 0, flag = 0;
			while(str[index] != '\0')                                                            
			{
				if(str[index] == ' ' || (str[index] >= 65 && str[index] <= 90) || (str[index] >= 97 && str[index] <= 122)) //To check string has no special characters other than space
				{
					index++;
				}
				else
				{
					flag = 1;
					break;
				}
			}

			if(index >= FIELD_LEN)        //Condition to check whether buffer size is not more than field length set
			{
				printf("\nError: Buffer exceeded\n\n");
				continue;
			}
			if(flag == 0)
			{
				strcpy(buffer[buf_index], str);                          //copying user input to buffer
				temp = temp->link;                                       //move to next node
				buf_index++;                                             //incrementing value of buffer index
				continue;                                               //will check the condition again for next filed
			}
			else
			{
				printf("\nError: No special characters allowed\n\n");
				continue;
			}
		}
	}

	printf("\nInfo: Employee details are recorded successfully\n\n");         //To store the employee details to excel sheet
	for(int i = 0;i < buf_index;i++)
	{
		fprintf(file_pointer, "%s\t", buffer[i]);
	}
	fprintf(file_pointer, "\n");
	fclose(file_pointer);                                                    //To close file
	pthread_mutex_unlock(&lock);                                             //To release the acquired lock
}

void voting_response(Vote **root)
{
	int flag = 0,i = 0;                                                //flag to count number of invalid options
	if(Count_forms > 0)                                                //Checking for count greater than 0 to display created forms
	{
		printf("\nAvailable voting forms are: \n");                  
		for(i = 0; i < Count_forms; i++)                           //Iterating over the Count for displaying available voting forms
		{
			printf("%d. %s\n", i + 1, Forms[i]);
		}
		while(1)                                                  //to make this process alive untill program terminates
		{
			printf("\nPlease select from available voting forms for providing response : ");
			scanf("%d", &form_option);
			if(form_option <= Count_forms)                                                     //checks no.of forms option is greater than user option
			{
				pthread_t thread[3];
				pthread_create(&thread[0], NULL, thread_handler, (void *)root[form_option - 1]);   //creating thread1 with handler function thread handler and passing address of form option as a pointer
				pthread_create(&thread[1], NULL, thread_handler, (void *)root[form_option - 1]);   //creating thread1 with handler function thread handler and passing address of form option as a pointer
				pthread_create(&thread[2], NULL, thread_handler, (void *)root[form_option - 1]);   //creating thread1 with handler function thread handler and passing address of form option as a pointer
				pthread_join(thread[0], NULL);                                             //wait untill thread1 completes its execution
				pthread_join(thread[1], NULL);                                             //wait untill thread2 completes its execution
				pthread_join(thread[2], NULL);	                                           //wait untill thread3 completes its execution
				main();                                                                    //Back to main menu after giving response
			}
			else
			{
				flag++;
				if(flag != 3)                                                           //checks for count of invalid option
				{
					printf("\nINVALID OPTION : Please enter valid option\n");
				}
				else
				{
					printf("\nINFO: User entered invalid option 3 times\n\n");
					main();                                                           //back to main menu if user enters invalid option three times
				}
			}
		}
	}
	else
	{
		printf("\nINFO: No voting forms are vailable\n\n");
		main();
	}
}

