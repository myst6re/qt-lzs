qt-lzs
======

Simple command-line tool to compress/decompress LZS files (mainly used in Final Fantasy VII and VIII).

Usage
-----

    lzs [-d] [-h] [-q] [-p offset] [-s size] [files...] [output directory]
    unlzs [-h] [-q] [-p offset] [-s size] [files...] [output directory]
    Options
        -d --decompress --uncompress
            Decompress.
    
        -h --help
            Show this help and quit.
    
        -p --offset
            Start offset (=position) in the source file.
    
        --no-header
            The input file starts directly with compressed data.
    
        --no-header-test
            Do not test the header integrity.
    
        -q --quiet
            Suppress all outputs
    
        -s --size
            Read at most size bytes (excluding lzs header) from the source file.

Compilation
-----------

qt-lzs is a Qt project, use these commands to build it:

    qmake
    make

To compile the unlzs executable, run:

    qmake "CONFIG+=configUNLZS"
    make
