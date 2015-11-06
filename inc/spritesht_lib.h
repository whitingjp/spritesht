#ifndef SPRITESHT_LIB_H_
#define SPRITESHT_LIB_H_

#include <stdbool.h>
#include <stdint.h>
typedef int64_t spritesht_int;

typedef struct
{
	const char* filename;
	const unsigned char* data;
	spritesht_int width;
	spritesht_int height;
	spritesht_int x;
	spritesht_int y;
} spritesht_sprite;

typedef struct
{
	spritesht_int size;
	spritesht_int num_sprites;
	spritesht_sprite* sprites;
} spritesht_spritesheet;

spritesht_spritesheet spritesht_create(spritesht_int size);
void spritesht_free(spritesht_spritesheet* sheet);
bool spritesht_add_sprite(spritesht_spritesheet* sheet, const char* file);
bool spritesht_save(spritesht_spritesheet* sheet, const char* file);

#endif // SPRITESHT_LIB_H_
