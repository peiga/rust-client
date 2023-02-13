#include "driver.hpp"

#include "../integrity/integrity.hpp"

#include <tlhelp32.h>
#include <iostream>

driver_t driver;

bool driver_t::initiate( const char* const window_name )
{
	return lf( GetWindowThreadProcessId )( lf( FindWindowA )( window_name, nullptr ), ( DWORD* )&to_process_id );
}

std::string driver_t::read_raw_bytes(std::uintptr_t address, const size_t size)
{
	std::unique_ptr< char[ ] > temp( new char[ size ] );
	
	driver.read_arr<char>(address, temp.get(), size);
	
	return std::string(temp.get());
}

std::string driver_t::read_unicode_string(std::uintptr_t address, const int size) const
{
	char16_t temp[128] = { '\0' };

	driver.read_arr<char16_t>(address, temp, size * sizeof(std::uint16_t));
	std::string buffer = 
		integrity::utilities::to_utf8(temp);

	return buffer;
}