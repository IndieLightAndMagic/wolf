#ifndef __LEVEL_COMPRESSED_PNG__
#define __LEVEL_COMPRESSED_PNG__
#include <vector>
class __level_compressed_png{
public:
	std::vector<unsigned char> atlas{};
	const unsigned int palette_offset{0};
	const unsigned int sprites_offset{0};
	const unsigned int palette_entries{0};
	const unsigned int sprites_pixels{0};
	unsigned char* GetAtlasData(){
		return atlas.data();
	}
	__level_compressed_png(unsigned int poff, unsigned int soff, unsigned int pentries, unsigned int sppixels):
	palette_offset(poff),
	sprites_offset(soff),
	palette_entries(pentries),
	sprites_pixels(sppixels){}
	//poff : palette offset (bytes)
	//soff : sprite offset (bytes)
	//pentries : number of entries in the palette (not bytes, ENTRIES!)
	//sppixels : number of pixels in the atlas sprite (pixels)
};
class __level_compressed_png_level1 : public __level_compressed_png {
public:
	__level_compressed_png_level1();
};

#endif //__LEVEL1_COMPRESSED_PNG__