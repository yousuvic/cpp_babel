#ifndef BABELGUI_H
#define BABELGUI_H

#include <QtWidgets/QMainWindow>
#include <QSignalMapper>
#include <Qmenu>
#include <QList>
#include <vector>
#include <list>
#include "ui_babelgui.h"
#include "homewidget.h"
#include "conversationwidget.h"

class babelGUI : public QMainWindow
{
	Q_OBJECT

public:
	babelGUI(QWidget *parent = 0);
	~babelGUI();

	QList<QAction*> actionList;
	QMenu statusMenu;
	std::vector<std::string> statusVec;
	QSignalMapper *signalMapper;
	
	homeWidget *home;
	QWidget *centralWidget;

	std::map<std::string, std::string> friendList;

private:
	Ui::babelGUIClass ui;


private slots :
	void changeStatus(int);
	void returnToHomeWidget();
	void changeCentralWidget(int index);
};

#endif // BABELGUI_H
