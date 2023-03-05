#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <QLabel>
#include "tests.h"
#include "repofile.h"
#include "Filmegui.h"
#include "histogramaGUI.h"
void runGUI(int argc, char* argv[])
{
	QApplication a(argc, argv);
	RepoFilmeFile rep{ "store_filme.txt" };
	Validator valid;
	Srv ctr{ rep,valid };
	WishList wish{};
	FilmeStoreGUI gui{ ctr ,wish};
	gui.show();

	a.exec();

}

int main(int argc, char* argv[])
{
	test testare{};
	testare.run_all_teste();

	runGUI(argc, argv);
	
	return 0 ;
}
