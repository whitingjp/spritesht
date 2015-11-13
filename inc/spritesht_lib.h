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
	spritesht_vec offset;
	spritesht_vec original_size;
} spritesht_sprite;

typedef struct
{
	spritesht_int max_sprites;
	spritesht_int num_sprites;
	spritesht_sprite* sprites;
} spritesht_spritesheet;

static const spritesht_int spritesht_magic_value = 0x9544fad7;

spritesht_spritesheet spritesht_create(spritesht_int max);
void spritesht_free(spritesht_spritesheet* sheet);
bool spritesht_add_sprite(spritesht_spritesheet* sheet, const char* file);
bool spritesht_add_fake_sprite(spritesht_spritesheet* sheet, spritesht_vec size, spritesht_col col);
bool spritesht_save_image(spritesht_spritesheet* sheet, const char* file);
bool spritesht_save_meta(spritesht_spritesheet* sheet, const char* file);
bool spritesht_load_meta(spritesht_spritesheet* sheet, const char* file);
bool spritesht_save_meta_as_csv(spritesht_spritesheet* sheet, const char* file);


#endif // SPRITESHT_LIB_H_
