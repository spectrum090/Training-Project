//
//  main.cpp
//  Training Project
//
//  Created by Vitaliy Zudov on 07.12.2022.
//

#include "Functions/Functions.h"
#include "List/MyList.h"

#include <cassert>
#include <memory>
#include <string>

using std::unique_ptr;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

int main()
{
    //
    //  Tests for functions that take a signed integer as input and print its binary representation.
    //

    PrintBitset( 12345 );
    PrintBitsetVec( 12345 );
    cout << endl;

    PrintBitset( -12345 );
    PrintBitsetVec( -12345 );
    cout << endl;

    PrintBitset( 12345L );
    PrintBitsetVec( 12345L );
    cout << endl;

    PrintBitset( 0 );
    PrintBitsetVec( 0 );
    cout << endl;


    //
    //  Tests for function for removing consecutively duplicate characters in a string
    //

    char data1[] = "AAA BBB   AAA";
    RemoveDups( data1 );
    cout << data1 << endl; // "A B A"

    char data2[] = "AAAAAAAAAA";
    RemoveDups( data2 );
    cout << data2 << endl; // "A"

    char data3[] = "A B C";
    RemoveDups( data3 );
    cout << data3 << endl; // "A B C"

    char data4[] = "A";
    RemoveDups( data4 );
    cout << data4 << endl; // "A"

    char data5[] = "";
    RemoveDups( data5 );
    cout << data5 << endl; // ""


    //
    // Tests for functions to serialize and deserialize a doubly linked list.
    // The data must be written in binary format.
    // The expected algorithmic complexity is less than the quadratic one.
    //

    std::vector strings_vector{ "a", "bc", "", "def", "hijk" };
    const auto strings_count = strings_vector.size();

    std::vector< ListNode* > nodes_vector;
    nodes_vector.reserve( strings_count );

    srand( unsigned{} );
    size_t count{};

    List test_list;
    for ( auto data : strings_vector )
    {
        test_list.InsertTail( data );
        if ( count++ > 0 && count < strings_count )
            test_list.Tail()->rand = nodes_vector[ rand() % ( count > 1 ? count - 1 : count ) ];
        nodes_vector.push_back( test_list.Tail() );
    }

    const char* path = "test.bin";

    auto serialize_func = [ &path ]( List& input_list, bool serialize )
    {
        using FILE_PTR = unique_ptr< FILE, decltype( &fclose ) >;
        FILE_PTR file( fopen( path, serialize ? "wb" : "rb" ), &fclose );
        if ( !file )
        {
            cerr << "Can't open file by path \"" << path << "\"" << endl;
            return false;
        }

        if ( serialize )
            input_list.Serialize( file.get() );
        else
            input_list.Deserialize( file.get() );

        return true;
    };

    auto check_func = [ &serialize_func ]( List& input_list, List& output_list )
    {
        if ( !serialize_func( input_list, true ) )
            return false;

        if ( !serialize_func( output_list, false ) )
            return false;

        if ( input_list != output_list )
        {
            cerr << "Deserializing list failed" << endl;
            return false;
        }

        return true;
    };

    List output_list;
    if ( !check_func( test_list, output_list ) )
        return 1;

    cout << "Test with non-empty lists is successful" << endl << endl;

    test_list.Clear();
    output_list.Clear();

    if ( !check_func( test_list, output_list ) )
        return 1;

    cout << endl << "Test with empty lists is successful" << endl << endl;

    return 0;
}
