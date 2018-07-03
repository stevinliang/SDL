#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "stdbool.h"
#include "string.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Surface *image = NULL;
SDL_Surface *screen = NULL;

SDL_Event event;

SDL_Surface *load_image(char *filename)
{
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;
	loadedImage = IMG_Load(filename);

	if (loadedImage != NULL) {
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, destination, &offset);
}


bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if (screen == NULL) {
		return false;
	}

	SDL_WM_SetCaption("Event Test", NULL);

	return true;
}

bool load_files()
{
	image = load_image("hello.jpg");
	if (image == NULL) {
		return false;
	}

	return true;
}

void clean_up()
{
	SDL_FreeSurface(image);
	SDL_Quit;
}

int main(int argc, char *argv[])
{
	bool quit = false;

	if (init() == false) {
		return 1;
	}

	if (load_files() == false)
	{
		return 1;
	}

	apply_surface(0, 0, image, screen);

	if (SDL_Flip(screen) == -1)
	{
		return 1;
	}

	while (quit == false) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		} else {
			SDL_Delay(50);
		}
	}

	clean_up();

	return 0;
}