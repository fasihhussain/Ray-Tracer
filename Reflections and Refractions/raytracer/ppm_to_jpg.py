import os
import sys
from PIL import Image

def main():
    """
    Entry point... You enter here.
    """
    assert 3 == len(sys.argv), "Wrong usage. Usage: %s <input_ppm_image> <output_jpg_image>." % sys.argv[0]
    input_image = sys.argv[1]
    assert os.path.isfile(input_image), "The input image %s doesn't exist." % input_image
    output_place = sys.argv[2]
    print(input_image)
    print(output_place)

    with open(input_image) as f:
        lines = [line.rstrip() for line in f]
    width,height = lines[1].split()
    width = int(width)
    height = int(width)
    
    data = []
    for j in range(3,len(lines)):
        values  = lines[j].split()
        rgb = [tuple(values[i:i+3]) for i in range(0, len(values)-1, 3)]
        data.append(rgb)
    new_img = Image.new("RGB", (int(width), int(height)))
    for i in range(height):
        for j in range(width):
            r,g,b = data[i][j]

            new_img.putpixel((j, i), (int(r), int(g), int(b)))
    new_img.save(output_place)   
    new_img.show()  
    
    
    
    
            
if "__main__" == __name__:
   main()
        
   
