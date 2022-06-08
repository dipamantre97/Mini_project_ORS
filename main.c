
/************************Main module implementation********************/
#include"main.h" //headerfile inclusion
void main()
{
	
	int count=1;			//local variable for invalid option counting
	
	char option;			// local variable for option choosing from menu
	
	printf(" Main menu \n");
	
	printf(" 1.Training \n 2.Voting \n 3.Exit\n");
	
	
	void (*fp[3])()={training,voting,exit}; //Array of function pointers 
	 
	while(1)
	  {
	 
	  printf("Enter the option\n");
	 
	   scanf(" %c",&option);
	
	  	if (count<3)
	  	{
	  		switch(option)
	  		{
	  			case '1': fp[option - 49]();break; //function call for training
	  			case '2': fp[option - 49]();break; //function call for votiong
	  			case '3': exit(0);		  //terminating the application
	  			default:count++;
	  			printf("Error:Invalid option\n");break;      	//counting the invalid options 
	  		}
	  	}
	  	else{
			printf("Error: user entered invalid option 3 times\n");
			exit(0);
		}	  	
	    }


}

/**************************************Creating Training Menu**************************/
void training()
{
	char option_t;			// local variable for option choosing from menu	
	
	int option_count=1;		//local variable for invalid option counting
	
	printf(" Training Menu\n");
	
	printf(" 1.Registration\n 2.Feedback\n *.Main menu\n");
	
	void (*fp_t[2])()={registration,feedback_module};//feedback}; //Array of function pointers 
	 	
	  while(1)
	  {
	  printf("Enter the option\n");
	 
	   scanf(" %c",&option_t);
	
	  	if (option_count<3)
	  	{
	  		switch(option_t)
	  		{
	  			case '1': fp_t[option_t - 49]();break; // function call for training_module
	  			case '2': fp_t[option_t - 49]();break;   // function call for feedback
	  			case '*': main();			// going backto main menu
	  			default:option_count++;
	  			printf("Error:Invalid option\n");break;		//counting the invalid options 
	  		}
	  	}
	  	else{
			printf("Error: user entered invalid option 3 times\n");
			main();
		}	  	
	    }
}
