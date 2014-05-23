#include "SDL/SDL.h"
#define SCREEN_W 800
#define SCREEN_H 600
#define W 8
#define H 6
char running = 1;
int posX;
int posY;

typedef enum FIELD_TYPE {

	FIELD_PATH = 0,
	FIELD_FINAL = 1,
	FIELD_SPIDER = 2,
	FIELD_WALL = 3,
	FIELD_BOX = 4

} fieldType_e;

fieldType_e map[W][H];

SDL_Surface* Surf_Display;
SDL_Surface* Surf_Final;
SDL_Surface* Surf_Path;
SDL_Surface* Surf_Wall;

SDL_Surface* Surf_Spider;
SDL_Surface* Surf_Box;

void OnKeyDowndd(SDLKey sym) {
	switch (sym) {

	case (SDLK_d): {

		break;
	}
	case (SDLK_a): {

		break;
	}
	case (SDLK_w): {

		break;
	}
	case (SDLK_s): {

		break;
	}
	default: {
	}
	}

}

void OnEvent(SDL_Event* Event) {

	switch (Event->type) {
	case (SDL_QUIT): {
		running = 0;
		break;
	}
	case (SDL_KEYDOWN): {
		OnKeyDowndd(Event->key.keysym.sym);
		break;
	}
	case (SDL_KEYUP): {
		break;
	}
	case (SDL_MOUSEBUTTONDOWN): {
		break;
	}
	}
}

int displaySurface(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
	if (Surf_Dest == NULL || Surf_Src == NULL) {
		return 0;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

	return 0;
}

void doLogic() {
	posX = 200;
	posY = 200;
	/*posX += speed*accelerationX;

	 if((posX < 0))
	 {
	 posX = 0;
	 }
	 else if ( posX > (SCREEN_W - size))
	 {
	 posX = SCREEN_W - size ;

	 }

	 posY += speed*accelerationY;

	 if (posY < 0)
	 {
	 posY = 0;
	 }
	 else if (posY > (SCREEN_H - size))
	 {
	 posY = SCREEN_H - size;
	 }
	 */}

void doGraphics() {

	int i, j;
	for (i = 0; i < W; i++) {
		for (j = 0; j < H; j++) {

			switch (map[i][j]) {

			case (FIELD_FINAL): {
				displaySurface(Surf_Display, Surf_Final, i * Surf_Final->w,
						j * Surf_Final->h);
				break;
			}
			case (FIELD_PATH): {
				displaySurface(Surf_Display, Surf_Path, i * Surf_Path->w,
						j * Surf_Path->h);
				break;
			}
			case (FIELD_WALL): {
				displaySurface(Surf_Display, Surf_Wall, i * Surf_Wall->w,
						j * Surf_Wall->h);

				break;
			}
			case (FIELD_BOX): {
				displaySurface(Surf_Display, Surf_Box, i * Surf_Box->w,
						j * Surf_Box->h);

				break;
			}
			case (FIELD_SPIDER): {
				displaySurface(Surf_Display, Surf_Spider, i * Surf_Spider->w,
						j * Surf_Spider->h);

				break;
			}

			default: {
			}
			}

		}
	}
	displaySurface(Surf_Display, Surf_Spider, posX, posY);
}

int main(int argc, char* args[]) {
	int i, j;

	for (i = 0; i < W; i++) {
		for (j = 0; j < H; j++) {
			map[i][j] = FIELD_PATH;
		}
	}
	map[4][1] = FIELD_BOX;
	map[6][5] = FIELD_FINAL;
	map[6][6] = FIELD_FINAL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return 0;
	}
	SDL_EnableKeyRepeat(20, 1);

	if ((Surf_Display = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32,
	SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
		return 0;
	}

	if ((Surf_Path = SDL_LoadBMP("path.bmp")) == NULL) {
		printf("error while loading BMP\n");
	}
	if ((Surf_Final = SDL_LoadBMP("final.bmp")) == NULL) {
		printf("error while loading BMP\n");
	}

	if ((Surf_Spider = SDL_LoadBMP("spider.bmp")) == NULL) {

		printf("error while loading BMP\n");
	}

	if ((Surf_Box = SDL_LoadBMP("box.bmp")) == NULL) {

		printf("error while loading BMP\n");

	}
	//Uint32 colorkey = SDL_MapRGB( Surf_Spider->format, 0, 0, 0 );
	//SDL_SetColorKey(Surf_Spider, SDL_SRCCOLORKEY, colorkey);

	if ((Surf_Wall = SDL_LoadBMP("wall.bmp")) == NULL) {
		printf("error while loading BMP\n");
	}

	SDL_Event Event;

	while (running) {

		while (SDL_PollEvent(&Event)) {
			OnEvent(&Event);
		}

		SDL_FillRect(Surf_Display, NULL, 12852252);

		doLogic();
		doGraphics();

		SDL_Flip(Surf_Display);

	}

}

