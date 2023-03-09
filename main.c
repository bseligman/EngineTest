// Import libraries
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <dirent.h>

//Declare renderer and window
SDL_Renderer* renderer;
SDL_Window* window;

// FILL FUNCTION
void fillscreen(int color1, int color2, int color3) {
	SDL_SetRenderDrawColor(renderer, color1, color2, color3, 0);
	for(int i=0;i<512;i++){
		for(int b=0;b<512;b++){
			 SDL_RenderDrawPoint(renderer, i, b);
		}
	}
}

// INT SUBSTR FUNCTION
int substring(int input, int enter) 
{
	return input;
}


/*
// FIND A NUM FUNCTION
int findNum(char input[], int find) 
{
	for(int i=0;i<strlen(input);i++)
	{
		if(input[i]==find)
		{
			return(i);
		}
	}
	return 5;
}
*/


///// DRAW SPRITE FUNCTION
void DrawSprite(char* sprite, int x, int y, int scale)
{
   FILE *file;
   char *code;
   size_t n = 0;
   int c;

   file = fopen(sprite, "r");

    code = malloc(1000);
    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char) c;
    }

    // terminator w/ null char
    code[n] = '\0';        
	
   fclose(file);

   //Go through and stuff
   int ogx = x;
   //for how many inputted pixels for sprite, set i
   for(int i =0; i<128;i++){
   	// for scale
   	for(int b=0;b<scale;b++){
   
   	if(code[i]=='1'){
   		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
   		SDL_RenderDrawPoint(renderer, x, y);
   		// y fix
   		for(int c=0;c<scale;c++){
   			SDL_RenderDrawPoint(renderer, x, y+c);
   		}
   	}
   	else if(code[i] == '0'){
   	   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
   	   SDL_RenderDrawPoint(renderer, x, y);
   	}
   	else{
   		y=y+1;
   		x=ogx;
   	}
   	x=x+1;
   	 }
   }
 
}

// Get X cords
int getXCords(char* sprite)
{
   FILE *file;
   char *code;
   size_t n = 0;
   int c, x=0,y=0;
   file = fopen(sprite, "r");
    code = malloc(1000);
    while ((c = fgetc(file)) != EOF)
    {
      code[n++] = (char) c;
    }

    // terminator w/ null char
    code[n] = '\0';        
   fclose(file);
   //Go through and stuff
   int ogx = x;
   //for how many inputted pixels for sprite, set i
   for(int i =0; i<128;i++){
   	if(code[i] == '3'){
   		return(x);
   }
   	else{
   		y=y+1;
   		x=ogx;
   	}
   	x=x+1;
   	}
   }

// Get Y cords
int getYCords(char* sprite)
{
   FILE *file;
   char *code;
   size_t n = 0;
   int c, x=0,y=0;
   file = fopen(sprite, "r");
    code = malloc(1000);
    while ((c = fgetc(file)) != EOF)
    {
      code[n++] = (char) c;
    }

    // terminator w/ null char
    code[n] = '\0';        
   fclose(file);
   //Go through and stuff
   int ogx = x;
   //for how many inputted pixels for sprite, set i
   for(int i =0; i<128;i++){
   	if(code[i] == '3'){
   		return(y);
   }
   	else{
   		y=y+1;
   		x=ogx;
   	}
   	x=x+1;
   	}
   }




///// LOAD ROOM FUNCTION
void LoadRoom(char* sprite, int scale)
{
	// Load Vars
   FILE *file;
   char *code;
   size_t n = 0;
   int c,x=0,y=0;

   // Open Map Visual Data
   file = fopen(sprite, "r");
    code = malloc(1000);
    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char) c;
    }

    // terminator w/ null char
    code[n] = '\0';        
	
   fclose(file);

   //Go through and stuff
   int ogx = x;
   int playerx = 0;
   int playery = 0;
   //for how many inputted pixels for sprite, set i
   for(int i =0; i<512;i++){
   	// for scale
   	for(int b=0;b<scale;b++){
   
   	if(code[i]=='1'){
   		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
   		SDL_RenderDrawPoint(renderer, x, y);
   		// y fix
   		for(int c=0;c<scale;c++){
   			SDL_RenderDrawPoint(renderer, x, y+c);
   		}
   	}
   	else if(code[i] == '0'){
   	   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
   		for(int c=0;c<scale;c++){
   			SDL_RenderDrawPoint(renderer, x, y+c);
   		}   	}
   	else if(code[i] == '3'){
   	   SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
   		for(int c=0;c<scale;c++){
   			SDL_RenderDrawPoint(renderer, x, y+c);
   		}   	}
   	else{
   		y=y+1;
   		x=ogx;
   	}
   	x=x+1;
   	 }
   }
 }


// Main Starting Function
int main( int argc, char* args[] )
{
	//// PLAYER VARS
	char* activer = "room1.txt";
	int xpos = getXCords(activer);
	int ypos = getYCords(activer);


	//Create window
	//base=128 scaled=512, 5*
	SDL_CreateWindowAndRenderer(512, 512, 0, &window, &renderer);



	// MAIN Loop
	while (true) {
	// Get next event
	SDL_Event event;

	///// KEYBORAD input
	// Init ncurse/keyb input
	initscr();
	cbreak();
	char ch = getch();

	//Draw Background
	fillscreen(0,0,0);
	//Load Room
	LoadRoom(activer,12);
   //Draw Player
	DrawSprite("chartest.txt",xpos,ypos,2);

	// UP
	if(ch == 119)
		{
			ypos=ypos-10;
		}
	// DOWN
	if(ch == 115)
		{
			ypos=ypos+10;
		}
	// LEFT
	if(ch == 97)
	{
		xpos=xpos-10;
	}
	// RIGHT
	if(ch == 100)
	{
		xpos=xpos+10;
	}

	// Refresh the render/frame
	SDL_RenderPresent(renderer);

	}
	// Cleanup crew
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}