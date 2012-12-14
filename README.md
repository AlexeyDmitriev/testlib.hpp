testlib.hpp
===========

`testlib.hpp` is a library for creating checkers and validators for sport programming problems. Simple checker example:
```c++
#include "testlib.hpp"
TESTLIB_CHECK(){
    verifyEqual(ouf.read<int>(), ans.read<int>());
    OK("1 number");
}
```

[Tutorial](https://github.com/AlexeyDmitriev/testlib.hpp/wiki/Tutorial)  
[More complex documentation](https://github.com/AlexeyDmitriev/testlib.hpp/wiki/General-Documentation)
