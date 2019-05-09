

#include "util.h"

#include <QDir>

QString HDC::Utility::GetAbsolutePath(const QString& path){
	auto qdirpath = QDir(path);
	auto absoluteTestPath = qdirpath.cleanPath(qdirpath.absoluteFilePath(path.toStdString().c_str()));
	return absoluteTestPath;
}

QString HDC::Utility::GetAbsolutePath(const std::string& path){
    return GetAbsolutePath(QString(path.c_str()));
}

QString HDC::Utility::GetAbsolutePath(const char* path){
    return GetAbsolutePath(QString(path));
}
