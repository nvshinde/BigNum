# BigNum++
An learning project for aribitary-precision integer arithmetic

# Build and Test
```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ ctest             # optional, for testing
```

# Use
```
#include "../include/bigint/BigInt.hpp"
#include <cassert>
#include <iostream>

int main() {
    using namespace bigint;

    BigInt a("123");
    BigInt b("456");

    BigInt c = a + b;

    std::cout << a.toString() << " + " << b.toString() << " = " << c.toString() << "\n";

    assert(c.toString() == "579");
    return 0;
}

```

# TODO:
1. Inplace ops in bigint
2. Compound ops for bigfloat

