/*
Write functions makeHeap, popHeap and pushHeap for the tests to pass.
They must behave the same way the std::make_heap, std::pop_heap and std::push_heap behave.
*/
#pragma once
#include <vector>
#include <iterator>
#include <functional>
#include <cstddef>

int rightChild(std::size_t index)
{
    return (index << 1) + 1;
}

int leftChild(std::size_t index)
{
    return index << 1;
}

int parent(std::size_t index)
{
    return index >> 1;
}

template <typename iter, typename cmp>
void shiftUp(iter begin, iter end, cmp func)
{
    auto index = std::distance(begin, end) - 1;
    while (index > 0)
    {
        int _parent = parent(index);
        if (!func(*(begin + _parent), *(begin + index)))
        {
            break;
        }
        std::swap(*(begin + index), *(begin + _parent));
        index = _parent;
    }
}

template <typename iter, typename cmp>
void shiftDown(iter begin, iter end, iter cur, cmp func)
{
    auto size = std::distance(begin, end);
    auto index = std::distance(begin, cur);
    while (true)
    {
        auto idx = index;
        auto l_idx = leftChild(index);
        auto r_idx = rightChild(index);
        if (l_idx < size && func(*(begin + idx), *(begin + l_idx)))
        {
            idx = l_idx;
        }
        if (r_idx < size && func(*(begin + idx), *(begin + r_idx)))
        {
            idx = r_idx;
        }
        if (idx == index)
        {
            break;
        }

        std::swap(*(begin + idx), *(begin + index));

        index = idx;
    }
}

template <typename iter, typename cmp>
void pushHeap(iter begin, iter end, cmp func)
{
    shiftUp(begin, end, func);
}

template <typename iter>
void pushHeap(iter begin, iter end)
{
    pushHeap(begin, end, std::less());
}

template <typename iter, typename cmp>
void popHeap(iter begin, iter end, cmp func)
{
    if (begin == end)
    {
        return;
    }
    std::swap(*(begin), *(end - 1));
    shiftDown(begin, end - 1, begin, func);
}

template <typename iter>
void popHeap(iter begin, iter end)
{
    popHeap(begin, end, std::less());
}

template <typename iter, typename cmp>
void makeHeap(iter begin, iter end, cmp func)
{
    auto size = std::distance(begin, end);
    for (auto i = size / 2 - 1; i >= 0; i--)
    {
        shiftDown(begin, end, begin + i, func);
    }
}

template <typename iter>
void makeHeap(iter begin, iter end)
{
    makeHeap(begin, end, std::less());
}
