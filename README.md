## Training Project

Here's the completed solution for the following tasks:

### Task 1. Binary representation
Write a function that takes a signed integer as input and prints its binary representation.

### Task 2. Duplicates removing
Write a function to remove consecutively duplicate characters in a string:
```c++
void RemoveDups( char* str );

// пример использования
char data[] = "AAA BBB AAA";
RemoveDups( data );
printf( "%s\n", data ); // "A B A"
```

### Task 3. Double-linked list with random iterators serialization and deserialization

Implement the functions to serialize and deserialize a double-linked list.
The data must be written in binary format.
The expected algorithmic complexity is less than the quadratic one.

```c++
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

private:
    // class fields //
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int count = 0;
};
```

Note: serialization means saving and restoring the complete structure of the list, including the mutual relationship of its elements to each other.