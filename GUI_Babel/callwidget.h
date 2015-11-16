#ifndef CALLWIDGET_H
#define CALLWIDGET_H

#include <QWidget>
#include "ui_callwidget.h"

class callWidget : public QWidget
{
	Q_OBJECT

public:
	callWidget(QWidget *parent = 0);
	~callWidget();

private:
	Ui::callWidget ui;
};

#endif // CALLWIDGET_H
