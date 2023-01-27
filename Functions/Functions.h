//
//  Functions.h
//
//  Created by Vitaliy Zudov on 07.12.2022.
//

#pragma once

#include <iostream>
#include <vector>

//
//  Write a function that takes a signed integer as input and prints its binary representation.
//  Variant of the solution without STL
//

template< typename T >
std::enable_if_t<std::is_integral_v<T>, void> PrintBitset( T num )
{
    if ( !num )
    {
        std::cout << num << std::endl;
        return;
    }

    size_t bits_count = sizeof( T ) * 8;
    const T mask = ( T )1 << ( bits_count - 1 );
    while( !( num & mask ) )
    {
        num <<= 1;
        --bits_count;
    }

    char result[ bits_count + 1 ];
    for ( auto i = 0; i != bits_count; ++i )
    {
        result[i] = ( num & mask ) ? '1' : '0';
        num <<= 1;
    }

    result[ bits_count ] = 0;

    std::cout << result << std::endl;
}

//  Variant of the solution with boolean vector

template< typename T >
std::enable_if_t<std::is_integral_v<T>, void> PrintBitsetVec( T num )
{
    size_t bits_count = sizeof( T ) * 8;
    std::vector<bool> result;
    result.reserve( bits_count );

    do {
        result.push_back( num & 1 );
        num >>= 1;
        --bits_count;
    }
    while( num && bits_count );

    for ( auto it = result.rbegin(); it != result.rend(); ++it )
        std::cout << *it;

    std::cout << std::endl;
}


//
//  Write a function to remove consecutively duplicate characters in a string
//

void RemoveDups( char* str )
{
    char* it = str;
    while ( *str )
    {
        if ( it != str )
            *it = *str;
        ++it;

        while ( *( str + 1 ) == *str && *( str + 1 ) )
            ++str;
        ++str;
    }
    *it = 0;
}
