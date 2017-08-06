#ifndef SPRITESHT_LIB_H_
#define SPRITESHT_LIB_H_

#include <stdbool.h>
#include <stdint.h>

#ifndef WHITGL_MATH_H_
typedef int64_t whitgl_int;

typedef struct
{
	whitgl_int x;
	whitgl_int y;
} whitgl_ivec;
static const whitgl_ivec whitgl_ivec_zero = {0,0};

#endif

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
	whitgl_ivec size;
	whitgl_ivec pos;
	whitgl_ivec offset;
	whitgl_ivec original_size;
} spritesht_sprite;

typedef struct
{
	whitgl_int max_sprites;
	whitgl_int num_sprites;
	spritesht_sprite* sprites;
} spritesht_spritesheet;

static const whitgl_int spritesht_magic_value = 0x9544fad7;

spritesht_spritesheet spritesht_create(whitgl_int max);
void spritesht_free(spritesht_spritesheet* sheet);
bool spritesht_add_sprite(spritesht_spritesheet* sheet, const char* file);
bool spritesht_save_image(spritesht_spritesheet* sheet, const char* file);
bool spritesht_save_meta(spritesht_spritesheet* sheet, const char* file);
bool spritesht_load_meta(spritesht_spritesheet* sheet, const char* file);
bool spritesht_save_meta_as_csv(spritesht_spritesheet* sheet, const char* file);


#endif // SPRITESHT_LIB_H_
