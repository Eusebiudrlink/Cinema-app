#pragma once
#include "repo.h"
#include <fstream>
class RepoFilmeFile : public Repo {

private:
	std :: string fName;
	void load_from_file();
	void write_to_file();

public:
	RepoFilmeFile(string fName) :Repo(), fName{ fName }{
		load_from_file();
	}
	void add_film(Film& film) override  {
		Repo::add_film(film);
		write_to_file();
	}
	void delete_film(Film& film)override{
		Repo::delete_film(film);
		write_to_file();
	}
	void update_film(Film film)override {
		Repo::update_film( film);
		write_to_file();
	}

};