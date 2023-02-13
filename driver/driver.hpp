#pragma once

#include <windows.h>

#include <string>

#include "../dependencies/xorstring/xorstring.hpp"
#include "../dependencies/lazy_importer/lazy_importer.hpp"

class driver_t
{
	enum class command_t
	{
		get_base,
		get_peb,
		copy_memory
	};

	struct large_argument_t { const std::uint8_t* from_buffer; const std::size_t size; const bool validated; };

	using NtMapVisualRelativePoints_t = std::uintptr_t( * )( const large_argument_t* const large_argument, const std::uint8_t* const to_buffer, command_t command, std::uint64_t from_process_id, std::uint64_t to_process_id );
	const NtMapVisualRelativePoints_t NtMapVisualRelativePoints = lf( NtMapVisualRelativePoints ).in< NtMapVisualRelativePoints_t >( lm( "win32u.dll" ).get( ) );

	const std::uint64_t from_process_id = lf( GetCurrentProcessId )( ), to_process_id;

	static struct _peb
	{
		std::uint8_t ldr = 0x18;

		std::uint8_t list_entry = 0x10;

		std::uint8_t dll_base = 0x30;
		std::uint8_t base_dll_name = 0x58;

		std::uint8_t unicode_start = 0x60;
	};

public:
	explicit driver_t( ) : to_process_id{ 0 } { } bool initiate( const char* const window_name );

	template < class value_t = std::uintptr_t > value_t raw_read( const auto read_address )
	{
		value_t value { };

		if ( !read_address )
			return value;

		large_argument_t large_argument { reinterpret_cast< std::uint8_t* >( read_address ), sizeof( value_t ) };

		NtMapVisualRelativePoints( &large_argument, reinterpret_cast< std::uint8_t* >( &value ), command_t::copy_memory, to_process_id, from_process_id );

		return value;
	}

	template < class value_t = std::uintptr_t > value_t __forceinline read( const auto read_address )
	{
		return raw_read< value_t >( read_address );
	}

	template < class buffer_t = std::uintptr_t >
	__forceinline buffer_t read( std::uintptr_t read_address, const std::initializer_list< std::uint16_t >&& offsets )
	{
		buffer_t buffer;

		for ( auto i = 0ull; i < offsets.size( ) - 1; ++i )
			read_address = raw_read<std::uintptr_t>( read_address + *( offsets.begin( ) + i ) );

		return read< buffer_t >( read_address + *( offsets.end( ) - 1 ) );
	}

	template < class value_t = std::uintptr_t > void read_arr( const auto read_address, value_t* buffer, const std::size_t size ) const
	{
		if ( !read_address )
			buffer = nullptr;

		large_argument_t large_argument { reinterpret_cast< std::uint8_t* >( read_address ), sizeof( value_t ) * size };

		NtMapVisualRelativePoints( &large_argument, reinterpret_cast< std::uint8_t* >( buffer ), command_t::copy_memory, to_process_id, from_process_id );
	}

	template < class value_t > void write( const auto write_address, const value_t& value )
	{
		if ( !write_address )
			return;

		large_argument_t large_argument { reinterpret_cast< const std::uint8_t* >( &value ), sizeof( value ) };

		NtMapVisualRelativePoints( &large_argument, reinterpret_cast< std::uint8_t* >( write_address ), command_t::copy_memory, from_process_id, to_process_id );
	}

	template < class value_t = std::uintptr_t > void write_arr(const std::uintptr_t address, value_t* buffer, const std::size_t size) const
	{
		if ( !address || !buffer )
			return;

		large_argument_t large_argument{ buffer, sizeof(value_t) * size };

		NtMapVisualRelativePoints(&large_argument, reinterpret_cast<std::uint8_t*>(address), command_t::copy_memory, from_process_id, to_process_id);
	}

	std::uintptr_t base( )
	{
		return NtMapVisualRelativePoints( nullptr, nullptr, command_t::get_base, from_process_id, to_process_id );
	}

	std::uintptr_t dll( const std::wstring& dll_name )
	{
		const auto peb_base = NtMapVisualRelativePoints( nullptr, nullptr, command_t::get_peb, from_process_id, to_process_id );

		_peb offsets;

		if ( auto ldr = read( peb_base + offsets.ldr ) )
		{
			if ( auto list_entry = read( ldr + offsets.list_entry ) )
			{
				while ( read( list_entry + offsets.dll_base ) )
				{
					std::wstring name { };

					auto length = read<USHORT>( list_entry + offsets.base_dll_name ); auto start = read( list_entry + offsets.unicode_start );	

					name.reserve( length / 2 );

					for ( auto i = 0u; i < length / 2; ++i )
						name.push_back( read< WCHAR>( start + i * 2 ) );
					
					if ( name == dll_name )
						return read( list_entry + offsets.dll_base );

					list_entry = read( list_entry );
					
					if ( !list_entry )
						return 0;
				}
			}
		}
	}

	std::string read_raw_bytes(std::uintptr_t address, const size_t size);
		std::string read_unicode_string(std::uintptr_t address, const int size = 32) const;
}
extern driver;