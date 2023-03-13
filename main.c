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

   	else if(code[i]=='2'){
   		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 128);
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
    code = malloc(1500);
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
   	if(code[i] == '0'){
   	   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
   		for(int c=0;c<scale;c++){
   			SDL_RenderDrawPoint(renderer, x, y+c);
   		}   	
   	}
   	if(code[i] == '3'){
   	   SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
   		for(int c=0;c<scale;c++){
   			SDL_RenderDrawPoint(renderer, x, y+c);
   		}   	
   	}
    	if(code[i] == '4'){
   	   SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
   		for(int c=0;c<scale;c++){
   			SDL_RenderDrawPoint(renderer, x, y+c);
   		}   	
   	}
   	else if(code[i] == '\n'){
   		y=y+1;
   		x=ogx;
   	}
   	x=x+1;
   	}
   }
 }


///// Get Room Position
int getCords(char* sprite, int scale, int inpx, int inpy)
{
	// Load Vars
   FILE *file;
   char *code;
   size_t n = 0;
   int c,x=0,y=0;

   // Open Map Visual Data
   file = fopen(sprite, "r");
    code = malloc(1500);
    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char) c;
    }

    // terminator w/ null char
    code[n] = '\0';        
	
   fclose(file);

   //arrays need to be very big to hold room data jesus christ
   int anaray[441][441];

   //Go through and stuff
   int ogx = x;
   int playerx = 0;
   int playery = 0;
   //for how many inputted pixels for sprite, set i
   for(int i =0; i<256;i++){
   	// for scale
   	for(int b=0;b<scale;b++){
   	// Filled Tile
   	if(code[i]=='1'){
   		anaray[x][y]=1;
   		// y fix
   		for(int c=0;c<scale;c++){
   			anaray[x][y+c]=1;
   		}
   	}
   	// Air Tile
   	else if(code[i] == '0'){
   		for(int c=0;c<scale;c++){
   			anaray[x][y+c]=0;
   		}   	
   	}
   	// Spawn Tile
   	else if(code[i] == '3'){
   		for(int c=0;c<scale;c++) {
   			anaray[x][y+c]=3;
   		} 
   	}
   	// Load R Tile
   	else if(code[i] == '4'){
   		for(int c=0;c<scale;c++) {
   			anaray[x][y+c]=4;
   		} 
   	}
   	else{
   		y=y+1;
   		x=0;
   	}
   	x=x+1;
   	}
	}
   return(anaray[inpx][inpy]);
}





// Main Starting Function
int main( int argc, char* args[] )
{
	//// PLAYER VARS
	char* activer = "room1.txt";
	int xpos = 10;
	int ypos = 10;
	//Create window, base=128 (scaled*5)
	SDL_CreateWindowAndRenderer(512, 512, 0, &window, &renderer);

	// ROOM STATUS VARS
	int loadroom1 = 0;

	//// OVERWORLD LOOP
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

	// COLLISION SCALE
	int cscale=10;

	///// LOAD ROOM MANAGER
	// Room Load
	LoadRoom(activer,cscale);
	if (loadroom1 == 1) {
		activer = "room2.txt";
		loadroom1=0;
	}

	// Check Loading Status
	// R LOAD
	if(getCords(activer,cscale,xpos+1,ypos) == 4) {
		loadroom1 = 1;
		xpos= 10;
		ypos= 10;
	}

   //Draw Player
	DrawSprite("chartest.txt",xpos,ypos,1);

	//// DEBUG MODE
	// PLAYER POSITION
	// XY NEXT+1
	if (getCords(activer,cscale,xpos+3,ypos)==0) {
		DrawSprite("0.txt",20,200,4);
	}
	if (getCords(activer,cscale,xpos+3,ypos)==1) {
		DrawSprite("1.txt",20,200,4);
	}
	if (getCords(activer,cscale,xpos+3,ypos)==2) {
		DrawSprite("2.txt",20,200,4);
	}
	if (getCords(activer,cscale,xpos+3,ypos)==4) {
		DrawSprite("4.txt",20,200,4);
	}

	//UP
	if(ch == 119)
	{
		if(getCords(activer,cscale,xpos,ypos-3) == 0) {
			ypos=ypos-3;
		}
	}

	// DOWN
	if(ch == 115)
	{
		if(getCords(activer,cscale,xpos,ypos+3) == 0) {
			ypos=ypos+3;
		}
	}
 
	//LEFT
	if(ch == 97)
	{
		if(getCords(activer,cscale,xpos-3,ypos) == 0) {
			xpos=xpos-3;
		}
	}

	//RIGHT
	if(ch == 100)
	{
		// Check boundry collision
		if(getCords(activer,cscale,xpos+3,ypos) == 0) {
			xpos=xpos+3;
		}	
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