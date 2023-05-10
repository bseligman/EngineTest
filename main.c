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
   //Go through and stuff
   int ogx = x;
   file = fopen(sprite, "r");

    code = malloc(2000);
    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char) c;
    }

    // terminator w/ null char
    code[n] = '\0';        
	
   fclose(file);

   //for how many inputted pixels for sprite, set i
   for(int i =0; i<64;i++){
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
   	   for(int c=0;c<scale;c++){
   			SDL_RenderDrawPoint(renderer, x, y+c);
   		}
   	}
   	else if(code[i]=='\n'){
   		y=y+1;
   		x=ogx;
   	}
   	x=x+1;
   	}
   }
 }

///// LOAD ROOM FUNCTION
void LoadRoom(char* sprite, int scale, int np_x, int np_y)
{
	// Load Vars
   FILE *file;
   char *code;
   size_t n = 0;
   int c,x=np_x,y=np_y;

   // Open Map Visual Data
   file = fopen(sprite, "r");
    code = malloc(12000);
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
   	   SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
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
    code = malloc(16000);
    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char) c;
    }

    // terminator w/ null char
    code[n] = '\0';        
	
   fclose(file);

   //arrays need to be very big to hold room data jesus christ
   int anaray[1024][1024];

   //Go through and stuff
   int ogx = inpx;
   //for how many inputted pixels for sprite, set i
   for(int i =0; i<512;i++){
   	// for scale
   	for(int b=0;b<scale;b++){
   
   	if(code[i]=='1'){

   		// y fix
   		anaray[x][y]=1;
   		for(int c=0;c<scale;c++){
   			anaray[x][y+c]=1;
   		}
   	}
   	if(code[i] == '0'){
    		anaray[x][y] = 0;
   		for(int c=0;c<scale;c++){
     			anaray[x][y+c] = 0;
   		}   	
   	}
   	if(code[i] == '3'){
    		anaray[x][y] = 3;
   		for(int c=0;c<scale;c++){
     			anaray[x][y+c] = 3;
   		}   	
   	}
    	if(code[i] == '4'){
    		anaray[x][y] = 4;
   		for(int c=0;c<scale;c++){
   			anaray[x][y+c] = 4;
   		}   	
   	}
   	else if(code[i] == '\n'){
   		y=y+1;
   		x=ogx;
   	}
   	x=x+1;
   	}
   }
   return(anaray[inpx][inpy]);
 }





// MAIN LOOP / STARTING FUNC
int main( int argc, char* args[] )
{

	// COLLISION / WORLD SCALE
	int cscale=20;

	//// PLAYER VARS
	char* activer = "room1.txt";
	int xpos = 0;
	int ypos = 0;

	int center = 256;
	//Create window, base=128 (scaled*5)
	SDL_CreateWindowAndRenderer(512, 512, 0, &window, &renderer);

	// ROOM STATUS VARS 
	int loadroom1 = 0;


	////////////////////////////////// OVERWORLD LOOP
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

	///// LOAD ROOM MANAGER
	// Room Load
	LoadRoom(activer,cscale, xpos, ypos);
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
	DrawSprite("chartest.txt",256,256,4);

	//// DEBUG MODE
	// PLAYER POSITION
	// XY NEXT+1
	/*
	if (getCords(activer,cscale,256-xpos,ypos)==0) {
		DrawSprite("0.txt",20,200,4);
	}
	if (getCords(activer,cscale,256-xpos,ypos)==1) {
		DrawSprite("1.txt",20,200,4);
	}
	if (getCords(activer,cscale,camxpos+3,camypos)==2) {
		DrawSprite("2.txt",20,200,4);
	}
	if (getCords(activer,cscale,camxpos+3,camypos)==4) {
		DrawSprite("4.txt",20,200,4);
	}
	*/

	// DOWN
	if(ch == 115)
	{
		// equ: (center - ypos - (wanteed difference) + center
		if(getCords(activer,cscale,center,(center-ypos)+center+20) == 0) {
			ypos=ypos+5;
		}
	}

	// UP
	if(ch == 119)
	{
		if(getCords(activer,cscale,center,((center-ypos)-center-20) *-1) == 0) {
			ypos=ypos-5;
		}
	}
 
	// RIGHT
	if(ch == 100)
	{
		if(getCords(activer,cscale,(center-xpos)+20,center) == 0) {
			xpos=xpos-5;

		}
	}

	// LEFT
	if(ch == 97)
	{
		if(getCords(activer,cscale,center-xpos+20,center) == 0) {
			xpos=xpos+5;

		}
	}	

	//Debug Test

	//UP
	DrawSprite("chartest.txt",center-xpos,center,4);
	//DOWN
	DrawSprite("chartest.txt",center+xpos,center,4);
	//LEFT
	DrawSprite("chartest.txt",center,center+5,4);
	//RIGHT
	DrawSprite("chartest.txt",center,center-5,4);

	// Refresh the render/frame
	SDL_RenderPresent(renderer);

	}
	// Cleanup crew
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}