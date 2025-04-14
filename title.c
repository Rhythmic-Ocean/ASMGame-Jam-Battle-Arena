
#include "common.h"

#include "draw.h"
#include "highscores.h"
#include "stage.h"
#include "text.h"
#include "title.h"

extern App app;

static void logic(void);
static void draw(void);
static void drawLogo(void);

static int          timeout;
static SDL_Texture *battleArenaTexture;
static SDL_Texture *donkTexture[5];
static int          battleArenaY = -200;
static float        battleArenaDY = 0;
static float        donkAngle[5];

SDL_Texture *background;

void initTitle(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
	memset(&app.mouse, 0, sizeof(Mouse));


	battleArenaTexture = loadTexture("gfx/battleArena.png");

	background = loadTexture("gfx/background.png");	


	timeout = FPS * 5;
}

static void logic(void)
{
	int i;

	battleArenaDY = MIN(battleArenaDY + 0.25, 25);

	battleArenaY = MIN(battleArenaY + battleArenaDY, 200);

	if (battleArenaY == 200)
	{
		battleArenaDY = -battleArenaDY * 0.5;

		if (battleArenaDY > -1)
		{
			battleArenaDY = 0;
		}
	}

	for (i = 0; i < 5; i++)
	{
		donkAngle[i] = MIN(donkAngle[i] + 2, 360);
	}

	if (--timeout <= 0)
	{
		initHighscores();
	}

	if (app.mouse.button[SDL_BUTTON_LEFT])
	{
		initStage();
	}
}

static void draw(void)
{
	SDL_Rect dest = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopy(app.renderer, background, NULL, &dest);

	drawLogo();

	if (timeout % 40 < 20)
	{
		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "PRESS FIRE TO PLAY!");
	}
}

static void drawLogo(void)
{
	int x, i;

	blit(battleArenaTexture, SCREEN_WIDTH / 2, battleArenaY, 1);

	x = -300;

	for (i = 0; i < 5; i++)
	{
		blitRotated(donkTexture[i], (SCREEN_WIDTH / 2) + x, 350, donkAngle[i]);

		x += 150;
	}
}
