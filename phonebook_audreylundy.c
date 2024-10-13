#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*Audrey lundy*/

//Struct to hold contact info. 
	struct Phonebook
	{
		char f_name[20];
		char l_name[20];
		char number[15];
	};

//add_friend function which adds contacts to phonebook
void add_friend(struct Phonebook **contacts, int *num_people)
{
	//Increasing the number of people and reallocating memory for new contact
	(*num_people)++;
	*contacts= realloc(*contacts, (*num_people) * sizeof(struct Phonebook));
	if (*contacts==NULL)
	{
		printf("Failed");
		exit(1);
	}
	//Asking for information about new contact and storing details in position of new memory 
	printf("First name: ");
	scanf("%s",(*contacts)[*num_people-1].f_name);
	printf("Last name: ");	
	scanf("%s",(*contacts)[*num_people-1].l_name);
	printf("Phone number: ");
	scanf("%s",(*contacts)[*num_people-1].number);
	printf("Record added in phonebook\n");
}
//Delete friend function to delete a contact
void del_friend(struct Phonebook **contacts, int *num_people)
{
	//declaring variables and asking which person the user would like to delete
	char del_fname[20];
	char del_lname[20];
	printf("First name:");
	scanf("%s",del_fname);
	printf("Last name:");
	scanf("%s",del_lname);
	
	/*For loop to go through contacts and check if the first and last name requested to be deleted are found. If so, "found" variable is changed to 
	1 and the contact is changed to the last element and deleted. Reallocation of memory to remove contact*/ 
	int found=0;
	for (int i=0; i< *num_people;i++) {
		if (strcmp((*contacts)[i].f_name,del_fname)==0 && strcmp((*contacts)[i].l_name,del_lname)==0)
		{
		found=1;
		(*contacts)[i]=(*contacts)[(*num_people)-1];
		(*num_people)--;
		*contacts=realloc(*contacts,(*num_people)*sizeof(struct Phonebook));
		printf("Record deleted from the phone book\n");
		break;
	}	
	}
		
}
//Print pb function to print the phonebook
void print_pb(struct Phonebook *contacts, int num_people)
{
	//For loop to iterate through each entry and prints the info.
	printf("Phone Book Entries: \n");
	for (int i=0;i<num_people;i++)
	{
		printf("\n%s %s %s",contacts[i].f_name,contacts[i].l_name,contacts[i].number);
	}
	
}


//Function to sort names by first name
void sort_fnames(struct Phonebook *contacts, int num_people)
{
	char temp[20];
	//Nested for loop and if statement to iterate through the first names of each contact and rearrange the names.
	for (int i=0;i<num_people-1;i++)
	{
		for (int j=0;j<num_people-1;j++)
		{
			if (strcmp(contacts[j].f_name, contacts[j+1].f_name)>0)
			{
				strcpy(temp,contacts[j].f_name);
				strcpy(contacts[j].f_name, contacts[j+1].f_name);
				strcpy(contacts[j+1].f_name,temp);
				printf("Names have been sorted by first name.");
				
			}	
		}
		
	}
	
}

/*Find_num function to find the number of a given contact. For loop to iterate through number of people and if statement to compare the requested strings to each contact. If found it will print their name and number. 
If not it will print unable to find. */
void find_num(struct Phonebook *contacts, int num_people)
{
	char fi_name[20];
	char la_name[20];
	printf("Enter first name of contact you'd like to find: ");
	scanf("%s",fi_name);
	printf("Enter last name of contact you'd like to find: ");
	scanf("%s",la_name);
	int found=0;
	for (int i=0; i< num_people;i++) 
	{
		if (strcmp((contacts)[i].f_name,fi_name)==0 && strcmp((contacts)[i].l_name,la_name)==0)
		{
			printf("%s %s's phone number is : %s\n",fi_name,la_name,contacts[i].number);
			int found=0;
			break;
		}
	if (!found)
	{
		printf("Unable to find contact\n");
	}
	}

}

//Random_select function to randomly pick a person from phonebook. Uses rand function to generate a contact within the number of people.
void random_select(struct Phonebook *contacts, int num_people)
{
	srand(time(NULL));
	int random_ind= rand() % num_people;
	printf("You should call %s %s: %s\n", contacts[random_ind].f_name,contacts[random_ind].l_name,contacts[random_ind].number);
}

