#pragma once
#include "service.h"
#include "cos.h"


class Consola {
public:
	Consola(Srv& serv, WishList wishlist) :serv{ serv }, cos{ wishlist }{
	}

	void start_consola();
	void adauga_film();
	void afiseaza_filme();
	void sterge_film();
	void modifica_film();
	void cauta_film();
	void filtrare_carti();
	void sortare_carti();
	
	void menu_wish_list();
	void show_menu_wishlist();
	void adauga_wishlist();
	void afiseaza_cos();
	void genereaza();
	void exporta();
	void undo_ui();

private:
	Srv& serv;
	WishList cos;
	void show_menu();
	
};