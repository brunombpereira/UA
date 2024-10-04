# Compare two image files
# Show number of pixels that are equal, similar (±1) and different.
#
# JMR 2023

# Uses the Pillow library to read images.
# To install (in Ubuntu):  sudo apt install python3-pil
# To install (using pip), see:
#    https://pillow.readthedocs.io/en/stable/installation.html#

import sys
from PIL import Image

def main(args):
    if len(args) != 3:
        print(f"python3 {args[0]} img1.pgm img2.pgm")
        exit(1)

    img1 = Image.open(args[1])
    img2 = Image.open(args[2])

    if img1.size != img2.size:
        print("DIFFERENT SIZES:", img1.size, img2.size)
        return 1

    w, h = img1.size
    tot = w * h
    
    counts = [0, 0, 0]
    for a, b in zip(img1.getdata(), img2.getdata()):
        diff = min(abs(a - b), 2)
        counts[diff] += 1
    assert sum(counts) == tot

    levels = ["EQUAL", "SIMILAR", "DIFFERENT"]
    for c, lvl in zip(counts, levels):
        print(f"{c:8} pixels\t{c/tot:4.0%}\t{lvl:<12}")

    img1.close()
    img2.close()

    return counts[2] > 1


if __name__ == "__main__":
    exit(main(sys.argv))

