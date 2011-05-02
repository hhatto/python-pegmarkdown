from distutils.core import setup, Extension
from subprocess import Popen, PIPE


def get_library_dirs():
    cmd = "pkg-config --libs-only-L glib-2.0"
    proc = Popen(cmd.split(), stdin=PIPE, stdout=PIPE, stderr=PIPE)
    ret = proc.communicate()[0]
    ret = ret.split()
    libdirs = [i.strip()[2:] for i in ret]
    return libdirs


def get_libraries():
    cmd = "pkg-config --libs-only-l glib-2.0"
    proc = Popen(cmd.split(), stdin=PIPE, stdout=PIPE, stderr=PIPE)
    ret = proc.communicate()[0]
    ret = ret.split()
    libs = [i.strip()[2:] for i in ret]
    return libs


def get_include_dirs():
    cmd = "pkg-config --cflags glib-2.0"
    proc = Popen(cmd.split(), stdin=PIPE, stdout=PIPE, stderr=PIPE)
    ret = proc.communicate()[0]
    ret = ret.split()
    incs = [i.strip()[2:] for i in ret]
    return incs

import os
setup(
    name='pegmarkdown',
    version='0.1',
    description='Python extension for peg-markdown.',
    author='Hideo Hattori',
    author_email='hhatto.jp@gmail.com',
    #url='',
    ext_modules=[
        Extension('pegmarkdown',
                  sources=['src/pegmarkdown.c', ],
                      #         'src/peg-markdown/markdown_lib.c',
                      #         'src/peg-markdown/markdown_parser.c',
                      #         'src/peg-markdown/markdown_output.c'],
                  include_dirs=get_include_dirs(),
                  library_dirs=get_library_dirs(),
                  libraries=get_libraries(),
                  extra_objects=['src/peg-markdown/markdown_lib.o',
                                 'src/peg-markdown/markdown_parser.o',
                                 'src/peg-markdown/markdown_output.o'],
                 )]
)
