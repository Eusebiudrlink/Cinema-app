#pragma once
#include <assert.h>
#include <iostream>
#include <vector>
#include "service.h"
#include "repo.h"

class test{
private:
	void test_creeaza_film();
	void test_adauga_film();
	void test_sterge_film();
	void test_modifica_film();
	void test_srv_adauga_film();
	void test_srv_sterge_film();
	void test_srv_update_film();
	void test_srv_cauta_film();
	void test_cos_filme();

public:
	void run_all_teste();


};