from PIL import Image
import numpy as np



PRINT_IMAGE = 0


im = Image.open(r"../pictures/starwars_128x32.bmp")
picture = np.array(im)

# in pixels
HEIGHT, WIDTH = picture.shape
NUMBER_OF_PAGES = WIDTH * HEIGHT // 8

picture_bytes = [ [0] * WIDTH for _ in range(HEIGHT // 8) ]
picture_bytes = np.zeros((HEIGHT // 8, WIDTH), dtype=int)
for i in range(HEIGHT):
    for j in range(WIDTH):
        pixel = int(picture[i,j] == 2)  # 2 is white for some reason
        picture_bytes[i // 8, j] |= (pixel << (i % 8))

        if PRINT_IMAGE:
            print("1" if pixel else "0", end="")
    if PRINT_IMAGE:
        print()



# print data as C array
BYTE_WIDTH = 8

print(f"height = {HEIGHT};")
print(f"width  = {WIDTH};")
print(f"pages  = {HEIGHT // 8};")
print()
print(f"const uint8_t song_name_{WIDTH}x{HEIGHT} PROGMEM = ")
print("{")
for i in range(HEIGHT // 8):
    print("    {", end="")
    for j in range(WIDTH):
        if j % BYTE_WIDTH == 0:
            print("\n        ", end="")
    
        endstr = ", "
        if j == WIDTH - 1:
            endstr = ""
        print(hex(picture_bytes[i, j]), end=endstr)
    
    endstr = "},"
    if i == HEIGHT // 8 - 1:
        endstr = "}"
    print("\n    " + endstr)
print("};")

