# Game night hack for a Vier Gewinnt online game

The game can be found at 
https://github.com/lakermann/connect-four-challenge-server

## Development notes

If QT is not found on your platform you can point `CMAKE_PREFIX_PATH` to it.

    cmake -DCMAKE_PREFIX_PATH=/.../Qt/platform ...
    
To inspect QT Datatypes like QString, QVector, QPointer, ... in __lldb__ use the rendering scripts from 
https://bitbucket.org/lukeworth/lldb-qt-formatters/overview


## Coding style
Google + space after ```*``` and ```&```