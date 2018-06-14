#include "clicklabel.h"


ClickLabel::ClickLabel(QWidget* parent)
{


}

void ClickLabel::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked(this);
}
