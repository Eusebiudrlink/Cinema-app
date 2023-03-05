#pragma once
#include "repo.h"
#include "validate.h"
#include "domain.h"
#include <vector>
#include <functional>
#include <algorithm>
#include "undo.h"


using namespace std;

class Sortare;

class Srv {
public:


	Srv(Repo& rep, Validator& valid) :repository{ rep }, valid{ valid }{
	}


	void srv_add(const std::string& titlul, const std::string& genul, const std::string& actorul, int anul);

	const vector<Film> get_lista_srv()const;

	void srv_delete(const std::string& titlul);

	void srv_update(const std::string& titlul, const std::string& genul, const std::string& actorul, int anul);

	Film srv_cauta_film(std::string titlul);


	vector<Film> filter(std::function<bool(const Film&)> fct);

	vector<Film> an_filter(int an);

	vector<Film> gen_filter(string gen);

	vector<Film> sortedAn();

	vector<Film> sortedTitlu();

	int nr_sf();

	int nr_Romantic();

	int nr_Roman();

	void undo();
private:
	Repo& repository;
	Validator& valid;
	std::vector<unique_ptr<ActiuneUndo>> undoActions;
};



