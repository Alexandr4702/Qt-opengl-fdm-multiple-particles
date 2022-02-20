#ifndef QMAINWINDOWS__H
#define QMAINWINDOWS__H

#include <QWidget>
#include "gl_game.h"

class Qmainwindows_ :public QWidget
{
//    Q_OBJECT
public:
     Qmainwindows_();
     GL_GAME* game;
     float ratio = 0.7;
protected:
    void resizeEvent(QResizeEvent *event)override ;
};


#endif // QMAINWINDOWS__H
