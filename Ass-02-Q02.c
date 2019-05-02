#include "Ass-02.h"
#include <stdio.h>
#include <stdlib.h>
<<<<<<< Updated upstream
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int isOperator(char );
int isFunction(char );
static char* mathParser(char* mathString);
float evaluatePostfix(char** queue, int qlen);
static int getSize(char *s);
int associative(char token);
int greaterPrecedence(char first, char second);
||||||| ancestor
#include <time.h>
=======
#include <time.h>
#include <math.h>
#include <ctype.h>
>>>>>>> Stashed changes

#define MAX_MATH_STR 30				//This is the maximum number of characters that an expression may have in calculator.
#define MAX_DISP_STR 13				//This is the maximum number of characters that may be displayed on the screen at any time.

#define qpush(x) queue[qlen++] = x
#define spush(x) stack[slen++] = x
#define spop() stack[--slen]

// ================ MATH PARSING SECTION =======================
#define qpush(x) queue[qlen++] = x
#define spush(x) stack[slen++] = x
#define spop() stack[--slen]

// SHUNTING-YARD ALGORITHM
//This function will parse the math expression and return the result OR an error if the expression made no sense.
static char* mathParser(char* mathString)
{
	char* stack[100];//malloc
	char* queue[100];//malloc
	int qlen = 0;
	int slen = 0;

	// TEST VALUES
	/* char* mathString = (char*)malloc(sizeof(char)*100); */
	/* char* mathString = "3+4x2/(1-5)^2^3\0";//3.00012 */
	/* mathString = "((15/(7−(1+1)))x3)−(2+(1+1))\0"; //5 */
	/* char* mathString = "13x14+((1-5)/2)\0";//180 */
	/* mathString = "13x14+15\0";//197 */
	/* mathString = "13+14x15\0";//223 */

	printf("math string is : ");
	for (int j = 0; j != '0'; j++)
		printf("%c", mathString[j]);
	printf("-end\n");

	/* 	while there are tokens to be read: */
	for (int j = 0; j < strlen(mathString); j++)
	{
/*     read a token. */
		char* token = (char*)malloc(sizeof(char)*10);
		token[0] = mathString[j];
		token[1] = '\0';
		printf("%dReads token '%s'", j, token);
		printf("	Action: ");
/*     if the token is a number, then: */
		if (isdigit(token[0]))
		{
			int len = 0;
			token[len++] = token[0];
			// read til end of number
			while (isdigit(mathString[j+1]) || mathString[j+1] == '.')
			{
#define qpush(x) queue[qlen++] = x
				j++;
				token[len++] = mathString[j];
			}
			token[len] = '\0';
			printf("num is %s\n", token);
			printf("Push it to the output queue\n");
			/*         push it to the output queue. */
			qpush(token);

		}
/*     if the token is a function then: */
		if (isFunction(token[0]))
		{
			printf("Push it to the operator stack\n");
			/*         push it onto the operator stack  */
			spush(token);
		}
/*     if the token is an operator, then: */
		if (isOperator(token[0]))
		{
			/*         while ((there is a function at the top of the operator stack) */
			while ((slen > 0 && isFunction(stack[slen-1][0])) 
					
					/*                or (there is an operator at the top of the operator stack with greater precedence) */
					|| (slen > 0 && isOperator(stack[slen-1][0]) && greaterPrecedence(stack[slen-1][0], token[0]) == -1) 
					
					/*                or (the operator at the top of the operator stack has equal precedence and is left associative)) */
					|| ((slen > 0 && isOperator(stack[slen-1][0]) && greaterPrecedence(stack[slen-1][0], token[0]) == 0 && associative(stack[slen-1][0]) == 0) 
						
						/*               and (the operator at the top of the operator stack is not a left parenthesis): */
						&& stack[slen-1][0] != '('))
			{
				printf("ENTER?\n");
				/*             pop operators from the operator stack onto the output queue. */
				printf("Pop stack to output\n");
				qpush(spop());
			}
			/*         push it onto the operator stack. */
			printf("Push it to the operator stack\n");
			spush(token);
		}
/*     if the token is a left paren (i.e. "("), then: */
		if (token[0] == '(')
/*         push it onto the operator stack. */
		{
			printf("Push it to the operator stack\n");
			spush(token);
		}
/*     if the token is a right paren (i.e. ")"), then: */
		if (token[0] == ')')
		{
			/*         while the operator at the top of the operator stack is not a left paren: */
			while (slen > 0 && stack[slen-1][0] != '(')
			{
				printf("Pop stack to output\n");

				/*             pop the operator from the operator stack onto the output queue. */
				qpush(spop());
				/*         #<{(| if the stack runs out without finding a left paren, then there are mismatched parentheses. |)}># */
			}
			
			/*         if there is a left paren at the top of the operator stack, then: */
			if (stack[slen-1][0] == '(')
			{
				printf("Pop stack\n");
				/*             pop the operator from the operator stack and discard it */
				spop();
			}
		}
	printf("Output queue: ");
	for (int a = 0; a < qlen; a++)
		printf("%s ", queue[a]);
	printf("	Operator stack: ");
	for (int a = 0; a < slen; a++)

		printf("%s ", stack[a]);
	printf("\n\n");
	}
	// end
/* after loop, if operator stack not null, pop everything to output queue */
/* if there are no more tokens to read: */
/*     while there are still operator tokens on the stack: */
	while (slen > 0)
	{
		/*         #<{(| if the operator token on the top of the stack is a paren, then there are mismatched parentheses. |)}># */
		if (stack[slen-1][0] == '(' || stack[slen-1][0] == ')')
			printf("mismatched parenthesis\n");
		/*         pop the operator from the operator stack onto the output queue. */
		qpush(spop();)

	}
	/* exit. */

	// print final contents of stack and queue
	printf("Output queue: ");
	for (int a = 0; a < qlen; a++)
			printf("%s ", queue[a]);
	printf("	Operator stack: ");
	for (int a = 0; a < slen; a++)
			printf("%s ", stack[a]);
	printf("\n");

	float result = evaluatePostfix(queue, qlen);	// evaluate postfix value read from stack
	printf("Result: %g\n", result);
	char* resultString = (char*)malloc((char)10);
	sprintf(resultString, "%f", result);		// store result in resultString
	printf("amount is %s\n", resultString);
	return resultString;				// return resultString
}

