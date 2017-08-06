
#include <spritesht_lib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const char* _usage = "\n\
usage:\n\
  ./spritesht --png sheet.png [--dat sheet.dat] [--csv sheet.csv] [--max 4096] [--margin 2] input/*.png\n\
\n";

int main(int argc, char** argv)
{
	whitgl_int i;
	spritesht_spritesheet sheet = spritesht_create(argc);

	whitgl_int max_image_size = 4096;
	whitgl_int margin = 2;
	char* png = NULL;
	char* dat = NULL;
	char* csv = NULL;

	for(i=1; i<argc; i++)
	{
		if(strncmp(argv[i], "--png", 5) == 0)
		{
			if(i == argc-1)
			{
				printf("No argument for --png");
				printf("%s", _usage);
				return 1;
			}
			png = argv[++i];
			continue;
		}
		if(strncmp(argv[i], "--dat", 5) == 0)
		{
			if(i == argc-1)
			{
				printf("No argument for --dat\n");
				printf("%s", _usage);
				return 1;
			}
			dat = argv[++i];
			continue;
		}
		if(strncmp(argv[i], "--csv", 5) == 0)
		{
			if(i == argc-1)
			{
				printf("No argument for --csv\n");
				printf("%s", _usage);
				return 1;
			}
			csv = argv[++i];
			continue;
		}
		if(strncmp(argv[i], "--max", 5) == 0)
		{
			if(i == argc-1)
			{
				printf("No argument for --max\n");
				printf("%s", _usage);
				return 1;
			}
			max_image_size = atoi(argv[++i]);
			if(max_image_size == 0)
			{
				printf("Invalid size for --max, must be an integer > 0");
				printf("%s", _usage);
				return 1;
			}
			continue;
		}
		if(strncmp(argv[i], "--margin", 5) == 0)
		{
			if(i == argc-1)
			{
				printf("No argument for --margin\n");
				printf("%s", _usage);
				return 1;
			}
			margin = atoi(argv[++i]);
			if(margin == 0)
			{
				printf("Invalid size for --margin, must be an integer > 0");
				printf("%s", _usage);
				return 1;
			}
			continue;
		}
		if(spritesht_add_sprite(&sheet, argv[i]))
			continue;
		printf("Failed to add %s\n", argv[i]);
		printf("%s", _usage);
		return 1;
	}

	if(sheet.num_sprites == 0)
	{
		printf("No sprites added to spritesheet\n");
		printf("%s", _usage);
		return 1;
	}

	if(!spritesht_layout(&sheet, max_image_size, margin))
	{
		printf("Failed to layout sprites in %dx%d image\n", (int)max_image_size, (int)max_image_size);
		printf("%s", _usage);
		return 1;
	}

	if(!png)
	{
		printf("No output --png\n");
		printf("%s", _usage);
		return 1;
	}

	if(png)
	{
		if(!spritesht_save_image(&sheet, png))
		{
			printf("Failed to save sheet\n");
			return 1;
		}
	}
	if(dat)
	{
		if(!spritesht_save_meta(&sheet, dat))
		{
			printf("Failed to save meta\n");
			return 1;
		}
	}
	if(csv)
	{
		if(!spritesht_save_meta_as_csv(&sheet, csv))
		{
			printf("Failed to save csv\n");
			return 1;
		}
	}
	spritesht_free(&sheet);
	return 0;
}
