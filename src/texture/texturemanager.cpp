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


unsigned int QQE::TextureManager::tunits{0xFFFFFFFF};


