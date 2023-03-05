#pragma once
#include "domain.h"
#include <exception>
#include <assert.h>
using namespace std;


class MyException : public exception {
public :
	const char* what() const noexcept {
		return "Datele filmului sunt invalide";
	}
};

class Validator {
public:
	Validator();
	void valideaza(const Film& film);
	void test_validare();
};