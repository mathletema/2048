import os
from PIL import Image, ImageDraw, ImageFont
import numpy as np

CELL_WIDTH = 60
FONT_WIDTH = 30
FONT = 'SFCompact.ttf'

NUMBERS = [
    [2, "#eee4da", "#776e65"],
    [4, "#ede0c8", "#776e65"],
    [8, "#f2b179", "#f9f6f2"],
    [16, "#f59563", "#f9f6f2"],
    [32, "#f67c5f", "#f9f6f2"],
    [64, "#f65e3b", "#f9f6f2"],
    [128, "#edcf72", "#f9f6f2"],
    [256, "#edcc61", "#f9f6f2"],
    [512, "#edc850", "#f9f6f2"],
    [1024, "#edc53f", "#f9f6f2"],
    [2048, "#3c3a32", "#f9f6f2"]
]

def get_size(text, fontSize, draw):
    _, _, w, h = draw.textbbox((0, 0), text, font=ImageFont.truetype(FONT, fontSize))
    return w, h

def rgbTo656(red, green, blue):
    red = int(red / 256 * 32)
    green = int(green / 256 * 64)
    blue = int(blue / 256 * 32)
    return "0x{:04x}".format((red<<11) + (green<<5) + (blue))

def create_cell(number, bgColor, fontColor):
    image = Image.new('RGB', (CELL_WIDTH, CELL_WIDTH), bgColor)
    draw = ImageDraw.Draw(image)
    
    font_size = 0
    while max(get_size(f"{number}", font_size+1, draw)) < FONT_WIDTH:
        font_size += 1

    w, h = get_size(f"{number}", font_size, draw)
    draw.text(((CELL_WIDTH-w)/2, (CELL_WIDTH-h)/2), f"{number}", font=ImageFont.truetype(FONT, font_size), fill=fontColor)


    return "color_t CELL_{}[] = ".format(number) + "{\n" + ",\n".join(
            "    " + ",".join(rgbTo656(*el) for el in row)
            for row in np.array(image)
    ) + "\n};\n\n"

    return image

with open("src/cells.c", "w") as f:
    f.write("#include \"cells.h\"\n")
    f.write("#include \"color.h\"\n\n")

    for number in NUMBERS:
        f.write(create_cell(*number))
         
# for number in NUMBERS:
#     img = create_cell(*number)
#     img.save(f"img/cell_{number[0]}.bmp", "BMP")

# os.makedirs("img", exist_ok=True)
# for number in NUMBERS:
#     img = create_cell(*number)
#     img.save(f"img/cell_{number[0]}.bmp", "BMP")


# myImage = create_cell(*NUMBERS[3])
# myImage.show()
# ('square.bmp', "BMP")
