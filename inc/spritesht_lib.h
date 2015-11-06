#ifndef SPRITESHT_LIB_H_
#define SPRITESHT_LIB_H_

#include <stdbool.h>
#include <stdint.h>
typedef int64_t spritesht_int;

bool _sys_load_png(const char *name, spritesht_int *width, spritesht_int *height, unsigned char **data);
bool _sys_save_png(const char *name, spritesht_int width, spritesht_int height, unsigned char *data);

#endif // SPRITESHT_LIB_H_
