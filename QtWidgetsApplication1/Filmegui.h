#pragma once
#include "domain.h"
#include "service.h"
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qdebug.h>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <qpalette.h>
#include <qbrush.h>
#include "cosGUI.h"
#include "cos.h"
#include "histogramaGUI.h"


class FilmeStoreGUI : public QWidget {
private:
	Srv& ctr;
	WishList wishlist;
	QLabel* lblCate = new QLabel{ "Filme disponibile:" };
	QHBoxLayout* lyMain = new QHBoxLayout;
	QListWidget* lst;
	QPushButton* btnSortByAn;
	QPushButton* btnSortByTitlu;
	QPushButton* btnDelete;
	QPushButton* btnUpdate;
	QPushButton* btnUndo;
	QPushButton* btnAdd;
	QPushButton* btnFilter;
	QPushButton* btnCosCrud;
	QPushButton* btnCosRead;
	QLineEdit* txtGen;
	QLineEdit* txtTitlu;
	QLineEdit* txtActor;
	QLineEdit* txtAn;
	QLineEdit* editFilterGen;



	void initGUI();
	void connectSignalsSlots();
	void reloadList(const std::vector<Film>& filme);
	void addNewFilm();
	void deleteFilm();
	void UpdateFilm();
	void UndoFilm();
	void filter();
	void creeaza_cosCrud();
	void creeaza_cosDesenat();

	
public:

	FilmeStoreGUI(Srv& ctr, WishList wishlist) :ctr{ ctr }, wishlist{ wishlist } {
		initGUI();
		connectSignalsSlots();
		reloadList(ctr.get_lista_srv());
		
	}
	
	

};