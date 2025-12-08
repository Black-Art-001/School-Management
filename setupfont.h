#ifndef SETUPFONT_H
#define SETUPFONT_H

#include <QFont>
#include <QSettings>
#include <QString>



#define UIFont "UIfont"
#define TableFont "TableFont"

class setupFont
{
public:
    setupFont() ;
    void saveFont(QFont & font , QString group) ;
    void loadFont(QFont & font , QString group) ;
private :
    QSettings setting ;
};

#endif // SETUPFONT_H
