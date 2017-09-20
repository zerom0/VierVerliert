# Template for QT Project with cmake

If QT is not found on your platform you can point `CMAKE_PREFIX_PATH` to it.

    cmake -DCMAKE_PREFIX_PATH=/.../Qt/platform ...
    
To inspect QT Datatypes like QString, QVector, QPointer, ... in __lldb__ use the rendering scripts from 
https://bitbucket.org/lukeworth/lldb-qt-formatters/overview

