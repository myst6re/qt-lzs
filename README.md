qt-lzs
======

Simple command-line tool to compress/decompress LZS files (mainly used in Final Fantasy VII and VIII).

Usage
-----

    lzs [-dhq] file
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
