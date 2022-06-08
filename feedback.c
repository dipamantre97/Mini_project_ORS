#include"feedback.h"
#include"registration.h"

pthread_mutex_t lock;   //declaring mutex variable

int employee_id(char* user_buffer_empid,int *option); //employee_id function declaration
int employee_name(char *user_buffer_name);   //employee_name function declaration
int employee_email(char *user_buffer_email);  //employee_email function declation
int employee_reporting_mgr(char *user_buffer_reporting_mgr);   //employee_rporting_magr function declaration
int employee_feedback(char *user_buffer_feedback);        //employee_feedback function declaration


void *feedback_thread(void *t1)        //thread definition
{
	pthread_mutex_lock(&lock); //to acquire the lock
	char form[SIZE];  //char array to store one feedback form name
	char user_buffer1[SIZE],user_buffer2[SIZE],user_buffer3[SIZE],user_buffer4[SIZE],user_buffer5[SIZE];  //buffer to copy the user inputted emp_id,emp_name,emp_emai,reporting_mgr,feedback from the user
	int *option = (int *)t1; 
	strcpy(form, Forms[*option - 1]);  //copying name of the training name to form
	int return_value_id = 0, return_value_name = 0,return_value_email = 0,return_value_reporting_mgr = 0,return_value_feedback = 0;

	return_value_id=employee_id(user_buffer1,option);
	if(return_value_id==1)        //checking if the user is not registered for the training
	{
		pthread_mutex_unlock(&lock);  //to release the lock
		pthread_exit(NULL);   //to exit from the thread
	}

	return_value_name=employee_name(user_buffer2);   //calling employee_name function to take emp_name from the user
	if(return_value_name==1)        //checking if the user has entered three times Invalid emp_name
	{
		pthread_mutex_unlock(&lock);  //to release the lock
		pthread_exit(NULL);   //to exit from the thread
	}

	return_value_email=employee_email(user_buffer3);  //calling emloyee_email function to take emp_email fromthe user
	if(return_value_email==1)        //checking if the user has enetered three times Invalid email_id
	{
		pthread_mutex_unlock(&lock);  //to release the lock
		pthread_exit(NULL);   //to exit from the thread
	}

	return_value_reporting_mgr=employee_reporting_mgr(user_buffer4);   //calling the employee_reporting_mgr function to take retporting manager name
	if(return_value_reporting_mgr==1)        //checking if the user haa enetered three times Invalid reporting_mgr name
	{
		pthread_mutex_unlock(&lock);  //to release the lock
		pthread_exit(NULL);   //to exit from the thread
	}

	return_value_feedback=employee_feedback(user_buffer5);   //calling the employee_feedback function to take feedback from the user		
	if(return_value_feedback==1)        //checking if the user has used special characters while giving feedback for three times
	{
		pthread_mutex_unlock(&lock);  //to release the lock
		pthread_exit(NULL);   //to exit from the thread
	}

	strcpy(form, Forms[*option - 1]);   //copying the training name to form
	strcat(form, "_training_feedback.xlsx");     //concatenating the _training.xlsx into form1
	FILE *fp2 = fopen(form, "a");            //opening the feedback xl sheet in append mode
	if(fp2==NULL)           //checking if the file is opened or not
	{
		printf("Cannot open file\n");
	}
	printf("Your response has been recorded\n\n");

	fprintf(fp2,"%s\t%s\t%s\t%s\t%s\n",user_buffer1,user_buffer2,user_buffer3,user_buffer4,user_buffer5); //storing user details into feedback xl sheet

	fclose(fp2); //to close the file
	pthread_mutex_unlock(&lock);     //to release the lock
}


