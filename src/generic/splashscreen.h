#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QSplashScreen>

namespace Generic {

class SplashScreen : public QSplashScreen
{
    Q_OBJECT

public:
    explicit SplashScreen(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);
    
signals:
    
public slots:
    
};

}

#endif // SPLASHSCREEN_H
