#ifndef TYPED_ARRAY
#define TYPED_ARRAY

#include <assert.h>
#include <iostream>
#include <stdexcept>

template <typename ElementType>
class TypedArray {

public:

    TypedArray();
    TypedArray(const TypedArray& other);

    // Copy constructor
    TypedArray& operator=(const TypedArray& other);

    // Destructor
    ~TypedArray();

    // Getters
    ElementType &get(int index);
    ElementType &safe_get(int index) const;
    int size() const;

    // Setters
    void set(int index, ElementType value);


    // Exercises ********************************
    
    // Push
    TypedArray& push(ElementType value);

    // Push_front
    TypedArray& push_front(ElementType value);

    // Pop
    ElementType &pop();

    // Pop_front
    ElementType &pop_front();

    // Concat
    TypedArray concat(const TypedArray other) const;

    // Reverse
    TypedArray& reverse();

    // Define '+' operator
    TypedArray operator+(const TypedArray other) const;

private:

    int capacity,
        origin,
        end;

    ElementType * buffer;   

    const int INITIAL_CAPACITY = 10;

    int index_to_offset(int index) const;
    int offset_to_index(int offset) const;
    bool out_of_buffer(int offset) const;
    void extend_buffer(void);    

};

template <typename ElementType>
TypedArray<ElementType>::TypedArray() {
    buffer = new ElementType[INITIAL_CAPACITY]();
    capacity = INITIAL_CAPACITY;    
    origin = capacity / 2;
    end = origin;    
}

// Copy constructor: i.e TypedArray b(a) where a is a TypedArray
template <typename ElementType>
TypedArray<ElementType>::TypedArray(const TypedArray& other) : TypedArray() {
    *this = other;
}

// Assignment operator: i.e TypedArray b = a 
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::operator=(const TypedArray<ElementType>& other) {
    if ( this != &other) {
        delete[] buffer; // don't forget this or you'll get a memory leak!
        buffer = new ElementType[other.capacity]();
        capacity = other.capacity;
        origin = other.origin;
        end = origin;
        for ( int i=0; i<other.size(); i++) {
            set(i,other.safe_get(i));
        }
    }
    return *this;
}

// Destructor
template <typename ElementType>
TypedArray<ElementType>::~TypedArray() {
    delete[] buffer;
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::get(int index) {
    if (index < 0) {
        throw std::range_error("Out of range index in array");
    }
    if ( index >= size() ) {
        ElementType x;
        set(index, x);
    } 
    return buffer[index_to_offset(index)];
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::safe_get(int index) const {
    if (index < 0 || index >= size() ) {
        throw std::range_error("Out of range index in array");
    }
    return buffer[index_to_offset(index)];
}

template <typename ElementType>
int TypedArray<ElementType>::size() const {
    return end - origin;
}

// Setters
template <typename ElementType>
void TypedArray<ElementType>::set(int index, ElementType value) {
    if (index < 0) {
        throw std::range_error("Negative index in array");
    }
    while ( out_of_buffer(index_to_offset(index) ) ) {
        extend_buffer();
    }
    buffer[index_to_offset(index)] = value; // Should call the copy constructor
                                            // of ElementType.
    if ( index >= size() ) {
        end = index_to_offset(index+1);
    }
}

template <typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedArray<ElementType> &array)
{
    os << '[';
    for (int i=0; i<array.size(); i++ ) {
        os << array.get(i);
        if ( i < array.size() - 1 ) {
            os << ",";
        }
    }
    os << ']';
    return os;
}

// Private methods

template <typename ElementType>
int TypedArray<ElementType>::index_to_offset ( int index ) const {
    return index + origin;
}

/* Position of the element at buffer position 'offset' */
template <typename ElementType>
int TypedArray<ElementType>::offset_to_index ( int offset ) const  {
    return offset - origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
template <typename ElementType>
bool TypedArray<ElementType>::out_of_buffer ( int offset ) const {
    return offset < 0 || offset >= capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
template <typename ElementType>
void TypedArray<ElementType>::extend_buffer() {

    auto temp = new ElementType[2 * capacity]();
    int new_origin = capacity - (end - origin)/2,
           new_end = new_origin + (end - origin);

    for ( int i=0; i<size(); i++ ) {
        temp[new_origin+i] = get(i);
    }

    delete[] buffer;
    buffer = temp;

    capacity = 2 * capacity;
    origin = new_origin;
    end = new_end;

    return;

}


// Exercise 1
// Push
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::push(ElementType value) {
    int new_end = origin + size(); 
    set(offset_to_index(new_end), value);
   
    return *this;
}

// Push_front
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::push_front(ElementType value) {
    push(value);
    auto tmp = new ElementType[capacity]();
    int new_end = origin + size();
    int new_origin = new_end - size();
    tmp[new_origin] = value;
    for (int i=1; i<size();i++) {
        tmp[new_origin+i] = get(i-1);
    }
    delete[] buffer;
    buffer = tmp;

    return *this;
}

// Pop
template <typename ElementType>
ElementType &TypedArray<ElementType>::pop() {
    if ( this == NULL) {
        throw std::range_error ("Cannot pop from an empty array");
    }
    auto tmp = new ElementType();
    *tmp = get(offset_to_index(end-1));
    set(offset_to_index(end-1),0);
    end = end - 1;
    capacity = end - origin;
     
    return *tmp ;
}

// Pop_front
template <typename ElementType>
ElementType &TypedArray<ElementType>::pop_front() {
    if (this == NULL) {
        throw std::range_error ("Cannot pop from an empty array");
    }
    auto tmp = new ElementType();
    *tmp = get(offset_to_index(origin));
    set(offset_to_index(origin),0);
    origin = origin + 1;
    capacity = end - origin;
     
    return *tmp ;
}

// Exercise 2      
// Concat
template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::concat(const TypedArray<ElementType> other) const{  
    auto tmp_this = TypedArray();
    tmp_this = *this;

    auto tmp_other = TypedArray();
    tmp_other = other;
    
    for(int i = 0; i<other.size(); i++) {
    tmp_this.push(tmp_other.buffer[index_to_offset(i)]);
    }

    return tmp_this;
}

// Exercise 3      
// reverse
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::reverse() {  
    auto tmp = new ElementType[capacity]();
    int new_end = origin + size();
    int new_origin = new_end - size();
      for (int i=0; i<size();i++) {
        tmp[new_origin+i] = safe_get(size()-1-i);
    }
    delete[] buffer;
    buffer = tmp;
    end = new_end;
    origin = new_origin;

    return *this;
}

//Exercise 4
// Defining '+' operator
template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::operator+(const TypedArray<ElementType> other) const {
    auto tmp_this = TypedArray();
    tmp_this = *this;

    auto tmp_other = TypedArray();
    tmp_other = other;
    
    for(int i = 0; i<other.size(); i++) {
    tmp_this.push(tmp_other.buffer[index_to_offset(i)]);
    }

    return tmp_this;
}
  
  



#endif