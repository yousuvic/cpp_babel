#include "connectionwidget.h"
#include "babelgui.h"
#include <iostream>

connectionWidget::connectionWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.connectionBtn, SIGNAL(clicked()), this, SLOT(handleConnectionButton()));
}

connectionWidget::~connectionWidget()
{

}

void connectionWidget::handleConnectionButton() {
	this->destroy();
	babelGUI *w = new babelGUI();

	w->show();
}
