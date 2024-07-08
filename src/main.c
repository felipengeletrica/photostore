/********************************************************************
Copyright (c) 2014-2018, Felipe Vargas <felipeng.eletrica@gmail.com>
 FileName:      main.c
 programmer:    Felipe Vargas
 version: See version control (git server)

*******************************************************************/

/************************** Includes ******************************/
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

#include "photostore/photostore.h"

/************************** Defines  *******************************/

#define TERMINAL_BUFFER 1000
#define KEYBOAD_BUFFER 255

#define POSIX

#if defined POSIX
  #define CLEARSCR system ( "clear" )
#elif defined MSDOS || defined WIN32
  #define CLEARSCR system ( "cls" )
#endif

enum selopt
{
	NA,
	ADD_CAMERA ,
	ADD_ACCESSORY,
	CONSULT_ALL_CAM ,
	CONSULT_ALL_ACC	,
	CONSULT_CAM_MODEL,
	DELETE_CAM_MODEL,
	DELETE_ACC_ID,
	UPDATE_CAM_MODEL,
	UPDATE_ACC_ID,
	CREATE_DATABASE,
	QUIT_PROGRAM
};

typedef struct
{
	int option;
	char *name;

}st_menu;

/************************** Prototypes *******************************/
void banner(void);
void choose_options(void);
void message(char *msg);
int read_validate_chardata(char data[]);

/*
 *\brief Table options
 */

static st_menu menu[] = {
		{
				.option = ADD_CAMERA,
				.name = "\t[ 1 ] Add new camera\n\r"
		},
		{
				.option = ADD_ACCESSORY,
				.name = "\t[ 2 ] Add new accessories\n\r"
		},
		{
				.option = CONSULT_ALL_CAM,
				.name = "\t[ 3 ] Consult all cameras\n\r"
		},
		{
				.option = CONSULT_ALL_ACC,
				.name = "\t[ 4 ] Consult all accessories\n\r"
		},
		{
				.option = CONSULT_CAM_MODEL,
				.name = "\t[ 5 ] Consult camera using model, "
				"returning accessories order\n\tby type and price\n\r"
		},
		{
				.option = DELETE_CAM_MODEL,
				.name = "\t[ 6 ] Remove camera using model\n\r"
		},
		{
				.option = DELETE_ACC_ID,
				.name = "\t[ 7 ] Remove accessory using id\n\r"
		},
		{
				.option = UPDATE_CAM_MODEL,
				.name = "\t[ 8 ] Update Camera list using model\n\r"
		},
		{
				.option = UPDATE_ACC_ID,
				.name = "\t[ 9 ] Update Accessories using id\n\r"
		},
		{
				.option = CREATE_DATABASE,
				.name = "\t[ 10 ] Create new database (careful this erases the database and"
						"\n\tcreates a new empty)\n\r"
		},
		{
				.option = QUIT_PROGRAM,
				.name = "\t[ 11 ] Quit\n\r"
		},
		{} /* None */
};

/*
 *\brief Show options
 */
void choose_options(void)
{
	int cont = 0;
	printf("\n\r\tSelect a option and press [ENTER]:\n\r");
	printf("----------------------------------------------------------------------\n\r");
	while(menu[cont].name){
		printf("%s", menu[cont++].name);
	}
}

/*
 *\brief: main
 */
