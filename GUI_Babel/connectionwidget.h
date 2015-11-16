#ifndef CONNECTIONWIDGET_H
#define CONNECTIONWIDGET_H

#include <QWidget>
#include "ui_connectionwidget.h"

class connectionWidget : public QWidget
{
	Q_OBJECT

public:
	connectionWidget(QWidget *parent = 0);
	~connectionWidget();

private:
	Ui::connectionWidget ui;

public slots:
	void handleConnectionButton();
};

#endif // CONNECTIONWIDGET_H
