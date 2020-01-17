#include "paser_pe.h"

char * get_file_buffer(const char *filename,int *file_size) {
	FILE * file = fopen(filename, "rb");
	if (file == nullptr) {
		std::cerr << "open file fail!" << std::endl;
		//return nullptr;
		exit(0);
	}
	fseek(file, 0, SEEK_END);
	*file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	char *file_buffer = (char *)malloc(*file_size);
	fread(file_buffer, 1, *file_size, file);

	return file_buffer;
}



PE::PE(const char *filename) {
	file_name = filename;
	file_buffer = get_file_buffer(filename, &file_size);
}

PE::~PE() {
	if (file_buffer) free(file_buffer);
}

bool PE::is_pefile() {
	return *file_buffer == 'M' && *(file_buffer + 1) == 'Z';
}


void PE::paser() {
	int offset;
	if (!is_pefile()) {
		std::cerr << file_name << ": is not a pe file!" << std::endl;
		exit(0);
	}

	memcpy(&image_dos_header, file_buffer, sizeof(IMAGE_DOS_HEADER));

	offset = image_dos_header.e_lfanew;
	memcpy(&image_nt_headers, file_buffer+offset, sizeof(IMAGE_NT_HEADERS));

	struct tm * timeinfo;
	char buffer[128];
	timeinfo = localtime((time_t*)&(image_nt_headers.FileHeader.TimeDateStamp));
	strftime(buffer, sizeof(buffer), "Now is %Y/%m/%d %H:%M:%S", timeinfo);
	
	std::cout << buffer << std::endl;


}