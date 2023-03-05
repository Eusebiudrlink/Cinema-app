#include "validate.h"
#include <fstream>
Validator::Validator() {
}

void Validator::valideaza(const Film& film)
{
	std::string err{};
	if (film.get_actor() == "" || film.get_an()<0 || film.get_gen() == "" || film.get_titlu() == "")
		throw  MyException();
	if(film.get_gen()!="sf"&& film.get_gen()!="actiune" && film.get_gen()!="romantic" && film.get_gen()!="1")
		throw  MyException();


}

void Validator::test_validare()
{
	Film film{ "ana","1","mere",1 };
	valideaza(film);
	

	Film film_rau{ "","","",-1 };
	try {
		valideaza(film_rau);
	}
	catch (MyException& e) {
		assert(strcmp(e.what() ,"Datele filmului sunt invalide")==0);


		ofstream log;
		log.open("log.txt");
		log << e.what(); 
		log.close();
	}


}
