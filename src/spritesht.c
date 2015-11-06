
#include <spritesht_lib.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	spritesht_int i;
	spritesht_spritesheet sheet = spritesht_create(512);
	for(i=1; i<argc; i++)
	{
		if(spritesht_add_sprite(&sheet, argv[i]))
			continue;
		printf("Failed to add %s\n", argv[i]);
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
