#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__
#include <QObject>
#include <QKeyEvent>
class InputManager : public QObject
{
    Q_OBJECT
public:
    InputManager( QObject *parent = 0 );
signals:
    void up_arrow();
    void down_arrow();
    void left_arrow();
    void right_arrow();
    void escape();

protected:
    bool eventFilter( QObject *dist, QEvent *event );
};


#endif/* __INPUTMANAGER_H__ */