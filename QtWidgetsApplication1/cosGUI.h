#pragma once
#include "domain.h"
#include "service.h"
#include <qwidget.h>

#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <qpalette.h>
#include <qbrush.h>
#include <string>
#include <set>
#include <cstdlib>
#include "cos.h"

using std::to_string;
using std::set;
using std::vector;

class CosGui : public QWidget, public Observer {
private:
	
	Srv& serv;
	WishList& wishlist;
	QHBoxLayout* lyCosMain = new QHBoxLayout;

	QListWidget* lst;
	QPushButton* btnGenre;
	QPushButton* btngoleste;
	QPushButton* btnexport;
	QPushButton* btnadd;
	QLineEdit* txt1;
	QLineEdit* txt2;
	QLineEdit* txt3;
	QLineEdit* txt4;
	QLineEdit* txtgenre;

	void initCosGui();
	void conectSignal();
	void reloadGui(vector<Film> filme);

	void add_film();
	void genre();
	void goleste();
	void update() override {
		reloadGui(wishlist.get_lista_cos());
	}
	
public:
	CosGui(Srv& serv, WishList& wishlist) :serv{ serv }, wishlist{wishlist}{
		initCosGui();
		conectSignal();
		reloadGui(wishlist.get_lista_cos());
	};



};
