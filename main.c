// Import libraries
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>

//Declare renderer and window
SDL_Renderer* renderer;
SDL_Window* window;

// ADD ALL IN A ARRAY FUNCTION
int addAll(char input[]) 
{
	int ult = 0;
	for(int i=0;i<strlen(input);i++){
		// quick fix
		if(input[i]  !='-') {
			int te = input[i];
			ult = ult + te;
		}
		else{
			i=i+1;
			continue;
		}
	}
	return ult;
}

///// DRAW SPRITE FUNCTION
void DrawSprite()
{
	// File Set
	FILE* fptr;
	char* data;
	// Set BuffLength and Buffer vars
	int bufferLength = 255;
	char buffer[bufferLength];

	// Open File
	fptr = fopen("chartest.txt", "r");
	// Error handler
	if (fptr == NULL) {
		perror("Failed: ");
		return;
	}

	// Get each data piece
	char listo[] = "";
	while(fgets(buffer, bufferLength, fptr))
	{
		char* data = buffer;
		//Add to string
		for(int i=0;i<strlen(data);i++)
		{
		//printf("%d",data[i]);
		listo[i] = data[i];
		}
		printf("%d", addAll(listo));
	}

	fclose(fptr);


	// Set render color
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// Draw a point
	SDL_RenderDrawPoint(renderer, 50, 50);
}




// Main Starting Function
int main( int argc, char* args[] )
{
	//// PLAYER VARS
	int xpos = 200;
	int ypos = 200;

	//Create window
	SDL_CreateWindowAndRenderer(350, 350, 0, &window, &renderer);

	// MAIN Loop
	while (true) {
	// Get next event
	SDL_Event event;

	///// KEYBORAD input
	// Init ncurse
	initscr();
	cbreak();
	char ch = getch();
	printf("%d", ch);
	// UP
	if(ch == 119)
		{
			ypos=ypos-1;
		}
	// DOWN
	if(ch == 115)
		{
			ypos=ypos+1;
		}
	// LEFT
	if(ch == 97)
	{
		xpos=xpos-1;
	}
	// RIGHT
	if(ch == 100)
	{
		xpos=xpos+1;
	}

	    // Set render color
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		// Draw a point
		SDL_RenderDrawPoint(renderer, xpos, ypos);
		DrawSprite();
		// Refresh the render/frame
		SDL_RenderPresent(renderer);

	}
	// Cleanup crew
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}