float evaluatePostfix(char** queue, int qlen)
{

#define opush(x) opStack[olen++] = x
#define opop() opStack[--olen]
	int olen = 0;
	float result = 0;
	float opStack[100];
/* 	for each token in the postfix expression: */
	for (int i = 0; i < qlen; i++)
	{
		for (int j = 0; j < olen; j++)
			printf("%g ", opStack[j]);

		char* token = queue[i];
		printf("[%s] ", token);
		for (int a = i+1; a < qlen; a++)
			printf("%s ", queue[a]);
		printf("\n");

		/*   if token is an operator: */
		if (isOperator(token[0]))
		{
			/*     operand_2 ← pop from the stack */
			float operand2 = opop();
			/*     operand_1 ← pop from the stack */
			float operand1 = opop();
			/* #<{(|     push token onto the stack |)}># */
			/*     result ← evaluate token with operand_1 and operand_2 */
			if (token[0] == '+')
				result = operand1 + operand2;
			if (token[0] == '-')
				result = operand1 - operand2;
			if (token[0] == 'x')
				result = operand1 * operand2;
			if (token[0] == '/')
				result = operand1 / operand2;
			if (token[0] == '^')
				result = pow(operand1, operand2);
			/*     push result back onto the stack */
			opush(result);
		}
		/*   else if token is an operand: */
		else if (isdigit(token[0]))
		{
			// push token onto the stack
			opush(atof(token));
		}
	}
	/* result ← pop from the stack */
	result = opop();
	return result;
}


// returns 0 if left and 1 if right associative respectively
int associative(char token)
{
	if (token == '^')
		return 1;

	if (token == 'x')
		return 0;

	if (token == '/')
		return 0;

	if (token == '+')
		return 0;

	if (token == '-')
		return 0;
	return -1;
}


// returns -1 if first has greater prec, 0 if equal and
// 1 if second has greater
int greaterPrecedence(char first, char second)
{
	int fir = 0;
	int sec = 0;
	if (first == '^')
		fir = 4;
	else if (first == 'x')
		fir = 3;
	else if (first == '/')
		fir = 3;
	else if (first == '+')
		fir = 2;
	else if (first == '-')
		fir = 2;

	if (second == '^')
		sec = 4;
	else if (second == 'x')
		sec = 3;
	else if (second == '/')
		sec = 3;
	else if (second == '+')
		sec = 2;
	else if (second == '-')
		sec = 2;

	if (fir > sec)
	{
		printf("%c has higher precedence than %c\n", first, second);
		return -1;
	}
	if (fir == sec)
	{

		printf("%c has equal precedence to %c\n", first, second);
		return 0;
	}

		printf("%c has higher precedence than %c\n", second, first);
	return 1;
}


int isOperator(char token)
{
	if (token == 'x')
		return 1;
	if (token == '/')
		return 1;
	if (token == '+')
		return 1;
	if (token == '-')
		return 1;
	if (token == '*')
		return 1;
	if (token == '^')
		return 1;
	return 0;
}

int isFunction(char token)
{
	// no functions implemented yet
	return 0;
}
// ================ MATH PARSING SECTION END =======================
static int   mathStrLen = 0;
static char  mathString[32];									//This is the string that contains the characters that contain the entire mathematical expression.
static char* globalDisplayPointer;								//Holds scroll position. When new character is input is reset to that most up to date display.
static int cursorX[] = {89,106,123,140,157,174,191,208,225,242,259,276,293,310};
static int cursorPos;
static float result = 0;

