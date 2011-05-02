all:
	@echo "make build"
	@echo "make test"

SO = pegmarkdown.so
FLAGS = -Wall -g -O2
INCS = -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/usr/include/python2.7

OBJS = src/pegmarkdown.o \
	   src/peg-markdown/markdown_lib.o \
	   src/peg-markdown/parsing_functions.o
LIBS = -lglib-2.0

.SUFFIXES: .c .o

$(SO): $(OBJS)
	gcc $(LIBS) -fPIC -shared -o $(SO) $^

.c.o:
	gcc $(FLAGS) $(INCS) -o $@ -c $<

clean:
	rm -rf *.o *.so build temp *.egg-info

cleanall: clean
	rm -rf src/peg-markdown

test:
	python test.py

PEGS_DIR = src/peg-markdown
build:
	cd src && git clone https://github.com/jgm/peg-markdown.git && cd -
	cd src/peg-markdown && make && cd -
	python setup.py build
	#gcc $(FLAGS) $(INCS) $(LIBS) -fPIC -shared -o $(SO) \
	#	src/pegmarkdown.c $(PEGS_DIR)/markdown_lib.o \

install:
	python setup.py install
		$(PEGS_DIR)/markdown_parser.o $(PEGS_DIR)/markdown_output.o