int main(void)
{
	char input_option[KEYBOAD_BUFFER];
	int inumber = 0;
	float fnumber = 0;
	int option = NA;
	int selected = NA;
	int status_program = 1;
	int ret = -1;
	int 	len = 0;
	st_camera camera_st;
	st_camera *cameraList_st =  NULL;
	st_accessory *accessoryList_st = NULL;

	st_accessory accessory_st;
	st_database *database_st;

	//database
	database_st = sqlite3_connect(database);

	//check database
	if(database_st == NULL){
		message("database not found! \n\r"
				"To create a new bank use the menu option 10");
	}


	//Clear terminal
	CLEARSCR;

	while(status_program){

		//Initial banner
		banner();
		//Banner Options
		choose_options();

		printf("\n\r\tType Option: ");
		fgets(input_option, KEYBOAD_BUFFER, stdin);
		option = atoi(input_option);

		//Selected menu options
		switch(option)
		{
			case ADD_CAMERA:

				printf("\n\r\t############## Registering a new camera ############## \n\r");
				printf("\n\r\tModel: ");
				if(read_validate_chardata((char *) &input_option) == false){
					message("Invalid input");
					break;
				}
			    sprintf(camera_st.model, "%s",  input_option);
			    printf("\n\r\tManufacturer: ");
			    if(read_validate_chardata((char *) &input_option) == false){
			    		message("Invalid input");
			    		break;
			    }
			    sprintf(camera_st.manufacturer, "%s", input_option);
			    	printf("\n\r\tWeight in grams: ");
			    	fgets(input_option, KEYBOAD_BUFFER, stdin);
			    	camera_st.weight = atoi(input_option);
			    printf("\n\r\tPrice: ");
			 	fgets(input_option, KEYBOAD_BUFFER, stdin);
				sscanf(input_option, "%f", &fnumber);
			    camera_st.price = fnumber;
			    printf("\n\r\tResolution in megapixel: ");
			   	fgets(input_option, KEYBOAD_BUFFER, stdin);
			   	sscanf(input_option, "%f", &fnumber);
			    camera_st.resolution = fnumber;
			    printf("\n\r\tWifi type y or n to Yes or Not:");
			    if(read_validate_chardata((char *) &input_option) == false){
			    		message("Invalid input");
			    		break;
			    }
			    	if(strcmp(input_option, "y") != 0 && strcmp(input_option, "n") != 0)
			    	{
			    		message("\tInvalid data");
			    		break;
			    	}
			    	camera_st.wifi =  atoi(input_option) == 'y' ? 1 : 0;
			    	//Save in database data
				//ret = insert_cam(&camera_st);
			    ret	= insert_cam(database_st, &camera_st);
				message(ret == 0 ? "Success in add new camera" : "Fail in add new camera");
				break;


			case ADD_ACCESSORY:

				printf("\n\r\t############## Registering a new accessory ############## \n\r");
				printf("\n\r\tCamera model for the accessory: ");
				if(read_validate_chardata((char *) &input_option) == false){
					message("Invalid input");
					break;
				}
				sprintf(camera_st.model, "%s",  input_option);
				printf("---------------- List os accessories types -------------------");
				for(int access = 0; access < SIZE_ACCESSORY_OPTIONS; access++)
				printf("\n\r\tid: %d -> %s", access, list_accessory[access]);
				printf("\n\r\tAccessory id:");
			    fgets(input_option, KEYBOAD_BUFFER, stdin);
			    accessory_st.accessory = atoi(input_option);
			    printf("\n\r\tManufacturer: ");
				if(read_validate_chardata((char *) &input_option) == false){
					message("Invalid input");
					break;
				}
			    sprintf(accessory_st.manufacturer, "%s", input_option);
			    	printf("\n\r\tDescription: ");
			    	if(read_validate_chardata((char *) &input_option) == false){
			    		message("Invalid input");
			    		break;
			    	}
          		sprintf(accessory_st.descrition , "%s", input_option);
			    	printf("\n\r\tPrice: ");
			    	fgets(input_option, KEYBOAD_BUFFER, stdin);
			    	sscanf(input_option, "%f", &fnumber);
			    	accessory_st.price =  fnumber;

			    	ret = insert_acess(database_st, &accessory_st, camera_st.model);
				message(ret == 0 ? "Success" : "Fail");
				break;


			case CONSULT_ALL_CAM:

				printf("\n\r\t############## Consult all Cameras ############## \n\r");
				ret = consult_allcam(database_st);
				//st_datatable * datatable_camera_st = NULL;
				//datatable_camera_st = fetch_all_cam(database_st);
				//free(datatable_camera_st);
				//showcam(datatable_camera_st);
				message(ret == 0 ? "Success in consult all cameras" : "Fail in consult all cameras");
				break;


			case CONSULT_ALL_ACC:

				printf("\n\r\t############## Consult all Accessories ############## \n\r");
				ret = consult_allacess(database_st);
				message(ret == 0 ? "Success" : "Fail");
				break;


			case CONSULT_CAM_MODEL:

				printf("\n\r\t############## Consult Cameras & Accessories ############## \n\r");
				printf("\n\r\tModel: ");
				if(read_validate_chardata((char *) &input_option) == false){
					message("Invalid input");
					break;
				}
				ret = consult_list_cam_ad_acess(database_st, input_option);
				message(ret == 0 ? "Success in consult cameras and accessories" : "Fail in consult cameras and accessories");
				break;


			case DELETE_CAM_MODEL:

				printf("\n\r\t############## Delete Camera ############## \n\r");
				printf("\n\r\tModel: ");
				if(read_validate_chardata((char *) &input_option) == false){
					message("Invalid input");
					break;
				}
			    sprintf(camera_st.model, "%s",  input_option);
				ret = delete_cam(database_st, input_option);
				message(ret == 0 ? "Success" : "Fail");
				break;


			case DELETE_ACC_ID:

				printf("\n\r\t############## Delete accessory ############## \n\r");
				printf("\n\r\tAccessory id: ");
				fgets(input_option, 256, stdin);
				ret = delete_acess(database_st, atoi(input_option));
				message(ret == 0 ? "Success" : "Fail");
				break;


			case UPDATE_CAM_MODEL:

				printf("\n\r\t############## Update Camera ############## \n\r");
				printf("\n\r\tModel: ");
				if(read_validate_chardata((char *) &input_option) == false){
					message("Invalid input");
					break;
				}
			    sprintf(camera_st.model, "%s",  input_option);
			    printf("\n\r\tManufacturer: ");
				if(read_validate_chardata((char *) &input_option) == false){
					message("Invalid input");
					break;
				}
			    sprintf(camera_st.manufacturer, "%s", input_option);
			    	printf("\n\r\tWeight in grams: ");
			    	fgets(input_option, KEYBOAD_BUFFER, stdin);
			    	camera_st.weight =  atoi(input_option);
			    printf("\n\r\tPrice: ");
			    	fgets(input_option, KEYBOAD_BUFFER, stdin);
			    	sscanf(input_option, "%f", &fnumber);
			    	camera_st.price = fnumber;
			    printf("\n\r\tResolution in megapixel: ");
			   	fgets(input_option, KEYBOAD_BUFFER, stdin);
			   	sscanf(input_option, "%f", &fnumber);
			    camera_st.resolution = fnumber;
			    printf("\n\r\tWifi type y or n to Yes or Not:");
				if(read_validate_chardata((char *) &input_option) == false){
					message("Invalid input");
					break;
				}
			    	if(strcmp(input_option, "y") != 0 && strcmp(input_option, "n") != 0)
			    	{
			    		message("\tInvalid data");
			    		continue;
			    	}
			    	camera_st.wifi =  atoi(input_option) == 'y' ? 1 : 0;

			    	//Save in database data
				ret = update_cam(database_st, &camera_st);
				message(ret == 0 ? "Success" : "Fail");
				break;


			case UPDATE_ACC_ID:

				printf("\n\r\t############## Update accessory ############## \n\r");
				printf("\n\r\tEnter the id of the acessories in the database, "
						"\n\r\tin case you do not know consult before noting oid: ");
				printf("\n\r\tId:");
				fgets(input_option, KEYBOAD_BUFFER, stdin);
				accessory_st.id = atoi(input_option);
				printf("---------------- List os accessories types -------------------");
				for(int access = 0; access < SIZE_ACCESSORY_OPTIONS; access++){

					printf("\n\r\tid: %d -> %s", access, list_accessory[access]);
				}
				printf("\n\r\tAccessory type:");
				fgets(input_option, KEYBOAD_BUFFER, stdin);
				accessory_st.accessory = atoi(input_option);
				printf("\n\r\tManufacturer: ");
				if(read_validate_chardata((char *) &input_option) == false){
					message("Invalid input");
					break;
				}
				sprintf(accessory_st.manufacturer, "%s", input_option);
				printf("\n\r\tDescription: ");
				if(read_validate_chardata((char *) &input_option) == false){
					message("Invalid input");
					break;
				}
				sprintf(accessory_st.descrition , "%s", input_option);
				printf("\n\r\tPrice: ");
				fgets(input_option, KEYBOAD_BUFFER, stdin);
				sscanf(input_option, "%f", &fnumber);
				accessory_st.price =  fnumber;

				//Update database
				ret = update_acess(database_st, &accessory_st);
				message(ret == 0 ? "Success" : "Fail");
				break;


			case CREATE_DATABASE:

				printf("\n\r\tAre you sure you want to delete the database? "
					   "\n\tEnter [y] to clear and [n] to cancel\n\r");

				if(read_validate_chardata((char *) &input_option) == false){
					message("Invalid input");
					break;
				}
				if(strcmp(input_option, "y") == 0)
				{
					message("\tDeleting database...");
					ret = createdatabase(database_st);
					printf("\t%s in delete and create new database", (ret == 0 ? "Success" : "Fail"));
			     }
				else
				{
					printf("\n\t Aborted");
				}

				break;


			case QUIT_PROGRAM:

				message("Quit! Bye Bye :)");
				status_program = 0;
				break;


			default:

				message("\tInvalid option!");
				break;
		}

		//wait a key for new banner and menu
		if(status_program != 0)
		{
			message("Press [ENTER] key continue...");
			fgets(input_option, KEYBOAD_BUFFER, stdin);
		}

		//Clear terminal
		CLEARSCR;
	}

	//Close database
	database_close(database_st);

	return 0;
}

/*
 *\brief: Show welcome banner
 */
void banner(void)
{
	const char * message =
	{		"\n\r######################################################################\n\r"
			"\n\r\tDBServer Assessoria em Sistemas de Informação            "
			"\n\r\tWelcome to Photographic Equipament Store!               \n\r"
			"\n\r######################################################################"
	};

	printf("%s", message);
}

/*
 *\brief: Print messagens with frame
 *\param *msg: message
 */
void message(char *msg)
{
	char buffer[TERMINAL_BUFFER];
	char  message [] =
	{
			"\n\r#####################################################################\n\r"
	};

	sprintf(buffer, "%s\t%s%s", message, msg, message);
	printf("%s", buffer);
}

int read_validate_chardata(char data[])
{
	int ret = false;
	int len = 0;

	 fgets(data, KEYBOAD_BUFFER, stdin);
	 len = strlen(data);
	 //Remove enter key
	 if(data[len-1] == '\n' ){
		 data[len-1] = 0;

		 ret = true;
	 }

	return ret;
}
