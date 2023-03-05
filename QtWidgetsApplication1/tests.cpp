
#include "tests.h"
#include "validate.h"
#include "cos.h"



using namespace std;
void test::test_creeaza_film() {
	string titlu{ "hoia" }, actor{ "baciu" }, gen("1");
	Film movie{ "ana","are","mere",3 };
	assert(movie.get_titlu() == "ana");
	assert(movie.get_gen() == "are");
	assert(movie.get_actor() == "mere");
	assert(movie.get_an() == 3);

	movie.set_actor(actor);
	movie.set_gen(gen);
	movie.set_titlu(titlu);
	movie.set_an(1);

}

void test::test_adauga_film() {
	Film movie{ "ana","are","mere",3 };
	Film movie2{ "ana1","are1","mere1",4 };
	Repo lista{};
	assert(lista.get_lungime() == 0);
	lista.add_film(movie);
	vector<Film> copie{ lista.get_lista() };


	assert(lista.get_lungime() == 1);
	assert(copie[0].get_titlu() == "ana");
	assert(copie[0].get_gen() == "are");
	assert(copie[0].get_actor() == "mere");
	assert(copie[0].get_an() == 3);

	lista.add_film(movie2);
	copie = lista.get_lista();
	assert(lista.get_lungime() == 2);
	assert(copie[1].get_titlu() == "ana1");
	assert(copie[1].get_gen() == "are1");
	assert(copie[1].get_actor() == "mere1");
	assert(copie[1].get_an() == 4);

	try {
		lista.add_film(movie2);
	}

	catch (...) {
		assert(true);
	}
}

void test::test_sterge_film()
{
	Film movie{ "ana","are","mere",3 };
	Film movie2{ "ana1","are1","mere1",4 };
	Repo lista{};
	vector<Film> copie{};
	lista.add_film(movie2);
	lista.add_film(movie);
	lista.delete_film(movie2);
	assert(lista.get_lungime() == 1);
	copie = lista.get_lista();
	assert(copie[0].get_titlu() == "ana");
	assert(copie[0].get_gen() == "are");
	assert(copie[0].get_actor() == "mere");
	assert(copie[0].get_an() == 3);
	try {
		lista.cauta_film("gresit");
	}
	catch (...) {
		assert(true);
	}



}

void test::test_modifica_film()
{
	Film movie{ "ana","are","mere",3 };
	Film movie2{ "ana","are1","mere1",4 };
	Repo lista{};
	vector<Film> copie{};
	lista.add_film(movie);

	lista.update_film(movie2);
	copie = lista.get_lista();
	assert(copie[0].get_titlu() == "ana");
	assert(copie[0].get_gen() == "are1");
	assert(copie[0].get_actor() == "mere1");
	assert(copie[0].get_an() == 4);

}

void test::test_srv_adauga_film()
{

	Repo lista{};
	Validator valid{};
	Srv service{ lista,valid };

	assert(lista.get_lungime() == 0);

	vector<Film> copie{};

	service.srv_add("ana", "1", "mere", 3);

	

	copie = service.get_lista_srv();

	assert(copie[0].get_titlu() == "ana");
	assert(copie[0].get_gen() == "1");
	assert(copie[0].get_actor() == "mere");
	assert(copie[0].get_an() == 3);

	service.srv_add("ana1", "1", "mere1", 4);
	copie = service.get_lista_srv();
	assert(copie[1].get_titlu() == "ana1");
	assert(copie[1].get_gen() == "1");
	assert(copie[1].get_actor() == "mere1");
	assert(copie[1].get_an() == 4);

	try {
		service.srv_delete("nu e");
	}
	catch (...) {
		assert(1 == 1);
	}

}

void test::test_srv_sterge_film()
{
	Repo lista{};
	Validator valid{};
	Srv service{ lista,valid };

	vector<Film> copie{};
	service.srv_add("ana1", "1", "mere1", 4);
	service.srv_add("ana", "1", "mere", 3);
	service.srv_delete("ana1");
	copie = service.get_lista_srv();
	assert(copie[0].get_titlu() == "ana");
	assert(copie[0].get_gen() == "1");
	assert(copie[0].get_actor() == "mere");
	assert(copie[0].get_an() == 3);

	try {
		service.srv_delete("nu e");
	}
	catch (...) {
		assert(1 == 1);
	}
}

void test::test_srv_update_film()
{
	Repo lista{};
	Validator valid{};
	Srv service{ lista,valid };

	vector<Film> copie{};
	service.srv_add("ana", "1", "mere", 3);

	service.srv_update("ana", "1", "mere1", 4);
	copie = service.get_lista_srv();
	assert(copie[0].get_titlu() == "ana");
	assert(copie[0].get_gen() == "1");
	assert(copie[0].get_actor() == "mere1");
	assert(copie[0].get_an() == 4);

	try {
		service.srv_update("NU E", "1", "mere1", 4);
	}
	catch (...) {

	}
}

void test::test_srv_cauta_film()
{

	Repo lista{};
	Validator valid{};
	Srv service{ lista,valid };
	Film rez{ "ana", "1", "mere", 3 };
	service.srv_add("ana", "1", "mere", 3);

	rez = service.srv_cauta_film("ana");
	try {
		rez = service.srv_cauta_film("anaa");
	}
	catch (...) {
		assert(true);
	}

	service.srv_add("aanaa", "1", "mere", 2);

	string an{ "an" }, titlu{ "titlu" };

	service.sortedAn();
	service.sortedTitlu();
	service.an_filter(1);
	service.gen_filter("ana");
}

void test::test_cos_filme()
{
	Repo lista{};
	Validator valid{};
	Srv service{ lista,valid };
	Film rez{ "ana", "1", "mere", 3 };
	service.srv_add("ana", "1", "mere", 3);

	WishList wishlist{};

	auto filme = service.get_lista_srv();

	wishlist.genereaza_filme(filme, 3);

	wishlist.adauga_film_wishlist("ana", "1", "mere", 3);
	wishlist.goleste_cos();
	auto wish = wishlist.get_lista_cos();
	wishlist.exporta_cos("test_Export");

}



void test::run_all_teste() {
	cout << "start teste:" << endl;
	test_creeaza_film();
	test_adauga_film();
	test_sterge_film();
	test_modifica_film();
	test_srv_adauga_film();
	test_srv_sterge_film();
	test_srv_update_film();
	test_srv_cauta_film();
	test_cos_filme();
	
	Validator vali{};
	vali.test_validare();

	
	cout << "finish teste!!!" << endl;

}