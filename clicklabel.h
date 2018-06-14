#ifndef CLICKLABEL_H
#define CLICKLABEL_H
#include <QWidget>
#include <QLabel>

class ClickLabel:public QLabel
{
    Q_OBJECT
public:
    ClickLabel(QWidget* parent=0);

signals:
    void clicked(ClickLabel* click);

protected:
    void mouseReleaseEvent(QMouseEvent*);
};

#endif // CLICKLABEL_H
