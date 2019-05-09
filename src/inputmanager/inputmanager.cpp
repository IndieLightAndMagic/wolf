#include "inputmanager.h"
#include <iostream>
InputManager::InputManager( QObject *parent ) : QObject( parent ) {
    
}

bool InputManager::eventFilter( QObject *dist, QEvent *event )
{
    Q_UNUSED(dist);
    auto et = event->type();
    if( et == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>( event );

        if ( keyEvent->key() == Qt::Key_Up ) {emit up_arrow(); return true;}
        else if ( keyEvent->key() == Qt::Key_Down ) {emit down_arrow(); return true;}
        else if ( keyEvent->key() == Qt::Key_Left ) {emit left_arrow(); return true;}
        else if ( keyEvent->key() == Qt::Key_Right ) {emit right_arrow(); return true;}
        else if ( keyEvent->key() == Qt::Key_Escape ) {emit escape(); return true;}


    } else if ( et == QEvent::Wheel) {

        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>( event );
        QPoint numSteps = wheelEvent->angleDelta() / 120;
        emit m_wheel(numSteps.y());

    } else if ( et == QEvent::MouseButtonRelease) {

        emit m_wheelreleased();

    }

    return false;
}
