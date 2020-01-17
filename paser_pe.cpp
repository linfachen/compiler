#include <iostream>


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









