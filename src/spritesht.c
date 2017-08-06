
#include <spritesht_lib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	whitgl_int i;
	spritesht_spritesheet sheet = spritesht_create(argc);

	char* png = NULL;
	char* dat = NULL;
	char* csv = NULL;

	for(i=1; i<argc; i++)
	{
		if(strncmp(argv[i], "--png", 5) == 0)
		{
			if(i == argc-1)
			{
				printf("No argument for --png\n");
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
				return 1;
			}
			csv = argv[++i];
			continue;
		}
		if(spritesht_add_sprite(&sheet, argv[i]))
			continue;
		printf("Failed to add %s\n", argv[i]);
		return 1;
	}

	if(!png)
	{
		printf("No output --png\n");
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
