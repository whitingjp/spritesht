
#include <spritesht_lib.h>

#include <png.h>
#include <stdlib.h>
#include <string.h>

bool _sys_load_png(const char *name, spritesht_int *width, spritesht_int *height, unsigned char **data);
bool _sys_save_png(const char *name, spritesht_int width, spritesht_int height, unsigned char *data);

spritesht_spritesheet spritesht_create(spritesht_int size)
{
	spritesht_spritesheet sheet;
	sheet.size = size;
	sheet.num_sprites = 0;
	sheet.sprites = malloc(sizeof(spritesht_sprite) * size);
	return sheet;
}
void spritesht_free(spritesht_spritesheet* sheet)
{
	free(sheet->sprites);
}
bool spritesht_add_sprite(spritesht_spritesheet* sheet, const char* file)
{
	return false;
}
bool spritesht_save(spritesht_spritesheet* sheet, const char* file)
{
	return false;
}

bool _sys_load_png(const char *name, spritesht_int *width, spritesht_int *height, unsigned char **data)
{
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	int color_type, interlace_type;
	FILE *fp;

	if ((fp = fopen(name, "rb")) == NULL)
		return false;

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
									 NULL, NULL, NULL);

	if (png_ptr == NULL) {
		fclose(fp);
		return false;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return false;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		/* Free all of the memory associated
		 * with the png_ptr and info_ptr */
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		/* If we get here, we had a
		 * problem reading the file */
		return false;
	}

	png_init_io(png_ptr, fp);

	png_set_sig_bytes(png_ptr, sig_read);

	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	png_uint_32 read_width, read_height;
	int bit_depth;
	png_get_IHDR(png_ptr, info_ptr, &read_width, &read_height, &bit_depth, &color_type,
				 &interlace_type, NULL, NULL);
	if(width)
		*width = read_width;
	if(height)
		*height = read_height;

	unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	if(data)
	{
		*data = (unsigned char*) malloc(row_bytes * read_height);

		png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

		png_uint_32 i;
		for (i = 0; i < read_height; i++)
		{
			memcpy(*data+(row_bytes * (i)), row_pointers[i], row_bytes);
		}
	}
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);

	return true;
}
bool _sys_save_png(const char *name, spritesht_int width, spritesht_int height, unsigned char *data)
{
	FILE *fp = fopen(name, "wb");
	if(!fp) return false;

	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png) return false;

	png_infop info = png_create_info_struct(png);
	if (!info) return false;

	if (setjmp(png_jmpbuf(png))) return false;

	png_init_io(png, fp);

	png_uint_32 png_width = width;
	png_uint_32 png_height = height;

	// Output is 8bit depth, RGBA format.
	png_set_IHDR(
		png,
		info,
		png_width, png_height,
		8,
		PNG_COLOR_TYPE_RGBA,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
	);
	png_write_info(png, info);

	png_byte ** row_pointers = png_malloc (png, png_height * sizeof (png_byte *));
	spritesht_int y;
	for (y = 0; y < height; ++y)
	{
		spritesht_int size = sizeof (uint8_t) * png_width * 4;
		row_pointers[y] = &data[size*y];
	}

	png_write_image(png, row_pointers);
	png_write_end(png, NULL);

	fclose(fp);

	return true;
}
