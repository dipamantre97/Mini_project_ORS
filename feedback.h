/*****************************************DESCRIPTION*******************************************************************/

/*

1. Name of the module                           : feedback
2. Date of creation                             : 27/5/2022
3. Author of Module                             : Tejaswini S P
4. Description of module                        : The purpose of this module is to take the feedback from the user

5. Different functions supported in this module : feedback(int)
6.Github link                                   : https://github.com/Harishchiluka0111/Mini_ORS_1_june
*/

/**********************************************************************************************************************/
/**************************HEADER FILES*****************************/
#include<pthread.h>
#include"main.h"
/************************MACROS**********************************/
#define SIZE 256

/*************************structure for this module**************/
typedef struct employee_f
{
char emp_id[MAX_LEN];
char emp_name[MAX_LEN];
char emp_email[MAX_LEN];
char reporting_mgr[MAX_LEN];
char feedback[SIZE];
}Employee_training_feedback;


/*************************FUNCTION PROTOTYPES**********************/
void feedback(int option);  //to record the feedback from the user and store the data in the .xlsx file
