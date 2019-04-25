#ifndef __UTIL_H__
#define __UTIL_H__
#include "objid.h"
#include <vector>
#include <QString>

//100 Days of Code
namespace HDC {

    class Utility {
    public:
        static QString GetAbsolutePath(const std::string& path);
        static QString GetAbsolutePath(const char * path);
        static QString GetAbsolutePath(const QString& path);
        
    };
    template <typename T>
	class ABuffer : public std::vector<T>, public ObjId{
		protected:
		bool m_valid{false};	
		public:
		ABuffer(const T* pBuffer = nullptr, long size = 0): ObjId(){
			if (!pBuffer || !size) return;
			for (auto index = 0; index < size; ++index)
				this->push_back(pBuffer[index]);
			m_valid = true;
		}
	};

	class AFile : public ABuffer<char>{
		std::string filename{};
		public:
		AFile(const char* path):ABuffer<char>(){
			auto fp = std::fopen(path, "r");
			if(!fp || std::fseek(fp, 0, SEEK_END)){
				if(fp) std::fclose(fp);
				return;
			}
			auto sz = ftell(fp);
			if(sz == -1L || std::fseek(fp, 0, SEEK_SET)) {
				std::fclose(fp);
				return;
			}
			this->resize(sz);
			if(std::fread(this->data(), 1, sz, fp)) {
				filename = std::string{path};
				m_valid = true;
			}
			std::fclose(fp);
			return;
		}	
	};

}



#endif //__UTIL_H__