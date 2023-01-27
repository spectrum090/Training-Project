//
//  MyList.cpp
//
//  Created by Vitaliy Andreevich Zudov on 07.12.2022.
//
// Implement the functions to serialize and deserialize a doubly linked list.
// The data must be written in binary format.
// The expected algorithmic complexity is less than the quadratic one.
//

#include "MyList.h"
#include <iostream>
#include <cassert>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::cerr;
using std::endl;


// Saving the list to a file, the file is opened with `fopen( path, "wb" )`

void List::Serialize( FILE* file ) {
    if ( !file )
    {
        cerr << "[List::Serialize] file is invalid" << endl;
        return;
    }

    fwrite( &count, sizeof( int ), 1, file );

    if ( Empty() )
    {
        cout << "[List::Serialize] list is empty, nothing to do" << endl;
        return;
    }

    int counter{};
    for ( auto it = head; it != nullptr; it = it->next ) {
        *reinterpret_cast< int* >( &it->prev ) = counter++;
        long length = it->data.size();
        fwrite( &length, sizeof( long ), 1, file );
        if ( length > 0 )
            fwrite( it->data.data(), sizeof( char ), length, file );
    }

    for ( auto it = head; it != nullptr; it = it->next ) {
        counter = it->rand ? *reinterpret_cast< int* >( &it->rand->prev ) : -1;
        fwrite( &counter, sizeof( int ), 1, file );
    }

    ListNode* buffer = nullptr;
    for ( auto it = head; it != nullptr; it = it->next ) {
        it->prev = buffer;
        buffer = it;
    }
}

// Restore list from file, file opened with `fopen( path, "rb" )`

void List::Deserialize( FILE* file ) {
    if ( !file )
    {
        cerr << "[List::Deserialize] file is invalid" << endl;
        return;
    }

    if ( !Empty() )
    {
        cout << "[List::Deserialize] list isn't empty, content will be cleared" << endl;
        Clear();
    }

    int input_count{};
    fread( &input_count, sizeof( int ), 1, file );

    if ( input_count <= 0 )
    {
        cout << "[List::Deserialize] input count isn't great zero, nothing to do" << endl;
        return;
    }

    std::vector< ListNode* > nodes_vector;
    nodes_vector.reserve( input_count );

    long length{};
    for ( auto i = 0; i != input_count; ++i ) {
        fread( &length, sizeof( long ), 1, file );
        if ( length < 0 )
            length = 0;

        char data[ length + 1 ];
        if ( length > 0 )
            fread( data, sizeof( char ), length, file );

        data[ length ] = 0;

        InsertTail( data );
        nodes_vector.push_back( tail );
    }

    int num{};
    for ( auto it = head; it != nullptr; it = it->next ) {
        fread( &num, sizeof( int ), 1, file );
        if ( num >= 0 )
            it->rand = nodes_vector[ num ];
    }
}

// methods for filling the list //

List::~List()
{
    Clear();
}

void List::InsertTail( const char* data, ListNode* rand )
{
    auto node = NewListNode( data, rand );
    assert( node );
    if ( tail )
    {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
    else
    {
        tail = head = node;
    }
    ++count;
}

void List::InsertHead( const char* data, ListNode* rand )
{
    auto node = NewListNode( data, rand );
    assert( node );
    if ( head )
    {
        node->next = head;
        head->prev = node;
        head = node;
    }
    else
    {
        head = tail = node;
    }
    ++count;
}

ListNode* List::NewListNode( const char* data, ListNode* rand )
{
    auto node = new ListNode();
    node->data = data;
    node->rand = rand;
    return node;
}

void List::PopHead()
{
    if ( !head )
        return;

    --count;

    if ( head == tail )
    {
        delete head;
        head = tail = nullptr;
        assert( !count );
    }
    else
    {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    }
}

void List::PopTail()
{
    if ( head == tail )
    {
        PopHead();
        return ;
    }

    --count;

    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
}

void List::Clear()
{
    while ( head )
        PopHead();
    assert( !head && !tail && !count );
}

bool List::Empty() const
{
    return count == 0;
}

bool List::Size() const
{
    return count;
}

const ListNode* List::Head() const
{
    return head;
}

const ListNode* List::Tail() const
{
    return tail;
}

ListNode* List::Head()
{
    return head;
}

ListNode* List::Tail()
{
    return tail;
}

bool List::operator==( const List& other ) const
{
    if ( this->count != other.count )
        return false;

    auto it1 = head;
    auto it2 = other.head;
   
    for ( ; it1 != nullptr && it2 != nullptr; it1 = it1->next, it2 = it2->next )
    {
        if ( it1->data != it2->data )
            return false;

        if ( it1->rand && it2->rand )
        {
            if ( it1->rand->data != it2->rand->data )
                return false;
        }
        else if ( !( !it1->rand && !it2->rand ) )
        {
            return false;
        }
    }

    assert( !it1 && !it2 );

    return true;
}

bool List::operator!=( const List& other ) const
{
    return !( *this == other );
}
