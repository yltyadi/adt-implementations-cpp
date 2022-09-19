#include "set.h"

size_t case_insensitive::hash( const std::string& s ) {
    size_t wordlen = s.length();
    size_t result = 0;
    if (wordlen == 0) {
        return 0;
    }
    for (size_t i = 0; i < wordlen; i++) {
        //result = result + (std::tolower(s[i]) * std::pow(31,wordlen - (i + 1)));
        size_t power = 31;
        for (size_t n = 0; n <= (wordlen - (i+1)); n++) {
            power = power * 31;
        }
        result = result + (std::tolower(s[i]) * power);
    }
    return result;
}

bool case_insensitive::equal( const std::string& s1, const std::string& s2 ) {
    if (s1.length() != s2.length()) {
        return false;
    }
    
    for (size_t i = 0; i < s1.length(); i++) {
        if (tolower(s1[i]) != tolower(s2[i])) {
            return false;
        }
    }
    return true;
}

bool set::insert_norehash( const std::string& s ) {
    size_t value = case_insensitive::hash(s);
    size_t index = value % buckets.size();
    for (auto it = buckets[index].begin(); it != buckets[index].end(); it++) {
        if (case_insensitive::equal(*it, s)) {
            return false;
        }
    }
    buckets[index].push_back(s);
    set_size++;
    return true;
}

void set::consider_rehash( ) {
    if (loadfactor() > max_load_factor) {
        size_t new_size = buckets.size() * 2;
        std::vector<buckettype> newBucket (new_size);
        for (size_t i = 0; i < buckets.size(); i++) {
            for (auto it = buckets[i].begin(); it != buckets[i].end(); it++) {
                size_t index = case_insensitive::hash(*it) % new_size;
                newBucket[index].push_back(*it);
            }
        }
        buckets = newBucket;
    }
}

set::set( std::initializer_list< std::string > init,
          double max_load_factor)
   : set_size(0),
     max_load_factor( max_load_factor ),
     buckets(std::vector<buckettype> (8))
{
    for (auto i = init.begin(); i != init.end(); i++) {
        insert(*i);
    }
}

bool set::contains( const std::string& s ) const {
    if (empty()) {
        return false;
    }
    size_t value = case_insensitive::hash(s);
    size_t index = value % buckets.size();
    for (auto it = buckets[index].begin(); it != buckets[index].end(); it++) {
        if (case_insensitive::equal(*it, s)) {
            return true;
        }
    }
    return false;
}

bool set::insert( const std::string& s ) {
    consider_rehash();
    return insert_norehash(s);
}

bool set::remove( const std::string& s ) {
    size_t value = case_insensitive::hash(s);
    size_t index = value % buckets.size();
    for (auto it = buckets[index].begin(); it != buckets[index].end(); it++) {
        if (case_insensitive::equal(*it, s)) {
            buckets[index].erase(it);
            set_size--;
            return true;
        }
    }
    return false;
}

size_t set::size( ) const {
    return set_size;
}

bool set::empty( ) const {
    if (set_size == 0) {
        return true;
    }
    return false;
}

void set::clear( ) {
    for (size_t i = 0; i < buckets.size(); i++) {
        buckets[i].clear();
    }
    set_size = 0;
}

void set::print( std::ostream& out ) const {
    for (size_t i = 0; i < buckets.size(); i++) {
        out << "bucket[" << i << "]: ";
        buckettype lst = buckets[i];
        out << "{ ";
        size_t count = 0;
        for (auto it = lst.begin(); it != lst.end(); it++) {
            out << *it;
            count++;
            if (count != buckets[i].size()) {
                out << ", ";
            }
        }
        out << " }\n";
    }
}
