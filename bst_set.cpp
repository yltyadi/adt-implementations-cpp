#include "set.h"

const treenode* find( const treenode* n, const std::string& s ) {
    if (n != nullptr) {
        while (n != nullptr) {
            if (n->value == s) {
                return n;
            } else if (s < n->value) {
                n = n->left;
            } else {
                n = n->right;
            }
        }
        return n;
    }
    return nullptr;
}

treenode** find( treenode** n, const std::string& s ) {
    if (*n != nullptr) {
        while (*n != nullptr) {
            if ((*n)->value == s) {
                return n;
            } else if (s < (*n)->value) {
                n = &(*n)->left;
            } else {
                n = &(*n)->right;
            }
        }
    }
    return n;
}

size_t size( const treenode* n ) {
    if (n == nullptr) {
        return 0;
    }
    return (size(n->left) + 1 + size(n->right));
}

size_t height( const treenode* n ) {
    if (n == nullptr) {
        return 0;
    }
    return (height(n->left) > height(n->right)) ? (height(n->left) + 1) : (height(n->right) + 1);
}

void deallocate( treenode* n ) {
    if (n != nullptr) {
        if (n->left != nullptr) {
            deallocate(n->left);
        }
        if (n->right != nullptr) {
            deallocate(n->right);
        }
        delete n;
    }
}

treenode* makecopy( const treenode* n ) {
    if (n) {
        treenode* temp = new treenode(n->value);
        temp->left = makecopy(n->left);
        temp->right = makecopy(n->right);
        return temp;
    }
    return nullptr;
}

void print( std::ostream& out, const treenode* n, unsigned int indent )
{
   for( unsigned int i = 0; i != indent; ++ i )
      out << "|  ";
   if(n)
   {
      out << ( n -> value ) << "\n";
      print( out, n -> left, indent + 1 );
      print( out, n -> right, indent + 1 );
   }
   else
      out << "#\n";
}


// Both the upperbound and the lowerbound are strict,
// we use pointers, so that they can be absent.

void checkbetween( const treenode* n,
                   const std::string* lowerbound,
                   const std::string* upperbound )
{
   while(n)
   {
      if( lowerbound && *lowerbound >= n -> value )
      {
         std::cout << "value " << ( n -> value );
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         throw std::runtime_error( "tree not correct" );
      }

      if( upperbound && n -> value >= *upperbound )
      {
         std::cout << "value " << ( n -> value );
         std::cout << "is not below upperbound " << *upperbound << "\n";
         throw std::runtime_error( "tree not correct" );
      }

      checkbetween( n -> left, lowerbound, &( n -> value ));
      lowerbound = & ( n -> value );
      n = n -> right;
   }
}

unsigned int log_base2( size_t s ) {
    if (s == 0 || s == 1) {
        return 0;
    } else {
        unsigned int result = 0;
        unsigned int log = 2;
        do {
            log = log * 2;
            result++;
        } while (s >= log);
        return result;
    }
}

bool set::contains( const std::string& s ) const {
    if (find(tr, s) == nullptr) {
        return false;
    }
    return true;
}
 
bool set::insert( const std::string& s ) {
    treenode** result = find(&tr, s);
    if (*result == nullptr) {
        treenode* node = new treenode(s);
        *result = node;
        return true;
    }
    return false;
}

size_t set::size( ) const {
    return ::size(tr);
}

size_t set::height( ) const {
    return ::height(tr);
}

bool set::empty( ) const {
    if (tr == nullptr) {
        return true;
    }
    return false;
}

set:: ~set( ) {
    clear();
}

void set::clear( ) {
    ::deallocate(tr);
    tr = nullptr;
}

set::set( const set& other ) {
    tr = ::makecopy(other.tr);
}

set& set::operator = ( const set& other ) {
    if (this != &other) {
        clear();
        tr = ::makecopy(other.tr);
    }
    return *this;
}

void set::checksorted( ) const {
   ::checkbetween( tr, nullptr, nullptr );
}

void set::print( std::ostream& out, unsigned int indent ) const {
   ::print( out, tr, indent );
}
