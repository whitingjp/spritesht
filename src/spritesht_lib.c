
#include <spritesht_lib.h>

#include <png.h>
#include <stdlib.h>
#include <string.h>

spritesht_int _find_lowest_power(spritesht_int val);
bool _sys_load_png(const char *name, spritesht_int *width, spritesht_int *height, unsigned char **data);
bool _sys_save_png(const char *name, spritesht_int width, spritesht_int height, unsigned char *data);

spritesht_spritesheet spritesht_create(spritesht_int max)
{
	spritesht_spritesheet sheet;
	sheet.max_sprites = max;
	sheet.num_sprites = 0;
	sheet.sprites = malloc(sizeof(spritesht_sprite) * max);
	return sheet;
}
void spritesht_free(spritesht_spritesheet* sheet)
{
	spritesht_int i;
	for(i=0; i<sheet->num_sprites; i++)
		free(sheet->sprites[i].data);
	free(sheet->sprites);
}
bool spritesht_add_sprite(spritesht_spritesheet* sheet, const char* file)
{
	if(sheet->num_sprites >= sheet->max_sprites)
		return false;
	spritesht_sprite* sprite = &sheet->sprites[sheet->num_sprites];
	if(!_sys_load_png(file, &sprite->size.x, &sprite->size.y, &sprite->data))
		return false;
	strncpy(sprite->filename, file, 254);
	sprite->filename[255] = '\0';
	sheet->num_sprites++;
	return true;
}

typedef struct
{
	bool active;
	spritesht_vec size;
	spritesht_vec pos;
} spritesht_cell;


bool spritesht_layout(spritesht_spritesheet* sheet, spritesht_vec sheet_size)
{
	spritesht_int max_cells = sheet->num_sprites * 4; // TODO - Linked list?
	spritesht_cell *cells = malloc(sizeof(spritesht_cell)*max_cells);
	spritesht_int i;
	for(i=0; i<max_cells; i++)
		cells[i].active = false;
	spritesht_cell initial = {true, sheet_size, spritesht_vec_zero};
	cells[0] = initial;
	spritesht_vec pos = spritesht_vec_zero;
	for(i=0; i<sheet->num_sprites; i++)
	{
		spritesht_int index = -1;
		spritesht_int j;
		for(j=0; j<max_cells; j++)
		{
			bool ok = true;
			if(!cells[j].active) ok = false;
			if(cells[j].size.x < sheet->sprites[i].size.x) ok = false;
			if(cells[j].size.y < sheet->sprites[i].size.y) ok = false;
			if(!ok)
				continue;
			index = j;
		}
		if(index == -1)
			return false;

		sheet->sprites[i].pos = cells[index].pos;

		spritesht_cell old = cells[index];
		if(old.size.y > sheet->sprites[i].size.y)
		{
			spritesht_int new_index = -1;
			for(j=0; j<max_cells; j++)
			{
				if(!cells[j].active)
				{
					new_index = j;
					break;
				}
			}
			if(new_index == -1) return false;
			cells[index].size.y = sheet->sprites[i].size.y;
			spritesht_cell newcell = {true, {old.size.x, old.size.y-cells[index].size.y}, {old.pos.x, old.pos.y+cells[index].size.y}};
			cells[new_index] = newcell;
		}
		old = cells[index];
		if(old.size.x > sheet->sprites[i].size.x)
		{
			spritesht_int new_index = -1;
			for(j=0; j<max_cells; j++)
			{
				if(!cells[j].active)
				{
					new_index = j;
					break;
				}
			}
			if(new_index == -1) return false;
			cells[index].size.x = sheet->sprites[i].size.x;
			spritesht_cell newcell = {true, {old.size.x-cells[index].size.x, old.size.y}, {old.pos.x+cells[index].size.x, old.pos.y}};
			cells[new_index] = newcell;
		}
		cells[index].active = false;
	}
	free(cells);
	return true;
}

bool spritesht_save(spritesht_spritesheet* sheet, const char* file)
{
	spritesht_int i;
	spritesht_vec size = {1024,1024};

	bool width_next = true;
	while(true)
	{
		if(spritesht_layout(sheet, size))
			break;
		if(width_next) size.x <<= 1;
		else size.y <<= 1;
		width_next = !width_next;
		if(size.x > 4096) // TODO Don't hard code this limit
			return false;
	}

	unsigned char* out_data = malloc(size.x*size.y*4);
	memset(out_data, '\0', size.x*size.y*4);

	for(i=0; i<sheet->num_sprites; i++)
	{
		spritesht_vec p = sheet->sprites[i].pos;
		spritesht_int row;
		for(row=0; row<sheet->sprites[i].size.y; row++)
		{
			unsigned char* src_start = &sheet->sprites[i].data[row*sheet->sprites[i].size.x*4];
			unsigned char* dst_start = &out_data[(p.x+(p.y+row)*size.x)*4];
			memcpy(dst_start, src_start, 4*sheet->sprites[i].size.x);
		}
	}

	bool success = _sys_save_png(file, size.x, size.y, out_data);
	free(out_data);
	return success;
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
