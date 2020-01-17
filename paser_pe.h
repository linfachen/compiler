#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
char * get_file_buffer(const char *filename, int *file_size);

class PE {
public:
	int file_size;
	char * file_buffer;
	std::string file_name;
	IMAGE_DOS_HEADER image_dos_header;
	IMAGE_NT_HEADERS image_nt_headers;

	PE(const char *filename);
	~PE();

	bool is_pefile();
	void paser();
};