void feedback(int option)
{
	char filename[SIZE]; //An array of character to store the one trainig form name
	char form_name[SIZE]; //An arraay of characters to store the one training feedback form name
	char c;  //to store the character    
	int line_count=0;        //to store the line_count
	strcpy(filename,Forms[option-1]);     //copying the conducted training form name 
	strcat(filename,"_training.xlsx");   //concatenating the form name with _training.xlsx
	FILE *fp=fopen(filename,"r");       //opening the file in read mode
	if(fp==NULL)                       //checking if file is exists or not
	{
		printf("File does not exists\n\n");
	}
	else
	{
		for (c = getc(fp); c != EOF; c = getc(fp))     //counting the number of lines in that conducted training sheet 
		{
			if (c == '\n') // Increment count if this character is newline
				line_count = line_count + 1;  
		}
	}
	fclose(fp);

	if(line_count==1) ////checking the conducted training xl file,checking if only form is created with no field enetred by the user
	{
		printf("Only form is created no entries are made\n\n");
		main();
	}
	else
	{
		strcpy(form_name,Forms[option-1]);   //copying conducted training form name
		strcat(form_name,"_training_feedback.xlsx");
		FILE *fp1=fopen(form_name,"w");     //opening the _feedback.xlsx file in write mode
		if(fp1==NULL)    //checking if file exists or not
		{
			printf("File does not exists\n\n");
		}
		else
		{
			Employee_training_feedback user={"emp_id","emp_name","emp_email","reporting_mgr","feedback"}; //initializing the field names using the structure varible

			fprintf(fp1,"%s\t%s\t%s\t%s\t%s\n",user.emp_id,user.emp_name,user.emp_email,user.reporting_mgr,user.feedback); //printing the field names into _feedback.xlsx file
			fclose(fp1); //closing the file
			pthread_t thread[3];  //creating threee threads to take three i/p from user
			pthread_create(&thread[0], NULL, feedback_thread, (void *)&option); //to take user1 i/p
			pthread_create(&thread[1], NULL, feedback_thread, (void *)&option); //to take user2 i/p
			pthread_create(&thread[2], NULL, feedback_thread, (void *)&option); //to take user3 i/p
			pthread_join(thread[0], NULL); //wait for the thread1 to complete
			pthread_join(thread[1], NULL);  //wait for the thread2 to complete
			pthread_join(thread[2], NULL);   //wait for the thread3 to complete
			main();
		}
	}
}



int employee_id(char* user_buffer_empid,int *option)
{

	char form[SIZE]; //char array to store one training form name
	char form1[SIZE];  //char array to store one feedback form name
	char emp_id[SIZE];     //char array to store user inputted emp_id to takefeedback
	char buffer1[SIZE][SIZE];  //buffer to store all the fields in the training xl file
	char buffer2[SIZE][SIZE];  //buffer to store only the emp_id fron that traing xl file
	char buffer3[SIZE][SIZE];  //buffer to store all the fields in the feedback xl sheet
	char buffer4[SIZE][SIZE];   //buffer to store the only the emp_id's present in the feedback xl sheet
	strcpy(form, Forms[*option - 1]);  //copying name of the training name to form
	strcat(form, "_training.xlsx");   //concatenating _training.xlsx into form
	FILE *file_pointer = fopen(form, "r");   //opening the file in read mode
	int i = 0,j = 0,m = 0,flag = 0;

	printf("Enter the Emp_id:");      //taking the emp_id from user
	__fpurge(stdin);                 //clear the buffer
	scanf("%s",emp_id);

	if(emp_id[0] == '0' && emp_id[1] == '2')     //checking if the second digit in emp_id is 0  
	{
		while(emp_id[m] != '\0')          //checking thefor the valid emp_id
		{
			if((emp_id[m] >= 47) &&  (emp_id[m] <= 58))
			{
				m++;
			}
			else
			{
				printf("Invalid emp-id\n");
				return 1;
			}
		}
	}
	else
	{
		printf("Invalid emp-id\n");
		return 1;
	}

	while(!feof(file_pointer))    //Reading whole conducted training xl file 
	{
		fscanf(file_pointer,"%s\t",buffer1[i]);
		if(buffer1[i][0]== '0')   //checking for emp_id 
		{
			strcpy(buffer2[j],buffer1[i]);    //storing that emp_id into another buffer
			j++;
		}
		i++;
	}
	fclose(file_pointer);
	for(int x=0;x<j;x++)
	{
		if(strcmp(emp_id,buffer2[x]) == 0)   //to comapare the user enetred emp_id with the training registered emp_id's
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		printf("This user has not registered for the training\n\n");
		return 1;
	}
	else
	{
		int k=0,l=0,flag1=0;
		strcpy(form1, Forms[*option - 1]);  //copying name of the training name to form1
		strcat(form1, "_training_feedback.xlsx");   //concatenating _training_feedback.xlsx into form1
		FILE *file_pointer1 = fopen(form1, "r");   //opening the file in read mode
		while(!feof(file_pointer1))    //Reading whole conducted feedback xl file 
		{
			fscanf(file_pointer1,"%s\n",buffer3[k]);
			if(buffer3[k][0]== '0')   //checking for emp_id 
			{
				strcpy(buffer4[l],buffer3[k]);    //storing that emp_id into another buffer
				l++;
			}
			k++;
		}

		fclose(file_pointer1);
		for(int z=0;z<l;z++)
		{
			if(strcmp(emp_id,buffer4[z]) == 0)  //checking if the user has already given the feedback
			{
				flag1=1;
				break;
			}
		}
		if(flag1==1)
		{
			printf("This user has already given the feedback\n\n");
			return 1;
		}
		else
		{

			strcpy(user_buffer_empid, emp_id);             //storing the emp_id into buffer
		}

	}
}



