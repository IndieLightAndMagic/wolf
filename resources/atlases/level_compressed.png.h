#ifndef __LEVEL_COMPRESSED_PNG__
#define __LEVEL_COMPRESSED_PNG__
#include <vector>
class __level_compressed_png{
public:
	std::vector<unsigned char> atlas{};
	unsigned int palette_offset{64 * 64 * 11};
	unsigned char* GetAtlasData(){
		return atlas.data();
	}	
};
class __level_compressed_png_level1 : public __level_compressed_png {
public:
	__level_compressed_png_level1();
};

#endif //__LEVEL1_COMPRESSED_PNG__