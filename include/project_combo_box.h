#ifndef PROJECT_COMBO_BOX_H
#define PROJECT_COMBO_BOX_H

#include <QObject>
#include <QComboBox>

class ProjectComboBox : public QComboBox
{
    Q_OBJECT
public:
    ProjectComboBox( QWidget* object = nullptr );
    ~ProjectComboBox();
    void showPopup() override;
};

#endif // PROJECT_COMBO_BOX_H