int employee_name(char* user_buffer_name)   //function definition to take emp_name from user
{
	char name[SIZE];
	int buffer_size = 0, k = 0, flag1 = 0;
	static int count = 0;
	printf("Enter the emp_name:"); 
	__fpurge(stdin);            //to clear the buffer
	scanf("%[^\n]%*c",name);      //to take emp_name from the user

	while(name[k] != '\0')
	{
		buffer_size++;
		if(buffer_size > MAX_LEN)    //checking for the max characters to take for the name
		{
			printf("Buffer size is exceeded\n\n");
			employee_name(user_buffer_name);    //if size exceeds calling the function to again take the emp_name
		}
		if(name[k] == ' ' || (name[k] >= 65 && name[k] <= 90) || (name[k] >= 97 && name[k] <=122)) //checking the user emp_name contains only the ' ' and capital and small letters 
		{
			k++;
		}
		else
		{
			flag1 = 1;
			break;
		}
	}
	if(flag1 == 0)
	{
		strcpy(user_buffer_name,name); //copying the user inputted emp_name to buffer
	}
	else
	{
		if(count != 2)          //checking if the user has entered invalid name more than 2 times
		{
			count++;
			printf("No special characters are allowed\n\n");
			employee_name(user_buffer_name);  //calling the function again to enter the valid emp_name
		}
		else
		{
			printf("You entered three times Invalid name\n\n");
			return 1;
		}
	}
}


int employee_email(char* user_buffer_email)
{
	char Email_id[SIZE];
	int i = 0,flag = 0;
	static int count = 0;

	printf("Enter the email_id:");
	__fpurge(stdin);
	scanf("%[^\n]%*c",Email_id);      // to take the email_id from the user

	if(Email_id[0]>=97 && Email_id[0]<=122)  //checking if the first character in the email-id is lowercase letter or not
	{
		while(Email_id[i] != '@')     //cheking if the email-id before @ conatains only lowercase and '.'
		{
			if((Email_id[i]>=97 && Email_id[i]<=122) || Email_id[i] == '.')
			{ 
				i++;
			}
			else
			{
				flag = 1;
				break;
			}
		}

		if(flag == 0)
		{
			if(strstr(Email_id, "@thundersoft.com") )  //checking for @thundersoft.com in that user entered emeil id
			{
				strcpy(user_buffer_email, Email_id);
			}
			else
			{

				if(count != 2)    //checking if the user has entered invaid email-id more than 2 times
				{
					count++;
					printf("Invalid email-id,should be @thundersoft.com\n\n");
					employee_email(user_buffer_email);  //calling the function again to enter the valid emp_name
				}
				else
				{
					printf("You entered three times Invalid email_id\n\n");
					return 1;
				}
			}
		}
		else
		{
			if(count != 2) //checking if the user entered Invlaid email-id more than 2 times
			{
				count++;
				printf("Invalid email_id,only lowercase and '.' are allowed\n\n");
				employee_email(user_buffer_email);  //calling the function again to enter the valid emp_name
			}
			else
			{
				printf("You entered three times Invalid email_id\n\n");
				return 1;
			}

		}
	}
	else
	{
		if(count != 2) //checking if the user has enetred Inavlid email-id more than 2 times
		{
			count++;
			printf("First character must be lowercase letter\n\n");
			employee_email(user_buffer_email);  //calling the function again to enter the valid emp_name
		}
		else
		{
			printf("You entered three times Invalid email_id\n\n");
			return 1;
		}
	}
}


