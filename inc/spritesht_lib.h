#ifndef SPRITESHT_LIB_H_
#define SPRITESHT_LIB_H_

#include <stdbool.h>
#include <stdint.h>
typedef int64_t spritesht_int;

typedef struct
{
	spritesht_int x;
	spritesht_int y;
} spritesht_vec;
static const spritesht_vec spritesht_vec_zero = {0,0};

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} spritesht_col;

typedef struct
{
	char filename[256];
	unsigned char* data;
	spritesht_vec size;
	spritesht_vec pos;
} spritesht_sprite;

typedef struct
{
	spritesht_int max_sprites;
	spritesht_int num_sprites;
	spritesht_sprite* sprites;
} spritesht_spritesheet;

spritesht_spritesheet spritesht_create(spritesht_int max);
void spritesht_free(spritesht_spritesheet* sheet);
bool spritesht_add_sprite(spritesht_spritesheet* sheet, const char* file);
bool spritesht_add_fake_sprite(spritesht_spritesheet* sheet, spritesht_vec size, spritesht_col col);
bool spritesht_save(spritesht_spritesheet* sheet, const char* file);

#endif // SPRITESHT_LIB_H_
