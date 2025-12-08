#include "setupfont.h"

setupFont::setupFont() : setting("MySchool" , "ManagementApp") {} ;

void setupFont::saveFont(QFont &font, QString group)
{
    setting.beginGroup(group) ;
    setting.setValue("fontFamily" , font.family()) ;
    setting.setValue("fontSize" , font.pointSize()) ;
    setting.setValue("fontBold" , font.bold()) ;
    setting.setValue("fontItalic" , font.italic()) ;
    setting.endGroup() ;
}

void setupFont::loadFont(QFont &font, QString group)
{
    setting.beginGroup(group) ;
    font.setFamily(setting.value("fontFamily" , "Segoe UI").toString()) ;
    font.setPointSize(setting.value("fontSize" , 9).toInt()) ;
    font.setBold(setting.value("fontBold" , false).toBool()) ;
    font.setItalic(setting.value("fontItalic" , false).toBool()) ;
}
