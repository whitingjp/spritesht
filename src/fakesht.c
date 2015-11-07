
#include <spritesht_lib.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

spritesht_int randint(spritesht_int size)
{
	return rand() % size;
}

int main()
{
	time_t t;
 	srand((unsigned) time(&t));

 	spritesht_int num_sprites = 5;

	spritesht_int i;
	spritesht_spritesheet sheet = spritesht_create(num_sprites);
	for(i=0; i<num_sprites; i++)
	{
		spritesht_vec size;
		size.x = randint(128);
		size.y = randint(128);
		spritesht_col col;
		col.r = randint(256);
		col.g = randint(256);
		col.b = randint(256);
		col.a = 0xff;
		if(!spritesht_add_fake_sprite(&sheet, size, col))
		{
			printf("Failed to add fake sprite\n");
			return 1;
		}
	}

	if(!spritesht_save(&sheet, "out.png"))
	{
		printf("Failed to save sheet\n");
		return 1;
	}
	spritesht_free(&sheet);
	return 0;
}
