#include <iostream>
#include "Book.hpp"
#include "Function.hpp"

int main()
{
    Book *arr[5];
    for (std::size_t i = 0; i < 5; i++)
    {
        arr[i] = foo(i);
        if (arr[i] == nullptr)
        {
            std::cout << "smth went wrong" << std::endl;
            continue;
        }
        arr[i]->read();
    }
    for (std::size_t i = 0; i < 5; i++)
    {
        delete arr[i];
    }
    return 0;
}