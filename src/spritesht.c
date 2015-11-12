
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

	if(!spritesht_save_image(&sheet, "out.png"))
	{
		printf("Failed to save sheet\n");
		return 1;
	}
	if(!spritesht_save_meta(&sheet, "out.dat"))
	{
		printf("Failed to save meta\n");
		return 1;
	}
	if(!spritesht_save_meta_as_csv(&sheet, "out.csv"))
	{
		printf("Failed to save csv\n");
		return 1;
	}
	spritesht_free(&sheet);
	return 0;
}