int employee_reporting_mgr(char* user_buffer_reporting_mgr)
{
	char reporting_manager[SIZE];

	printf("Enter the Reporting manager name:");
	__fpurge(stdin);
	scanf("%[^\n]%*c",reporting_manager);          //to take reporting manager namefrom the user


	int  k = 0, flag1 = 0,buffer_size = 0;
	static int count = 0;

	while(reporting_manager[k] != '\0') 
	{
		buffer_size++;
		if(buffer_size > MAX_LEN) //checking the max charcaters that that entered by the user
		{
			printf("Buffer size is exceeded\n\n"); 
			employee_reporting_mgr(user_buffer_reporting_mgr); //calling the function again to take valid reporting manager anme
		} //checking for the ' ' capital and small lettres 
		if(reporting_manager[k] == ' ' || (reporting_manager[k] >= 65 && reporting_manager[k] <= 90) || (reporting_manager[k] >= 97 && reporting_manager[k] <=122))
		{ 
			k++;
		}
		else
		{
			flag1 = 1;
			break;
		}
	}
	if(flag1 == 0)
	{
		strcpy(user_buffer_reporting_mgr,reporting_manager); //copying the user inputted reporting manager to buffer
	}
	else
	{
		if(count != 2)  //checking if the user has entered invalid reporting-manager more than 2 times
		{
			count++;
			printf("No special characters are allowed\n\n");
			employee_reporting_mgr(user_buffer_reporting_mgr);    //calling the function again to enter the valid reporting manager name
		}
		else
		{
			printf("You entered three times Invalid Reporting manager name\n\n");
			return 1;
		}
	}
}


int employee_feedback(char *user_buffer_feedback)
{
	char feedback_training[SIZE];

	printf("Enter the Feedback for the training:");
	__fpurge(stdin);
	scanf("%[^\n]%*c",feedback_training);   //to take feedback from the user
	int feedback_count=0,k = 0, flag1 = 0;
	static int count = 0;

	while(feedback_training[k] != '\0')
	{
		feedback_count++;
		if(feedback_count> SIZE) //checking max characeter that canbe entered by the usre for giving feedback
		{
			printf("Buffer Size is exceeded\n");
			employee_feedback(user_buffer_feedback);
		} //checking for  ' ' small and capital letters
		if(feedback_training[k] == ' ' || (feedback_training[k] >= 65 && feedback_training[k] <= 90) || (feedback_training[k] >= 97 && feedback_training[k] <=122))
		{
			k++;
		}
		else
		{
			flag1 = 1;
			break;
		}
	}
	if(flag1 == 0)
	{
		strcpy(user_buffer_feedback,feedback_training);   //copying the user inputted feedback into buffer
	}
	else
	{
		if(count != 2)    //checking if the user has entered special characters while giving feedback more than 2 times
		{
			count++;
			printf("No special characters are allowed\n\n");
			employee_feedback(user_buffer_feedback);  //calling the function again to enter the valid feedback(i.e no special characters are allowed)
		}
		else
		{
			printf("You entered three times special characetrs while giving feedback \n\n");
			return 1;
		}
	}
}
