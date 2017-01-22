
#include <spritesht_lib.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

whitgl_int randint(whitgl_int size)
{
	return rand() % size;
}

int main()
{
	time_t t;
 	srand((unsigned) time(&t));

 	whitgl_int num_sprites = 50;

	whitgl_int i;
	spritesht_spritesheet sheet = spritesht_create(num_sprites);
	for(i=0; i<num_sprites; i++)
	{
		whitgl_ivec size;
		size.x = randint(32)+1;
		size.y = randint(32)+1;
		spritesht_col col;
		col.r = randint(256);
		col.g = col.r*0.4;
		col.b = col.r*0.4;
		col.a = 0xff;
		if(!spritesht_add_fake_sprite(&sheet, size, col))
		{
			printf("Failed to add fake sprite\n");
			return 1;
		}
	}

	if(!spritesht_save_image(&sheet, "out.png"))
	{
		printf("Failed to save sheet\n");
		return 1;
	}
	spritesht_free(&sheet);
	return 0;
}
