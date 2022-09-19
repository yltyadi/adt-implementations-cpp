#include "queue.h"

queue::queue( ) :
    queue_size(0),
    front(nullptr),
    back(nullptr)
{}

queue::queue( const queue& q ) :
    queue_size(0),
    front(nullptr),
    back(nullptr)
{
    node* current = q.front;
    while (current != nullptr) {
        push(current->value);
        current = current->next;
    }
}

const queue& queue::operator = ( const queue& q ) {
    if (this != &q) {
        clear();
        node* current = q.front;
        while (current != nullptr) {
            push(current->value);
            current = current->next;
        }
        this->queue_size = q.queue_size;
    } else {
        throw std::runtime_error("Self assignment error!");
    }
    return *this;
}

queue::~queue( ) {
    clear();
}

queue::queue( std::initializer_list< std::string > init ) :
    queue_size(0),
    front(nullptr),
    back(nullptr)
{
    for (size_t i = 0; i < init.size(); i++) {
        push(*(init.begin() + i));
    }
}

void queue::push( const std::string& s ) {
    node* new_node = new node(s);
    if (queue_size == 0) {
        front = new_node;
    } else {
        back->next = new_node;
    }
    back = new_node;
    queue_size++;
}

void queue::pop( ) {
    if (front == nullptr) {
        throw std::runtime_error("Cannot pop from an empty queue!");
    }
    node* old_node = front;
    front = front->next;
    delete old_node;
    queue_size--;
}

void queue::clear( ) {
    while (front != nullptr) {
        pop();
    }
}

void queue::reset( size_t s ) {
    if (s > queue_size) {
        throw std::runtime_error("Cannot reset! Requested size is greater than the queue size!");
    }
    while (s != queue_size) {
        pop();
    }
}

const std::string& queue::peek( ) const {
    return front->value;
}

size_t queue::size( ) const {
    return queue_size;
}

bool queue::empty( ) const {
    if (queue_size != 0) {
        return false;
    }
    return true;
}

void queue::print( std::ostream& out ) const {
    out << "queue:  ";
    node* current = front;
    for (size_t i = 0; i < queue_size; i++) {
        out << current->value;
        if (current->next != nullptr) {
            out << ", ";
        }
        current = current->next;
    }
}
