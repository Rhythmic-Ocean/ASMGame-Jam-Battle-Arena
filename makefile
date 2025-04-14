
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

main: \
  bullets.c camera.c draw.c effects.c enemies.c entities.c highscores.c init.c input.c items.c main.c player.c sound.c stage.c text.c title.c util.c    
	gcc -o main $^ $(LDFLAGS)
