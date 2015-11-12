SRC = src
BUILD = build
OBJ = $(BUILD)/obj
OUT = $(BUILD)/out

CFLAGS = -Iinput/libpng -Iinc -g
LDFLAGS = -Linput/libpng -Linput/zlib -lpng -lz

all: $(OUT)/spritesht $(OUT)/fakesht

clean:
	rm -rf $(BUILD)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $(@))
	gcc -c $(CFLAGS) -o $@ $<

SPRITESHT_OBJ = $(OBJ)/spritesht_lib.o $(OBJ)/spritesht.o
$(OUT)/spritesht: $(SPRITESHT_OBJ)
	@mkdir -p $(dir $(@))
	gcc $(LDFLAGS) -o $@ $(SPRITESHT_OBJ)

FAKESHT_OBJ = $(OBJ)/spritesht_lib.o $(OBJ)/fakesht.o
$(OUT)/fakesht: $(FAKESHT_OBJ)
	@mkdir -p $(dir $(@))
	gcc $(LDFLAGS) -o $@ $(FAKESHT_OBJ)
