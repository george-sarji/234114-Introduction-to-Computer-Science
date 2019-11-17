/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/



/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/

int print_enter_enemy_name();
int print_dragonA_sent();
int print_dragonB_sent();
int print_dragonC_sent();
int print_no_dragon_sent();

int main()
{
	return 0;
}

int print_enter_enemy_name(){
	return printf("Please enter enemy name:\n");
}

int print_dragonA_sent(){
	return printf("\nKhalisi sent dragonA into the battle!!!\n");
}

int print_dragonB_sent(){
	return printf("\nKhalisi sent dragonB into the battle!!!\n");
}

int print_dragonC_sent(){
	return printf("\nKhalisi sent dragonC into the battle!!!\n");
}

int print_no_dragon_sent(){
	return printf("\nNO Dragon has been sent into the battle!!!\n");
}