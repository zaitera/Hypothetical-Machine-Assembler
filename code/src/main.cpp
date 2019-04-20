#include <assembler.h>
#include <preprocessor.h>

int main()
{
    int a = test();
    std::cout << a << std::endl;
    sayHello();
    return 0;
}