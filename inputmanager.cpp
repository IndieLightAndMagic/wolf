#include "inputmanager.h"

InputManager::InputManager( QObject *parent ) : QObject( parent ) {
    
}

bool InputManager::eventFilter( QObject *dist, QEvent *event )
{
    if( event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>( event );

        if ( keyEvent->key() == Qt::Key_Up ) {emit up_arrow(); return true;}
        else if ( keyEvent->key() == Qt::Key_Down ) {emit down_arrow(); return true;}
        else if ( keyEvent->key() == Qt::Key_Left ) {emit left_arrow(); return true;}
        else if ( keyEvent->key() == Qt::Key_Right ) {emit right_arrow(); return true;}
        else if ( keyEvent->key() == Qt::Key_Escape ) {emit escape(); return true;}
    }

    return false;
}
