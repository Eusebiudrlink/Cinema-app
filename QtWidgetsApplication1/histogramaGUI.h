#pragma once
#include <qwidget.h>
#include <qpainter.h>
#include "Filmegui.h"
class HistogramaGUI : public QWidget,public Observer
{

	WishList& wishlist;
public:
	HistogramaGUI(WishList& wishlist) : wishlist{ wishlist } {
		wishlist.addObserver(this);
	}

	void update() override {
		repaint();
	}
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		int x = 10;
		
		QRect boundingRect;
		for (const auto& film : wishlist.get_lista_cos())
		{
			const QRect rectangle = QRect(x, 0, 100, 50);
			p.drawText(rectangle, 0, QByteArray::fromStdString(film.get_titlu()), &boundingRect);
			p.drawRect(x, 30, 20, 30);
			x += 40;
		}
		

	}




};