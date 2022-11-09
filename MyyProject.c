/*
 ============================================================================
 Name        : Mini_project.c
 Author      :  Mohamed Mostafa Mohamed Abdelrahman
 Date        : 25/8/2022
 Description : c project,Vehicle Control System.
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
//-------------------------------------------------------------------//
typedef enum             //Creating boolean type
{
	ON = 1, OFF = 0
} bool;
//-------------------------------------------------------------------//
//My Functions//
void my_vehicle();       //Control the state of the vehicle
void Main_Menu();        // Display the main options for the vehicle ON,OFF,QUIT!
void turn_on_vehicle();  //Dealing with the option of turning on the vehicle
void sensors_menu();     //Displaying the options when the vehicle is ON
void turn_off_vehicle(); //Turning off the vehicle
void quit_vehicle();     //Quitting the vehicle
void current_vehicle_state(); //Displays the current state of the different components of the vehicle
//-------------------------------------------------------------------//
//Some global variables used
int vehicle_speed=70;
float room_temp=35.0,engine_temp=90.0;
bool AC_control=OFF,engine_temp_controller=OFF;
//-------------------------------------------------------------------//
int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	Main_Menu();
	return 0;
}
void my_vehicle()
{
	char state_vehicle;           //Getting input from the user to determine the state of the vehicle
	scanf(" %c",&state_vehicle);
	switch(state_vehicle)
	{
	case 'a':
	{
		turn_on_vehicle();
		break;
	}
	case 'b':
	{
		turn_off_vehicle();
		break;
	}
	case 'c':
	{
		quit_vehicle();
		break;
	}
	default:
	{
		printf("Please enter a valid value :) \n");
		Main_Menu();
	}
	}
}
void Main_Menu()        //Displaying the main options for the state of the vehicle
{
	printf("HELLO :)\nMain Menu\n");
	printf("\na.Turn on the vehicle\nb.Turn off the vehicle\nc.Quit the system\n");
	my_vehicle();
}
void sensors_menu(char *ptr2answer) //Displaying the options valid in the system and start dealing with it
{
	printf("1-Turn OFF the engine\t\tFor yes press 1\n");
	printf("2-Set the traffic lights\tFor yes press 2\n");
	printf("3-Set the room temperature\tFor yes press 3\n");
	printf("4-Set the engine temperature\tFor yes press 4\n");
	scanf(" %c",ptr2answer);
}

void turn_on_vehicle()           //Dealing with the options available when the vehicle is ON
{
	printf("Vehicle is ON!\n\n"); //printing the state of the vehicle
	void (*ptr2turn_on_vehicle)()=turn_on_vehicle; //Pointer to function used for calling the function
	char answer_from_menu;
    char traffic_color;
	sensors_menu(&answer_from_menu);  //Getting value from the user who chose from the menu what to do
	switch(answer_from_menu)          //Depending on the value the user enters the system starts to deal with
		{
		case '1':             //Here the user chooses to turn off the vehicle
		{
			turn_off_vehicle();
			break;
		}
		case '2':         // Here the user chooses to set the traffic Controller
		{
			puts("You chose to set the traffic light color\nWhat is the traffic color now?");
			puts("For GREEN press G\nFor RED press R\nFor ORANGE press O");
			scanf(" %c",&traffic_color);  //Getting value from the user for the traffic color and depending on the value determine what to do
			if (traffic_color == 'G' || traffic_color == 'g')
				{
					vehicle_speed = 100;  //Setting the vehicle speed to 100 as the traffic color is GREEN
					current_vehicle_state(); //Displays the current state of the different components of the vehicle
				}
			else if (traffic_color == 'R' || traffic_color == 'r')
				{
				    vehicle_speed = 0;      //Setting the vehicle speed to 0 as the traffic color is RED
				    current_vehicle_state(); //Displays the current state of the different components of the vehicle
				}
		    else if (traffic_color == 'O' || traffic_color == 'o')
				{
					vehicle_speed = 30;  //Setting the vehicle speed to 30 as the traffic color is ORANGE
					AC_control = ON;
					room_temp = room_temp * (5 / 4) + 1;
					engine_temp = room_temp;
					if (!engine_temp_controller)
						 {
						   engine_temp_controller = ON;
						 }
					current_vehicle_state(); //Displays the current state of the different components of the vehicle
				 }
			(*ptr2turn_on_vehicle)();  //calling the function (Turn_on_vehicle)to make the sensors menu always displayed
			break;
		}
		case '3':    // Here the user chooses to deal with the temperature controller as it will change the state of the AC
		{
			puts("You chose to set the room temperature\nPlease enter the room temperature!");
			scanf("%f",&room_temp);
			if (room_temp < 10)
				{
					AC_control = ON;
					room_temp = 20;
					current_vehicle_state(); //Displays the current state of the different components of the vehicle
				}
			else if (room_temp > 30)
				{
					AC_control = ON;
					room_temp = 20;
					current_vehicle_state(); //Displays the current state of the different components of the vehicle
				}
			else
				{
					AC_control = OFF;
					current_vehicle_state(); //Displays the current state of the different components of the vehicle
				}
			(*ptr2turn_on_vehicle)();
			break;
		}
		case '4':   // Here the user chooses to deal with the Engine controller as it will change the engine temperature and the state of the engine_temp_controller
		{
			puts("You chose to set the engine temperature\nHow much is the engine temperature?");
			scanf(" %f",&engine_temp);
			if (engine_temp < 100)
				{
				    engine_temp_controller = ON;
				    engine_temp = 125;
				    current_vehicle_state(); //Displays the current state of the different components of the vehicle
			}
			else if (engine_temp > 150)
				{
					engine_temp_controller = ON;
					engine_temp = 125;
					current_vehicle_state(); //Displays the current state of the different components of the vehicle
				}
			else
				{
					engine_temp_controller = OFF;
					current_vehicle_state(); //Displays the current state of the different components of the vehicle
			    }
		(*ptr2turn_on_vehicle)();
			break;
		}
		default:
			printf("Please enter a valid value :) \n");
			(*ptr2turn_on_vehicle)();
		}
	}
void current_vehicle_state()   //printing some values of the components of the vehicle
{
	printf("Engine is ON\n");
	if (AC_control == 1)
	{
		printf("AC is ON\n");
	}
	else
	{
		printf("AC is OFF\n");
	}
	printf("Vehicle Speed: %d Km/Hr\n", vehicle_speed);
	printf("Room Temperature: %.1f C\n", room_temp);
	if (engine_temp_controller == 1)
	{
		printf("Engine Temp Controller is ON\n");
	}
	else
	{
		printf("Engine Temp Controller is OFF\n");
	}
	printf("Engine Temperature: %.1f C\n\n", engine_temp);

}
void turn_off_vehicle()  //Dealing with the vehicle when it's off
{
	printf("\n\nThe vehicle is OFF\n\n\n");
	Main_Menu();  //Display the main options so the user can choose again
}
void quit_vehicle()
{
	puts("Quitting the system !");   //Terminating the system.
	return ;
}




