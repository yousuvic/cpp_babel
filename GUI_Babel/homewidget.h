#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>
#include "ui_homewidget.h"

class homeWidget : public QWidget
{
	Q_OBJECT

public:
	homeWidget(QWidget *parent = 0);
	~homeWidget();

private:
	Ui::homeWidget ui;
};

#endif // HOMEWIDGET_H
