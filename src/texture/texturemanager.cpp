#include "texturemanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QImage>
#include <QFile>

#include <deque>
#include <tuple>
#include <cassert>
#include <utility>


unsigned int HDC::TextureManager::tunits{0xFFFFFFFF};


