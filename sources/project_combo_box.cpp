#include "include/precompiled.h"
#include "include/project_combo_box.h"

ProjectComboBox::ProjectComboBox( QWidget* object )
    : QComboBox( object )
{
}

ProjectComboBox::~ProjectComboBox()
{

}

void ProjectComboBox::showPopup()
{
    QComboBox::showPopup();
    QWidget* popup = this->findChild<QFrame*>();
    popup->resize( width() * 1.5, height() * count() + 10 );
    popup->move( mapToGlobal( QPoint( width() + 10, 0 ) ) );
}
