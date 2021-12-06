from PIL import Image




raw = 'raw_images/fruits/orange.png'

out = 'sprites/fruits/orange.spr'


# read from the raw image

im = Image.open(raw, 'r')
width, height = im.size
pixel_values = list(im.convert('RGBA').getdata())


# write to the output file

file = open(out, 'w')
for i in range(width*height):
    r, g, b, a = pixel_values[i]

    # convert from rgb -> hex -> decimal
    val = str(int(str('%02x%02x%02x' % (r, g, b)), 16))
    if a != 255:
        val = str(-1)

    file.write(val + " ")
    if (i + 1) % width == 0:
        file.write('\n')

file.close()