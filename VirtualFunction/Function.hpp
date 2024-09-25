#include "Book.hpp"

Book *foo(std::size_t x)
{
    switch (x % 5)
    {
    case 0:
        return new Horror;
    case 1:
        return new RomanceNovel;
    case 2:
        return new ScienceFiction;
    case 3:
        return new Detective;
    case 4:
        return new Thriller;
    default:
        return nullptr;
    }
}