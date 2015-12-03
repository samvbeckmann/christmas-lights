import random

# Color dictionary, in r-g-b format.
# Color ranges from 0x0 - 0x7f. The MSB is always enabled.
color_dict = {
    'y': '0xff, 0xc4, 0x80, ',  # Yellow
    'o': '0xfc, 0x8c, 0x80, ',  # Orange
    'r': '0xff, 0x80, 0x80, ',  # Red
    'g': '0x80, 0xff, 0x80, '  # Green
}

acceptable_colors = ['r', 'r', 'y', 'y', 'o', 'o', 'g']

# Transforms a simple txt file to a c-readable array.
# Contains colors for PLD8806 RGB LED strip.
result = '{\n'
for y in range(30):
    result += '\t{ '
    for x in range(32):
        result += color_dict[random.choice(acceptable_colors)]
    result = result[:-2] + ' } ,\n'
result = result[:-3] + '\n};'

print(result)