/* Prints a cursor to screen. i determines the position of cursor. */
static void printCursor(int i){

	//Clear Cursor Area
	BSP_LCD_SetTextColor (0xFFFF);										//Text Color: White.
	BSP_LCD_FillRect (81, 1, 239, 12);									//Write over screen.
	BSP_LCD_SetTextColor (LCD_COLOR_BLACK);								//Text Color: Black.

	//Determine pixel positions
	BSP_LCD_SetBackColor(0xFFFF);			//Background Color: White
	BSP_LCD_SetTextColor (LCD_COLOR_BLACK);			//Text Color: Black
	BSP_LCD_SetFont (&Font12);						//Font Size: 24
	BSP_LCD_DisplayChar(cursorX[i],1,'^');
	BSP_LCD_SetFont (&Font24);



	printf("Cursor Position: %d", cursorPos);

/* Deletes the last character entered. */
static void deleteKey(){

	int diff = 0;


	if(mathStrLen != 0){
		mathString[mathStrLen-1] = '\0'; 					//Replaces the last character of the string with a null.
		mathStrLen--;										//Update the length of the mathString.
		printf("mathStrnLen: %d\n", mathStrLen);
		diff = mathStrLen - MAX_DISP_STR;

		if(diff <= 0){										//If the diff < 0 then the length of string is less than display so show whole string.
			cursorPos = mathStrLen-1;
			printf("making display ptr = mathString \n");
			globalDisplayPointer = mathString;				//This assignment means that the whole string will be shown from the beginning.
			printf("String to be displayed: %s \n", globalDisplayPointer);

		}else{
			cursorPos = 12;
			globalDisplayPointer = (mathString + (mathStrLen - MAX_DISP_STR));		//If the mathStrLen is greater than display move display down the expression.
			printf("Global Ptr not updated \n");
		}


		/* Refresh Display */
		BSP_LCD_SetTextColor (0xFFFF);										//Text Color: White.
		BSP_LCD_FillRect (81, 0, 239, 46);									//Write over screen.
		BSP_LCD_SetTextColor (LCD_COLOR_BLACK);								//Text Color: Black.
		BSP_LCD_DisplayStringAt(85,13,globalDisplayPointer,LEFT_MODE);		//Display Expression after scroll.


		printCursor(cursorPos);
	}
}

/* Moves the displayed string around.*/
static void scroll(int direction){

	char showString[MAX_DISP_STR +1];
	int diff = mathStrLen - MAX_DISP_STR;								//The difference between the string length and maximum displayable characters.

	if(mathString != '\0'){														//If the display is not empty.

		/*
		 * direction			: Is the flag saying scroll to the right.
		 * diff < MAX_DISP_STR	: If false, you must stop scrolling or you'll scroll the display entirely off the screen.
		 * diff > 0 			: If false, the mathString is not yet greater than the maximum amount of display char, so you'd be scrolling content off the screen entirely.
		 */
		if(direction && ((globalDisplayPointer - mathString) <= (diff - 1)) && (diff > 0)){	//Scroll Right

			globalDisplayPointer += 1;

			//Performs the assignment for the string to be displayed.
			for(int j = 0; j<MAX_DISP_STR; j++){
				showString[j] = *(globalDisplayPointer+j);
			}

			showString[MAX_DISP_STR] = '\0';


			/* Refresh Display */
			BSP_LCD_SetTextColor (0xFFFF);										//Text Color: White.
			BSP_LCD_FillRect (81, 0, 239, 46);									//Write over screen.
			BSP_LCD_SetTextColor (LCD_COLOR_BLACK);								//Text Color: Black.
			BSP_LCD_DisplayStringAt(85,13,showString,LEFT_MODE);		//Display Expression after scroll.

			printf("StrLen: %d Scroll right > \n", mathStrLen);

			//cursorPos++;
			//printCursor(cursorPos);

		}else if( (!direction) && (diff>0) && (globalDisplayPointer != mathString)){		//Scroll Left					//Prevents negative scrolling back in time.

			globalDisplayPointer -= 1;

			//Performs the assignment for the string to be displayed.
			for(int j = 0; j<MAX_DISP_STR; j++){
				showString[j] = *(globalDisplayPointer+j);
			}

			showString[MAX_DISP_STR] = '\0';



			/* Clear Screen */
			BSP_LCD_SetTextColor (0xFFFF);				//Text Color: White.
			BSP_LCD_FillRect (81, 0, 239, 46);			//Write over screen.
			BSP_LCD_SetTextColor (LCD_COLOR_BLACK);		//Text Color: Black.

			BSP_LCD_DisplayStringAt(85,13,showString,LEFT_MODE);		//Display Expression after scroll.
			printf("StrLen: %d Scroll left < \n", mathStrLen);

			//cursorPos--;
			//printCursor(cursorPos);

		}
		//For overflowed display case and cursor moving to start of string. Only want to execute if other two cases don't.
	}

		//Just for cursor. CASE: Full string is shown.
		if(mathStrLen <= MAX_DISP_STR){
			if(direction && cursorPos >= 0 && cursorPos < (mathStrLen-1)){
				cursorPos ++;
				printCursor(cursorPos);
			}else if(!direction && cursorPos <= mathStrLen && cursorPos > 0){
				cursorPos--;
				printCursor(cursorPos);
			}

		}
		//Cursor. CASE: String longer than display.
		if(mathStrLen > MAX_DISP_STR){
			if(direction && cursorPos >= 0 && cursorPos < (MAX_DISP_STR-1)){
				cursorPos ++;
				printCursor(cursorPos);
			}else if(!direction && cursorPos <= MAX_DISP_STR && cursorPos > 0){
				cursorPos--;
				printCursor(cursorPos);
			}
		}
}

/* Just writes over the entire text box with background color. Also Resets the flags for the free position on the screen.*/
static void ClearTextBox(){

	BSP_LCD_SetTextColor (0xFFFF);				//Text Color: White.
	BSP_LCD_FillRect (81, 0, 239, 46);			//Write over screen.
	BSP_LCD_SetTextColor (LCD_COLOR_BLACK);		//Text Color: Black.

	mathString[0] = '\0'; //Sets start of string to null again.
	mathStrLen = 0;
}

/* Displays an error when you go over maximum number of characters in expression. */
static void displayError(){

	BSP_LCD_SetTextColor (0xFFFF);				//Text Color: White.
	BSP_LCD_FillRect (81, 0, 239, 46);			//Write over screen.
	BSP_LCD_SetTextColor (LCD_COLOR_BLACK);		//Text Color: Black.


	BSP_LCD_DisplayStringAt(85,13,"Max Char 30",LEFT_MODE); 		//Display Error
	HAL_Delay(1000);

	BSP_LCD_SetTextColor (0xFFFF);				//Text Color: White.
	BSP_LCD_FillRect (81, 0, 239, 46);			//Write over screen.
	BSP_LCD_SetTextColor (LCD_COLOR_BLACK);		//Text Color: Black.

	BSP_LCD_DisplayStringAt(85,13,globalDisplayPointer,LEFT_MODE);				//Display Expression

}

/* Update strings and display. */
static void updateDisplay(const char* theChar){ //PROBLEM IS MATHSTRING IS MUNTED.

	//This logic is for the cursor and only applies to when a new char is added.
	int diff = mathStrLen - MAX_DISP_STR;

	if(diff<0) cursorPos = mathStrLen;		//Whole string is shown.
	else{
		//Amount over is shown.
		cursorPos = 12;
	}

	mathString[mathStrLen] = '\0';
	if((mathStrLen) > MAX_MATH_STR){		//If max expression length exceeded.
		displayError();					 	// Display error message in text box.
	}
	else
	{
		//concatenate character onto expression.
		printf("The Char: %s\n", theChar);
		printf("A. MathString: %s Length: %d \n",mathString, mathStrLen);
		strcat(mathString,theChar);

		mathStrLen++;
		diff = mathStrLen - MAX_DISP_STR;											//Gets difference between length of string and maximum amount of display.

		if(diff > 0){
			globalDisplayPointer = (mathString + (mathStrLen - MAX_DISP_STR));		//If the mathStrLen is greater than display move display down the expression.
		}else{
			globalDisplayPointer = mathString;									    //Else if the expression doesn't yet exceed the display just display the entire mathString.
		}


//		globalDisplayPointer = displayPointer;

		printf("B. MathString: %s Length: %d \n\n",mathString, mathStrLen);

		if(mathStrLen > MAX_DISP_STR) 	BSP_LCD_DisplayStringAt(85,13,globalDisplayPointer,LEFT_MODE);	//Expression > Display
		else 						 	BSP_LCD_DisplayStringAt(85,13,(mathString),LEFT_MODE);		//Expression < Display

		printCursor(cursorPos);
	}

}

void CalculatorInit (void)
{

  // Initialize and turn on LCD and calibrate the touch panel
  BSP_LCD_Init ();
  BSP_LCD_DisplayOn ();
  BSP_TP_Init ();


  BSP_LCD_Clear (LCD_COLOR_WHITE);


  /*** Drawing Display: Consult Spreadsheet ***/


  /** DRAWING BOXES **/

  /* Scroll Buttons */
  BSP_LCD_SetTextColor(0xF81E);			//Text Colour: Power Ranger Pink
  BSP_LCD_FillRect (0, 0, 80, 48);

  /* Numbers [0-9] */
  BSP_LCD_SetTextColor(0x00FF);
  BSP_LCD_FillRect (0, 49, 240, 192);

  /* Operations */
  BSP_LCD_SetTextColor(0xFF00);
  BSP_LCD_FillRect (241, 49, 79, 192);	// [+, -, x, %]
  BSP_LCD_SetTextColor(0x1685);
  BSP_LCD_FillRect (161, 193, 80, 48);	// [=]

  /* Clear Button  */
  BSP_LCD_SetTextColor(0xE0A2);
  BSP_LCD_FillRect (81, 193, 80, 48);	// [C]

  /* Draw Grid (Borders are 2 thick) */
  BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
  BSP_LCD_DrawHLine (0,47, 320);		//0a
  BSP_LCD_DrawHLine (0,48, 320);		//0b
  BSP_LCD_DrawHLine (0,95, 320);		//1a
  BSP_LCD_DrawHLine (0,96, 320);		//1b
  BSP_LCD_DrawHLine (0,143, 320);		//2a
  BSP_LCD_DrawHLine (0,144, 320);		//2c
  BSP_LCD_DrawHLine (0,191, 320);		//3a
  BSP_LCD_DrawHLine (0,192, 320);		//3b
  BSP_LCD_DrawHLine (0,239, 320);		//4a
  BSP_LCD_DrawHLine (0,240, 320);		//4b

  BSP_LCD_DrawVLine (79, 0, 240);		//0a: Updated for scroll buttons
  BSP_LCD_DrawVLine (80, 0, 240);		//0b: Updated for scroll buttons
  BSP_LCD_DrawVLine (159, 49, 192);		//1a
  BSP_LCD_DrawVLine (160, 49, 192);		//1b
  BSP_LCD_DrawVLine (239, 49, 192);		//2a
  BSP_LCD_DrawVLine (240, 49, 192);		//2b
  BSP_LCD_DrawVLine (319, 49, 192);		//3a
  BSP_LCD_DrawVLine (320, 49, 192);		//3b
  BSP_LCD_DrawVLine (39, 0, 48);		//Scrolla
  BSP_LCD_DrawVLine (40, 0, 48);		//Scrollb

  //Updated buttons vert lines.
  BSP_LCD_DrawVLine (119, 193, 48);		//1a
  BSP_LCD_DrawVLine (120, 193, 48);		//1b
  BSP_LCD_DrawVLine (199, 193, 48);		//2a
  BSP_LCD_DrawVLine (200, 193, 48);		//2b
  BSP_LCD_DrawVLine (279, 49 , 192);	//3a
  BSP_LCD_DrawVLine (280 ,49 , 192);	//3b

  /** DRAWING CHARACTERS **/

  BSP_LCD_SetTextColor (LCD_COLOR_BLACK);	//Text Color: Black
  BSP_LCD_SetFont (&Font24);				//Font Size: 24

  /* Col 0 */
  BSP_LCD_SetBackColor(0x00FF);				//Background Color: Blue
  BSP_LCD_DisplayChar (32, 61, '7');
  BSP_LCD_DisplayChar (32, 109, '4');
  BSP_LCD_DisplayChar (32, 157, '1');
  BSP_LCD_DisplayChar (32, 205, '0');

  /* Col 1 */
  BSP_LCD_SetBackColor(0x00FF);				//Background Color: Blue
  BSP_LCD_DisplayChar (114, 61, '8');
  BSP_LCD_DisplayChar (114, 109, '5');
  BSP_LCD_DisplayChar (114, 157, '2');
  /* Split Cell */
  BSP_LCD_SetBackColor(0xE0A2);				//Background Color: Red
  BSP_LCD_DisplayChar (93, 205, 'C');
  BSP_LCD_SetFont (&Font12);				//Font Size: 12
  BSP_LCD_DisplayStringAt (130, 210, "DEL",LEFT_MODE);	//Trial and errored into place.
  BSP_LCD_SetFont (&Font24);				//Font Size: 24

  /* Col 2 */
  BSP_LCD_SetBackColor(0x00FF);				//Background Color: Blue
  BSP_LCD_DisplayChar (194, 61, '9');
  BSP_LCD_DisplayChar (194, 109, '6');
  BSP_LCD_DisplayChar (194, 157, '3');
  /* Split Cell */
  BSP_LCD_SetBackColor(0x1685);				//Background Color: Green
  BSP_LCD_DisplayChar (173, 205, '=');
  BSP_LCD_SetFont (&Font12);				//Font Size: 12
  BSP_LCD_DisplayStringAt (210, 210, "ANS",LEFT_MODE);	//Trial and errored into place.
  BSP_LCD_SetFont (&Font24);				//Font Size: 24

  /* Col 3: All Split*/
  BSP_LCD_SetBackColor(0xFF00);				//Background Color: Yellow
  BSP_LCD_DisplayChar (253, 61, '+');
  BSP_LCD_DisplayChar (290, 61, '-');
  BSP_LCD_DisplayChar (253, 109, 'x');
  BSP_LCD_DisplayChar (290, 109, '/');
  BSP_LCD_DisplayChar (253, 157, '%');
  BSP_LCD_DisplayChar (290, 160, '^');
  BSP_LCD_DisplayChar (250, 205, '(');
  BSP_LCD_DisplayChar (293, 205, ')');

  /* Scroll Buttons */
  BSP_LCD_SetBackColor(0xF81E);				//Background Color: Power Ranger Pink
  BSP_LCD_DisplayChar (10, 13, '<');
  BSP_LCD_DisplayChar (55, 13, '>');




}

/* Handles user inputs and passes the math expression as a string to a parser which returns result of mathematical expression. */
void CalculatorProcess (void)
{


  if (BSP_TP_GetDisplayPoint (&display) == 0)	//Reading in the touched points.
  {

	BSP_LCD_SetBackColor(0xFFFF);				//Set Background Color: White
	BSP_LCD_SetTextColor (LCD_COLOR_BLACK);		//Set Text Color: Black.


    if (((display.x >= 0) && (display.x <= 80)))			/* COL1: [7,4,1,0] */
    {
      if ((display.y >= 49) && (display.y < 96)) 			/* 7 */
      {
    	  updateDisplay("7");
    	  HAL_Delay(100);
      }
      else if ((display.y >= 97) && (display.y <= 144)) 	/* 4 */
      {
    	  updateDisplay("4");
		  HAL_Delay(100);
      }
      else if ((display.y >= 145) && (display.y <= 192))  	/* 1 */
      {
    	  updateDisplay("1");
		  HAL_Delay(100);
      }
      else if ((display.y >= 193) && (display.y <= 240))	/* 0 */
      {
    	  updateDisplay("0");
		  HAL_Delay(100);
      }
      else if((display.y >= 0) && (display.y <= 48)){		/* Scroll Buttons */
    	  if(display.x <= 40){
//    		  updateDisplay("<");							/* < */
    		  //printf("Scroll Left\n");
    		  scroll(0);
			  HAL_Delay(100);
    	  }else{											/* > */
//    		  updateDisplay(">");
    		 // printf("Scroll Right\n");
    		  scroll(1);
    		  HAL_Delay(100);
    	  }
      }
    }
    else if (((display.x >= 81) && (display.x <= 160))){	/* COL2: [8,5,2,[C,DEL]] */

    	if ((display.y >= 49) && (display.y < 96))			/* 8 */
	   {
		  updateDisplay("8");
		  HAL_Delay(100);
	   }
	   else if ((display.y >= 97) && (display.y <= 144))	/* 5 */
	   {
		  updateDisplay("5");
		  HAL_Delay(100);
	   }
	   else if ((display.y >= 145) && (display.y <= 192))	/* 2 */
	   {

		  updateDisplay("2");
		  HAL_Delay(100);
	   }
	   else if ((display.y >= 193) && (display.y <= 240))
	   {
		   if(display.x <= 120){							/* C */
			   ClearTextBox();
			   HAL_Delay(100);
		   }else{
			   deleteKey();									/* DEL */
			   HAL_Delay(100);
		   }
	   }
    }
    else if (((display.x >= 161) && (display.x <= 240))){	 /* COL3: [9,6,3,[=,ANS]] */

    	if ((display.y >= 49) && (display.y < 96))			/* 9 */
	   {
	      updateDisplay("9");
		  HAL_Delay(100);
	   }
	   else if ((display.y >= 97) && (display.y <= 144))	/* 6 */
	   {
		  updateDisplay("6");
		  HAL_Delay(100);
	   }
	   else if ((display.y >= 145) && (display.y <= 192)) 	/* 3 */
	   {
		  updateDisplay("3");
		  HAL_Delay(100);
	   }
	   else if ((display.y >= 193) && (display.y <= 240))
	   {
		   if(display.x <= 200){
			   equalsPressed();
			   HAL_Delay(100);
		   }else{
			   updateDisplay("A");							/* ANS */
			   HAL_Delay(100);
		   }
	   }
    }
	else if (((display.x >= 241) && (display.x <= 320))){	 /* COL4: [ [+, -], [x, /], [%, ^], [(, )] ] */

	   if ((display.y >= 49) && (display.y < 96))
	   {
		   if(display.x <= 280){
				   updateDisplay("+");						/* + */
				   HAL_Delay(100);
			   }else{
				   updateDisplay("-");						/* - */
				   HAL_Delay(100);
			   }
	   }
	   else if ((display.y >= 97) && (display.y <= 144))
	   {
		   if(display.x <= 280){
				   updateDisplay("x");						/* x */
				   HAL_Delay(100);
			   }else{
				   updateDisplay("/");						/* / */
				   HAL_Delay(100);
			   }
	   }
	   else if ((display.y >= 145) && (display.y <= 192))
	   {
		   if(display.x <= 280){
				   updateDisplay("%");						/* % */
				   HAL_Delay(100);
			   }else{
				   updateDisplay("^");						/* ^ */
				   HAL_Delay(100);
			   }
	   }
	   else if ((display.y >= 193) && (display.y <= 240))
	  {
		   if(display.x <= 280){
				   updateDisplay("(");						/* ( */
				   HAL_Delay(100);
			   }else{
				   updateDisplay(")");						/* ) */
				   HAL_Delay(100);
			   }
	  }
	}//End Col
  }// End Button Checks

}//End CalculatorProcess


// PARSER //

int isOperator(char token)
{
	if (token == 'x')
		return 1;
	if (token == '/')
		return 1;
	if (token == '+')
		return 1;
	if (token == '-')
		return 1;
	if (token == '*')
		return 1;
	if (token == '^')
		return 1;
	return 0;
}

float evaluatePostfix(char** queue, int qlen)
{

#define opush(x) opStack[olen++] = x
#define opop() opStack[--olen]
	int olen = 0;
	float result = 0;
	float opStack[100];
/* 	for each token in the postfix expression: */
	for (int i = 0; i < qlen; i++)
	{
		for (int j = 0; j < olen; j++)
			printf("%g ", opStack[j]);

		char* token = queue[i];
		printf("[%s] ", token);
		for (int a = i+1; a < qlen; a++)
			printf("%s ", queue[a]);
		printf("\n");

		/*   if token is an operator: */
		if (isOperator(token[0]))
		{
			/*     operand_2 ← pop from the stack */
			float operand2 = opop();
			/*     operand_1 ← pop from the stack */
			float operand1 = opop();
			/* #<{(|     push token onto the stack |)}># */
			/*     result ← evaluate token with operand_1 and operand_2 */
			if (token[0] == '+')
				result = operand1 + operand2;
			if (token[0] == '-')
				result = operand1 - operand2;
			if (token[0] == 'x')
				result = operand1 * operand2;
			if (token[0] == '/')
				result = operand1 / operand2;
			if (token[0] == '^')
				result = pow(operand1, operand2);
			/*     push result back onto the stack */
			opush(result);
		}
		/*   else if token is an operand: */
		else if (isdigit(token[0]))
		{
			// push token onto the stack
			opush(atof(token));
		}
	}
	/* result ← pop from the stack */
	result = opop();
	return result;
}

// returns 0 if left and 1 if right associative respectively
int associative(char token)
{
	if (token == '^')
		return 1;

	if (token == 'x')
		return 0;

	if (token == '/')
		return 0;

	if (token == '+')
		return 0;

	if (token == '-')
		return 0;
	return -1;
}

// returns -1 if first has greater prec, 0 if equal and
// 1 if second has greater
int greaterPrecedence(char first, char second)
{
	int fir = 0;
	int sec = 0;
	if (first == '^')
		fir = 4;
	else if (first == 'x')
		fir = 3;
	else if (first == '/')
		fir = 3;
	else if (first == '+')
		fir = 2;
	else if (first == '-')
		fir = 2;

	if (second == '^')
		sec = 4;
	else if (second == 'x')
		sec = 3;
	else if (second == '/')
		sec = 3;
	else if (second == '+')
		sec = 2;
	else if (second == '-')
		sec = 2;

	if (fir > sec)
	{
		printf("%c has higher precedence than %c\n", first, second);
		return -1;
	}
	if (fir == sec)
	{

		printf("%c has equal precedence to %c\n", first, second);
		return 0;
	}

		printf("%c has higher precedence than %c\n", second, first);
	return 1;
}

int isFunction(char token)
{
	// no functions implemented yet
	return 0;
}

//This function will parse the math expression and return the result OR an error if the expression made no sense.
void mathParser(void)
{
	char* stack[100];//malloc
	char* queue[100];//malloc
	int qlen = 0;
	int slen = 0;

	printf("math string is : ");
	for (int j = 0; j != '0'; j++)
		printf("%c", mathString[j]);
	printf("-end\n");

	/* 	while there are tokens to be read: */
	for (int j = 0; j < strlen(mathString); j++)
	{
/*     read a token. */
		char* token = (char*)malloc(sizeof(char)*10);
		token[0] = mathString[j];
		token[1] = '\0';
		printf("%dReads token '%s'", j, token);
		printf("	Action: ");
/*     if the token is a number, then: */
		if (isdigit(token[0]))
		{
			int len = 0;
			token[len++] = token[0];
			// read til end of number
			while (isdigit(mathString[j+1]) || mathString[j+1] == '.')
			{
			#define qpush(x) queue[qlen++] = x
				j++;
				token[len++] = mathString[j];
			}
			token[len] = '\0';
			printf("num is %s\n", token);
			printf("Push it to the output queue\n");
			/*         push it to the output queue. */
			qpush(token);

		}
		/*     if the token is a function then: */
		if (isFunction(token[0]))
		{
			printf("Push it to the operator stack\n");
			/*         push it onto the operator stack  */
			spush(token);
		}
		/*     if the token is an operator, then: */
		if (isOperator(token[0]))
		{
			/*         while ((there is a function at the top of the operator stack) */
			while ((slen > 0 && isFunction(stack[slen-1][0]))

					/*                or (there is an operator at the top of the operator stack with greater precedence) */
					|| (slen > 0 && isOperator(stack[slen-1][0]) && greaterPrecedence(stack[slen-1][0], token[0]) == -1)

					/*                or (the operator at the top of the operator stack has equal precedence and is left associative)) */
					|| ((slen > 0 && isOperator(stack[slen-1][0]) && greaterPrecedence(stack[slen-1][0], token[0]) == 0 && associative(stack[slen-1][0]) == 0)

						/*               and (the operator at the top of the operator stack is not a left parenthesis): */
						&& stack[slen-1][0] != '('))
			{
				printf("ENTER?\n");
				/*             pop operators from the operator stack onto the output queue. */
				printf("Pop stack to output\n");
				qpush(spop());
			}
			/*         push it onto the operator stack. */
			printf("Push it to the operator stack\n");
			spush(token);
		}
		/*     if the token is a left paren (i.e. "("), then: */
		if (token[0] == '(')
			/*         push it onto the operator stack. */
		{
			printf("Push it to the operator stack\n");
			spush(token);
		}
		/*     if the token is a right paren (i.e. ")"), then: */
		if (token[0] == ')')
		{
			/*         while the operator at the top of the operator stack is not a left paren: */
			while (slen > 0 && stack[slen-1][0] != '(')
			{
				printf("Pop stack to output\n");

				/*             pop the operator from the operator stack onto the output queue. */
				qpush(spop());
				/*         #<{(| if the stack runs out without finding a left paren, then there are mismatched parentheses. |)}># */
			}

			/*         if there is a left paren at the top of the operator stack, then: */
			if (stack[slen-1][0] == '(')
			{
				printf("Pop stack\n");
				/*             pop the operator from the operator stack and discard it */
				spop();
			}
		}
	printf("Output queue: ");
	for (int a = 0; a < qlen; a++)
		printf("%s ", queue[a]);
	printf("	Operator stack: ");
	for (int a = 0; a < slen; a++)

		printf("%s ", stack[a]);
	printf("\n\n");
	}
	// end



	// after loop, if operator stack not null, pop everything to output queue
	// if there are no more tokens to read:
	//     while there are still operator tokens on the stack:
	while (slen > 0)
	{
		/*         #<{(| if the operator token on the top of the stack is a paren, then there are mismatched parentheses. |)}># */
		if (stack[slen-1][0] == '(' || stack[slen-1][0] == ')')
			printf("mismatched parenthesis\n");
		/*         pop the operator from the operator stack onto the output queue. */
		qpush(spop();)

	}
	/* exit. */

	// print final contents of stack and queue
	printf("Output queue: ");
	for (int a = 0; a < qlen; a++)
			printf("%s ", queue[a]);
	printf("	Operator stack: ");
	for (int a = 0; a < slen; a++)
			printf("%s ", stack[a]);
	printf("\n");


	//Getting the solution.
	result = evaluatePostfix(queue, qlen);	// evaluate postfix value read from stack.
	sprintf(&mathString, "%.2f", result);		//Store the reult in the string. Null terminate that badboi

	printf("Result: %g\n", result);
	printf("amount is %s\n", mathString);
}



void equalsPressed(){
	int diff = 0; 								//For calculating cursor position.
	mathParser();								//This has replaced the mathString with the float.
	mathStrLen = strlen(mathString);			//Update length of the string.

	diff = mathStrLen - MAX_DISP_STR;			//Get difference.

	BSP_LCD_SetTextColor (0xFFFF);				//Text Color: White.
	BSP_LCD_FillRect (81, 0, 239, 46);			//Write over screen.
	BSP_LCD_SetTextColor (LCD_COLOR_BLACK);		//Text Color: Black.

	if(diff <= 0){								//String length is less than screen.
		cursorPos = mathStrLen;
	}else{										//String is too long for screen so...
		cursorPos = 13;
	}

	printCursor(cursorPos);
	BSP_LCD_DisplayStringAt(85,13,mathString,LEFT_MODE);	//Display result on screen.
	HAL_Delay(1000);
}

















