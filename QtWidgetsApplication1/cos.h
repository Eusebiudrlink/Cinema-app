#pragma once

#include "repo.h"
#include "validate.h"
#include "service.h"
#include <vector>
#include <fstream>
#include "domain.h"

class WishList:public Observable
{	
public:
	WishList(){
	};

	int  adauga_film_wishlist(const std::string& titlul, const std::string& genul, const std::string& actorul, int anul);

	void goleste_cos();

	const vector<Film> get_lista_cos()const;

	int genereaza_filme(vector<Film> lista_originala, int nr_filme);
	void exporta_cos(string file);

private:
	vector<Film> cos_filme;
	


};