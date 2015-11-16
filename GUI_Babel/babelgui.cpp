#include "babelgui.h"
#include <iostream>

babelGUI::babelGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	/*** Status Menu ***/
	statusVec.push_back("Online");
	statusVec.push_back("Busy");
	statusVec.push_back("Abscent");
	statusVec.push_back("Offline");
	QSignalMapper* signalMapper = new QSignalMapper(this);
	for (int i = 0; i <= 3; i++) {
		std::string img = ":/babelGUI/Resources/" + statusVec.at(i) + ".png";
		actionList.push_back(new QAction(QIcon(img.c_str()), QString::fromStdString(statusVec.at(i)), this));
		connect(actionList.at(i), SIGNAL(triggered()), signalMapper, SLOT(map()));
		signalMapper->setMapping(actionList.at(i), i);
	}
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(changeStatus(int)));
	statusMenu.addActions(actionList);
	ui.StatusBtn->setMenu(&statusMenu);
	/*******************/

	ui.stakedWidget->addWidget(new homeWidget(ui.stakedWidget));
	QObject::connect(ui.homeBtn, SIGNAL(clicked()), this, SLOT(returnToHomeWidget()));
	
	/*** Friend list ***/

	//Remplacer par le retour de "SendFriendList" server commande.
	friendList.insert(std::make_pair("toto", "Available"));
	friendList.insert(std::make_pair("tata", "Busy"));

	ui.friendList->addItem(new QListWidgetItem(QIcon(":/babelGUI/Resources/Online.png"), "toto"));
	ui.friendList->addItem(new QListWidgetItem(QIcon(":/babelGUI/Resources/Offline.png"), "tata"));
	ui.stakedWidget->addWidget(new conversationWidget("toto", ui.stakedWidget, this));
	ui.stakedWidget->addWidget(new conversationWidget("tata", ui.stakedWidget, this));
	QObject::connect(ui.friendList, SIGNAL(currentRowChanged(int)), this, SLOT(changeCentralWidget(int)));
	/*******************/
}

babelGUI::~babelGUI()
{
	
}

void babelGUI::changeStatus(int status) {
	switch (status) {
		case 0 :
			ui.StatusBtn->setIcon(QIcon(":/babelGUI/Resources/Online.png"));
			break;
		case 1 :
			ui.StatusBtn->setIcon(QIcon(":/babelGUI/Resources/Busy.png"));
			break;
		case 2 :
			ui.StatusBtn->setIcon(QIcon(":/babelGUI/Resources/Abscent.png"));
			break;
		case 3:
			ui.StatusBtn->setIcon(QIcon(":/babelGUI/Resources/Offline.png"));
			break;
	}
}

void babelGUI::returnToHomeWidget() {
	ui.stakedWidget->setCurrentIndex(0);
}

void babelGUI::changeCentralWidget(int index) {
	ui.stakedWidget->slideInIdx(index + 1);
}
