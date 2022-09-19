#include "stack.h"

void stack::ensure_capacity( size_t c ) {
    if (c > current_capacity) {
        unsigned int p = 0;
        do {
            p++;
        } while (p*p < c);
        double* new_data = new double[p*p];
        std::copy(data, data + current_size, new_data);
        delete[] data;
        data = new_data;
        current_capacity = p*p;
    }
}
   // Keep current_capacity always in powers of two.

stack::stack( ) :
    current_size(0),
    current_capacity(4),
    data(new double[4])
{}

stack::stack( const stack& s ) :
    current_size(s.current_size),
    current_capacity(s.current_capacity),
    data(new double[s.current_capacity])
{
    std::copy(s.data, s.data + s.current_size, this->data);
}
   // use std::copy

stack::~stack( ) {
    delete[] data;
}

const stack& stack::operator = ( const stack& s ) {
    // making sure that this->data is empty before copying s into it
    
    ensure_capacity(s.current_size);
    this->current_size = s.current_size;
    this->current_capacity = s.current_capacity;
    
    std::copy(s.data, s.data + s.current_size, this->data);
    return *this;
}
   // use ensure_capacity and std::copy.
  
stack::stack( std::initializer_list< double > init ) :
    current_size(0),
    current_capacity(init.size()),
    data(new double[init.size()])
{
    for (size_t i = 0; i < init.size(); i++) {
        push(*(init.begin() + i));
    }
}
   // 1. either use push( ), or
   // 2. ensure_capacity.
  
void stack::push( double d ) {
    ensure_capacity(current_size + 1); // if i pass just current_size nothing iwll happen
    // here i give current_size + 1 to allocate new memory if the current_size == current_capacity
    data[current_size] = d;
    current_size++;
}

void stack::pop( ) {
    if (current_size == 0) {
        throw std::runtime_error("pop: stack is empty");
    }
    current_size--;
}

void stack::clear( ) {
    current_size = 0;
}

void stack::reset( size_t s ) {
    while (current_size != s) {
        current_size--;
    }
}

double stack::peek( ) const {
    if (current_size == 0) {
        throw std::runtime_error("pop: stack is empty");
    }
    return data[current_size - 1];
}

size_t stack::size( ) const {
    return current_size;
}

bool stack::empty( ) const {
    if (current_size == 0) {
        return true;
    }
    return false;
}

void stack::print( std::ostream& out ) const {
    out << "stack: ";
    for (size_t i = 0; i < current_size; i++) {
        out << data[i];
        if (i != current_size - 1) {
            out << ", ";
        }
    }
}
   // make sure that printing is correct and commas are put properly
   // between the stack elements. Make sure to print into out and not
   // std::cout.
