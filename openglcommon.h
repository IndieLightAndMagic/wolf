#ifndef __OPENGLCOMMON_H__
#define __OPENGLCOMMON_H__
#include <QOpenGLFunctions>
#ifdef __APPLE__
#include <QOpenGLFunctions_3_3_Core>
#else
#include <QOpenGLFunctions_4_3_Core>
#endif
#endif //__OPENGLCOMMON_H__