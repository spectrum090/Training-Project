//
//  MyList.h
//
//  Created by Vitaliy Andreevich Zudov on 07.12.2022.
//
// Implement the functions to serialize and deserialize a doubly linked list.
// The data must be written in binary format.
// The expected algorithmic complexity is less than the quadratic one.
//

#pragma once

#include <stdio.h>
#include <string>

struct ListNode                 // can't be modified
{
    ListNode* prev = nullptr;   // pointer to the previous element of the list, or `nullptr` if head
    ListNode* next = nullptr;   // pointer to the next element of the list, or `nullptr` if tail
    ListNode* rand = nullptr;   // pointer to a random element of the given list, or `nullptr`
    std::string data;           // some user data
};

class List {
public:
    void Serialize  ( FILE* file ); // saving the list to a file, the file is opened with `fopen( path, "wb" )`
    void Deserialize( FILE* file ); // restore list from file, file opened with `fopen( path, "rb" )`

    // methods for filling the list //

    ~List();

    void InsertHead( const char* data, ListNode* rand = nullptr );
    void InsertTail( const char* data, ListNode* rand = nullptr );

    void PopHead();
    void PopTail();

    void Clear();

    bool Empty() const;
    bool Size()  const;

    const ListNode* Head() const;
    const ListNode* Tail() const;

    ListNode* Head();
    ListNode* Tail();

    bool operator==( const List& other ) const;
    bool operator!=( const List& other ) const;

private:
    static ListNode* NewListNode( const char* data, ListNode* rand = nullptr );

private:
    // class fields //
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int count = 0;
};
