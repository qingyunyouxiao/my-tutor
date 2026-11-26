# AtCoder Grand Contest 008 && Cpp Begin 1

Date: 26/8/2


## AtCoder Grand Contest 008

Link: https://atcoder.jp/contests/agc008/tasks

## Cpp Begin 1

X - Atomic Counter
Y - LRU
Z - Weather

### Using alias

```c++
using Entry = std::pair<K, V>;
using List  = std::list<Entry>;
using Iter  = typename List::iterator;
 ```

### alias Types

```c++
int main()
{
    using Miles = long; // define Miles as an alias for type long
    using Speed = long; // define Speed as an alias for type long

    Miles distance { 5 }; // distance is actually just a long
    Speed mhz  { 3200 };  // mhz is actually just a long

    // The following is syntactically valid (but semantically meaningless)
    distance = mhz;

    return 0;
}
```

### explicit func

```c++
explicit LRUCache(std::size_t capacity) : capacity_(capacity) {}
```

### forbidden explicit usage

```c++
#include <iostream>

class Dollars
{
private:
    int m_dollars{};

public:
    explicit Dollars(int d)
        : m_dollars{ d }
    {
    }

    int getDollars() const { return m_dollars; }
};

void print(Dollars d)
{
    std::cout << "$" << d.getDollars();
}

int main()
{
    print(5); // compilation error because Dollars(int) is explicit

    return 0;
}
```
