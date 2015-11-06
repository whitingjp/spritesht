
#include <spritesht_lib.h>
#include <stdlib.h>

int main()
{
	spritesht_int w, h;
	unsigned char *data;
	if(!_sys_load_png("../../data/ball.png", &w, &h, &data))
		return 1;
	if(!_sys_save_png("out.png", w, h, data))
		return 1;
	free(data);
	return 0;
}
