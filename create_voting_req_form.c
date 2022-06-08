#include"voting_request.h"

/************ function defination of creating voting request form**************************/

void create_voting_req_form(Vote **root)
{
	char form_name[FORM_LEN];                                           //user requested form name                                       
	int flag = 0;
	int count_fields=0;                                                // to enter no of fields base of user
	FILE *file_pointer = NULL;
	printf("Enter the form name: ");                                  //scan the form name
	scanf("%s", form_name);
	for(int i = 0;i < Count_forms; i++)                              // to check form already exists or not
	{
		if(strcasecmp(Forms[i], form_name) == 0)
		{
			flag = 1;
			printf("file already present\n");
			main();
		}
	}

	strcpy(Forms[Count_forms], form_name);                      //for coping forms
	if(flag == 0)
	{
		strcat(form_name, "_request.xlsx");                 // adding file extention in file name
		file_pointer = fopen(form_name, "w");              // to open form file
		if(file_pointer == NULL)                           //if fopen failed
		{
			printf("File open not successfull\n");
		}

		printf("Enter the number of fields required: ");  // to enter no of fields base on users choice
		scanf("%d", &count_fields);      
		root[Count_forms] = NULL;	                 //root pointer of linklist
		Vote *lastnode = NULL;
		for(int i = 0;i < count_fields;i++)
		{

			Vote *newnode = NULL;
			newnode=(Vote*)malloc(sizeof(Vote));
			printf("Enter field name: ");           
			__fpurge(stdin);                                 //to clear buffer
			scanf("%[^\n]s", newnode->fields);               // upto new line it will take input
			newnode->link = NULL;

			fprintf(file_pointer, "%s\t", newnode->fields);       //to write field data in file
			if(root[Count_forms] == NULL)                        // if linklist is empty add newnode as root pointer
			{
				root[Count_forms] = newnode;

			}
			else                                                // if list is not empty
			{      
				lastnode->link = newnode;                 // to add at last in linklist
			}
			lastnode = newnode;
		}	
		fprintf(file_pointer,"\n");
	}

	fclose(file_pointer);
	Count_forms++;
	main();

}


