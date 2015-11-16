#include "callwidget.h"

callWidget::callWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.spiner->start();
}

callWidget::~callWidget()
{

}
