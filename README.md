qt-lzs
======

Simple command-line tool to compress/decompress LZS files (mainly used in Final Fantasy VII and VIII).

Usage
-----

    lzs [-dhq] file
    unlzs [-hq] file
    Options
        -d --decompress --uncompress
            Decompress.
    
        -h --help
            Show this help and quit.
    
        --no-header
            The input file starts directly with compressed data.
    
        --no-header-test
            Do not test the header integrity.
    
        -q --quiet
            Suppress all outputs

Compilation
-----------

qt-lzs is a Qt project, use these commands to build it:

    qmake
    make

To compile the unlzs executable, run:

    qmake "CONFIG+=configUNLZS"
    make
