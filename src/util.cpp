

#include "util.h"

#include <QDir>

QString QQE::Utility::GetAbsolutePath(const QString& path){
	auto qdirpath = QDir(path);
	auto absoluteTestPath = qdirpath.cleanPath(qdirpath.absoluteFilePath(path.toStdString().c_str()));
	return absoluteTestPath;
}

QString QQE::Utility::GetAbsolutePath(const std::string& path){
    return GetAbsolutePath(QString(path.c_str()));
}

QString QQE::Utility::GetAbsolutePath(const char* path){
    return GetAbsolutePath(QString(path));
}
