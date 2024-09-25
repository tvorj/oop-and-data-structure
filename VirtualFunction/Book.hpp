#pragma once
#include <iostream>
class Book
{
public:
    virtual void read()
    {
        std::cout << "this is book. " << std::endl;
    }
    virtual ~Book()
    {
        std::cout << "destructor called for Book. " << std::endl;
    }
};

class Horror : public Book
{
public:
    void read() override
    {
        std::cout << "horror book." << std::endl;
    }
    ~Horror() override
    {
        std::cout << "destructor called for Horror. " << std::endl;
    }
};

class RomanceNovel : public Book
{
public:
    void read() override
    {
        std::cout << "romance novel." << std::endl;
    }
    ~RomanceNovel() override
    {
        std::cout << "destructor called for RomanceNovel. " << std::endl;
    }
};

class ScienceFiction : public Book
{
public:
    void read() override
    {
        std::cout << "science fiction book." << std::endl;
    }
    ~ScienceFiction() override
    {
        std::cout << "destructor called for ScienceFiction. " << std::endl;
    }
};

class Detective : public Book
{
public:
    void read() override
    {
        std::cout << "detective book." << std::endl;
    }
    ~Detective() override
    {
        std::cout << "destructor called for Detective. " << std::endl;
    }
};

class Thriller : public Book
{
public:
    void read() override
    {
        std::cout << "thriller book." << std::endl;
    }
    ~Thriller() override
    {
        std::cout << "destructor called for Thriller. " << std::endl;
    }
};