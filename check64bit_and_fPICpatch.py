import os
import sys

is_64bit = sys.maxsize > 2**32
if is_64bit:
    os.chdir("src/peg-markdown")
    os.system("patch -u < ../../pegmarkdown-Makefile.patch")
