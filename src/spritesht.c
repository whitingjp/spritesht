
#include <spritesht_lib.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	spritesht_int w, h;
	spritesht_spritesheet sheet = spritesht_create(2);
	if(!spritesht_add_sprite(&sheet, "../../data/ball.png"))
	{
		printf("Failed to add ball\n");
		return 1;
	}
	if(!spritesht_add_sprite(&sheet, "../../data/shard.png"))
	{
		printf("Failed to add shard\n");
		return 1;
	}
	if(!spritesht_save(&sheet, "out.png"))
	{
		printf("Failed to save sheet\n");
		return 1;
	}
	spritesht_free(&sheet);
	return 0;
}
