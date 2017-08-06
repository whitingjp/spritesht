SRC = src
INC = inc
BUILD = build
OBJ = $(BUILD)/obj
OUT = $(BUILD)/out

CFLAGS = -Iinput/libpng -Iinc -g
LDFLAGS = -Linput/libpng -Linput/zlib -lpng -lz
DEP = $(INC)/spritesht_lib.h

all: $(OUT)/spritesht $(OUT)/spritesht.a

clean:
	rm -rf $(BUILD)

$(OBJ)/%.o: $(SRC)/%.c $(DEP)
	@mkdir -p $(dir $(@))
	gcc -c $(CFLAGS) -o $@ $<

SPRITESHT_OBJ = $(OBJ)/spritesht_lib.o $(OBJ)/spritesht.o
$(OUT)/spritesht: $(SPRITESHT_OBJ)
	@mkdir -p $(dir $(@))
	gcc $(LDFLAGS) -o $@ $(SPRITESHT_OBJ)

$(OUT)/spritesht.a: $(OBJ)/spritesht_lib.o
	@mkdir -p $(dir $(@))
	ar rcs $@ $<
