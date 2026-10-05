# begin 003

Date: 26/10/5



## CHAPTER ONE

1. using 类型别名，给一个很长、复杂的类型起简短别名，方便代码书写阅读。

```c++
using Entry = std::pair<K, V>;
using List  = std::list<Entry>;
using Iter  = typename List::iterator;
```

- 别名实际上并不定义一个新的独立类型（被视为与其他类型分开的类型）——它只是为已有类型的新标识符引入。
- 类型别名与别名类型**完全可以互换**。

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

2. explicit 显式构造函数，阻止编译器自动做隐式类型转换，只允许显式调用构造函数。

```c++
explicit LRUCache(std::size_t capacity) : capacity_(capacity) {}
```

- 显式构造函数不能用于复制初始化或复制列表初始化。
- 显式构造函数**不能用于隐式转换**（因为这需要复制初始化或复制列表初始化）。

```c++
#include <iostream>

class Dollars
{
private:
    int m_dollars{};

public:
    explicit Dollars(int d) // now explicit
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

