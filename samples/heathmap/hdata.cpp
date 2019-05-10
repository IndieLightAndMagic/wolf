#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <vector>
#include <string>
#include <cstdio>
#include <map>
#include <QFile>
#include <QString>

#include "hdata.h"

static json _json;
void fast(std::string filename){
	
	auto stdfile = std::fopen(filename.c_str(), "r");
	auto qfile = QFile();
	auto qsize = qfile.size();
	qfile.open(stdfile, QIODevice::ReadOnly);
	auto qmap = qfile.map(0, qsize);
	_json = json::parse(qmap);


}