//Function to delete entire phonebook. Free() function to de-allocate space 
void del_every1(struct Phonebook **contacts, int *num_people)
{
	free(*contacts);
	*contacts=NULL;
	*num_people=0;
	printf("Your phonebook has been deleted\n");
}


//Store function to store the phonebook content into a file
void store(struct Phonebook *contacts, int num_people, const char *filename)
{
	char default_locat[]= "phonebook.txt";
	const char *inp_filename= filename;
	if (filename[0]=='\0')
	{
		inp_filename=default_locat;
	}
	
	//open stream
	FILE *fp;
	fp=fopen(inp_filename,"w");
	
	if(fp==NULL)
	{
		printf("Error in opening file for writing.\n");
		return;
	}
	//store info
	for(int i=0;i<num_people;i++)
	{
		fprintf(fp,"%s %s %s\n",contacts[i].f_name,contacts[i].l_name,contacts[i].number);
	}
	//close stream
	fclose(fp);
	printf("User entries have been stored successfully.\n");
}

//Restore function allows user to exit and then reopen their phonebook
void restore(struct Phonebook **contacts, int *num_people, const char *filename)
{
	//establishing name for file
	char default_locat[]= "phonebook.txt";
	const char *inp_filename= filename;
	if (filename[0]=='\0')
	{
		inp_filename=default_locat;
	}

	//open stream to read
	FILE *fp;
	fp=fopen(inp_filename,"r");
	
	if (fp==NULL)
	{
		printf("Error in opening file for reading.\n");
		return;
	}
	//Allocating memory for phonebook struct
	*contacts= malloc(sizeof(struct Phonebook));
	if (*contacts==NULL)
	{
		printf("Error in opening your file.\n");
		fclose(fp);
		return;
	}
	
	*num_people=0;
	//Reading data into allocated memory and reallocating memory for more phonebook structs
	while(fscanf(fp,"%s %s %s",(*contacts)[*num_people].f_name,(*contacts)[*num_people].l_name, (*contacts)[*num_people].number)==3)
	{
		(*num_people)++;
		
		*contacts= realloc(*contacts,(*num_people+1) * sizeof(struct Phonebook));
		if (*contacts==NULL)
		{
			printf("Error in memory reallocation.\n");
			fclose(fp);
			return;
		}
	}
	//close stream
	fclose(fp);
	printf("Phonebook data has been restored.\n");
}
//Menu_display function which display the options to user
void menu_display()
{
	printf("\nPhone Book Application\n1) Add friend \n2) Delete friend \n3) Show phone book \n4) Sort phonebook \n5) Find phone number \n6) Randomly select friend \n7) Delete entire phonebook \n8) Store entries into file \n9) Retrieve entries from file \n10) Quit \n\nWhat do you want to do: ");

}

int main()
{
	//Friend variable to point to memory for phonebook. Num_people stores the number of people in contacts and request is initialized for user request
	struct Phonebook *friend = NULL;
	int num_people=0;
	int request;
	char filename[256];
	//Do while loop to loop through phone book guide until the user enters 10. It then prints the phonebook and exits loop.
	do{
	menu_display();
	scanf("%d",&request);
	
	//Printing the function related to the user request
	switch(request)
	{
	case 1:
		add_friend(&friend, &num_people);
		break;
		
	case 2:
		del_friend(&friend, &num_people);
		break;
		
	case 3:
		print_pb(friend,num_people);
		break;
	
	case 4:
		sort_fnames(friend,num_people);
		break;
		
	case 5:
		find_num(friend, num_people);	
		break;
		
	case 6:
		random_select(friend, num_people);
		break;
	case 7:
		del_every1(&friend,&num_people);
		break;
	case 8:
		printf("Enter name of file to store your phonebook information, or leave empty for default file location: ");
		scanf("%s", filename);
		store(friend,num_people,filename);
		break;
	case 9:
		printf("Enter name of file to restore from, or leave empty for default file location: ");
		scanf("%s", filename);
		restore(&friend, &num_people,filename);
		break;
	case 10:
		printf("Goodbye!");
		break;
	}
	}while (request!=10);
	return 0;
}