// gra_w_zycie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <cstdlib>

using namespace std;

//wymiary planszy
const int k = 80;
const int w = 20;

//plansza
char plansza[w][k];

//funkcja umożliwiająca wyświetlanie polskich znaków
char *tr(char *str)
{
	static char buff[256];
	char cp[] = "\245\206\251\210\344\242\230\276\253\244\217\250\235\343\340\227\275\215ąćęłńóśżźĄĆĘŁŃÓŚŻŹ";
	if (strlen(str) >= sizeof(buff)) return str;
	char *bf = buff;
	while (*str)
	{
		char *pos = strchr(cp + 18, *str);
		*(bf++) = pos ? *(pos - 18) : *str;
		++str;
	}
	*bf = 0;
	return buff;
}

//wpisanie danych do planszy przez użytkownika
char wpis_danych_do_tab(char plansza[w][k])
{
	cout << tr("Teraz będzie Pan wpisywał początkowe ułożenie żywych i martwych komórek wiersz po wierszu.") << endl;
	cout << tr("Jeżeli dana komórka ma być żywa proszę wpisać znak: $") << endl;
	cout << tr("Jeżeli ma być martwa, to proszę wpisać znak 0.") << endl;
	cout << tr("Po wpisaniu każdego znaku (dokładnie jednego), proszę wcisnąć klawisz enter.") << endl;
	string liczebnik[30] = { "pierwszy", "drugi", "trzeci", "czwarty", tr("piąty"), tr("szósty"), tr("siódmy"), tr("ósmy"),
							tr("dziewiąty"), tr("dziesiąty"), "jedenasty", "dwunasty", "trzynasty", "czternasty", 
							tr("piętnasty"), "szesnasty", "siedemnasty", "osiemnasty", tr("dziewiętnasty"), "dwudziesty" };
	for (int i = 20; i < 29; i++)
	{
		liczebnik[i] = liczebnik[19] + " " + liczebnik[i - 20];
	}
	liczebnik[29] = "trzydziesty";
	for (int i = 0; i < w; i++)
	{
		bool czy_ok;
		do
		{
			czy_ok = 1;
			cout << liczebnik[i] << " wiersz:" << endl;
			for (int j = 0; (j < k) && (czy_ok); j++)
			{
				cin >> plansza[i][j];
				cin.get();
				if ((plansza[i][j] != '$') && (plansza[i][j] != '0'))
				{
					cout << tr("Wpisał Pan zły znak!") << endl;
					cout << tr("Od początku!") << endl;
					czy_ok = 0;
					Sleep(1200);
				}
			}
			system("cls");
		} while (!czy_ok);
	}
	return plansza[w][k];
}

//losowe wpisanie danych do planszy
char wpis_danych_do_tab_losowo(char plansza[w][k])
{
	srand(time(0));
	int tab[w][k];
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < k; j++)
		{
			tab[i][j] = rand() % 10;
			if (tab[i][j] < 5)
			{
				plansza[i][j] = '$';
			}
			else
			{
				plansza[i][j] = '0';
			}
		}
	}
	return plansza[w][k];
}

//sprawdzanie, ile ma sąsiadów żywych
int ile_sąsiadów(char plansza[w][k], int i, int j)
{
	int ile = 0;

	//i, j
	if (i > 0 && plansza[i - 1][j] == '$')
		ile++;
	if (i < w - 1 && plansza[i + 1][j] == '$')
		ile++;
	if (j > 0 && plansza[i][j - 1] == '$')
		ile++;
	if (j < k - 1 && plansza[i][j + 1] == '$')
		ile++;

	if (i > 0 && j > 0 && plansza[i - 1][j - 1] == '$')
		ile++;
	if (i < w - 1 && j > 0 && plansza[i + 1][j - 1] == '$')
		ile++;
	if (i > 0 && j < k - 1 && plansza[i - 1][j + 1] == '$')
		ile++;
	if (i < w - 1 && j < k - 1 && plansza[i + 1][j + 1] == '$')
		ile++;

	return ile;
}



//wykonanie jednego kroku w symulacji
void jeden_krok()
{
	char następna_plansza[w][k];
	//zapisanie nowego rozmieszczenia komórek do nowej planszy
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < k; j++)
		{
				if (ile_sąsiadów(plansza, i, j) == 2)
				{
					if (plansza[i][j] == '$')
					{
						następna_plansza[i][j] = '$';
					}
					else
					{
						następna_plansza[i][j] = '0';
					}
				}
				if (ile_sąsiadów(plansza, i, j) == 3)
				{
					następna_plansza[i][j] = '$';
				}
				else
				{
					następna_plansza[i][j] = '0';
				}
		}
	}
	//zapisanie stanu nowej planszy do starej planszy
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < k; j++)
		{
			plansza[i][j] = następna_plansza[i][j];
		}
	}
}

int main()
{
	//krótkie wprowadzenie
	cout << tr("Witam Pana w moim programie!") << endl;
	cout << tr("Jest to symulacja gry w życie. Oto zasady:") << endl;
	cout << tr("Rzecz dzieje się na prostokątnej planszy o wymiarach 20x80 podzielonej na komórki.") << endl;
	cout << tr("Komórki mogą znajdować się w dwóch stanach: \n- żywym (symbolizowanym przez $), \n- martwym (symbolizowanym przez 0).") << endl;
	cout << tr("Dany jest pewien stan początkowy, w którym część komórek jest żywa, a część martwa.") << endl;
	cout << tr("W następnym kroku, niektóre komórki zmienią swój stan, a niektóre nie, według następujących zasad:") << endl;
	cout << tr("- jeżeli żywa komórka ma 2 lub 3 żywych sąsiadów, to zachowuje swoje życie,") << endl;
	cout << tr("- przy mniejszej liczbie żywych sąsiadów, umiera z samotności; przy większej - z zatłoczenia,") << endl;
	cout << tr("- jeśli martwa komórka ma dokładnie 3 żywych sąsiadów, to staje się żywa. ") << endl;
	cout << tr("To wszystko, jeżeli chodzi o zasady. Zaczynajmy naszą grę!") << endl;
	cout << tr("Proszę wcisnąć dowolny przycisk...") << endl;
	_getch();
	system("cls");

	//zapisanie stanu początkowego planszy
	bool czy_ok;
	cout << tr("Jeżeli chce Pan zapisać poczatkowy stan planszy samodzielnie - proszę wpisać 1.") << endl;
	cout << tr("Jeśli chce Pan aby zrobił to za Pana losowo komputer - proszę wpisać 0.") << endl;
	cout << tr("Wybór proszę zatwierdzić klawiszem enter!") << endl;
	do
	{
		int wybor;
		cin >> wybor;
		system("cls");
		cin.get();
		czy_ok = 0;
		if (wybor == 1)
		{
			//użytkownik wpisuje ręcznie
			plansza[w][k]= wpis_danych_do_tab(plansza);
		}
		else if (wybor == 0)
		{
			//automatyczny zapis tablicy
			plansza[w][k] = wpis_danych_do_tab_losowo(plansza);
		}
		else
		{
			czy_ok = 1;
			cout << tr("Wpisał Pan zły znak!") << endl;
			cout << tr("Proszę wpisać znak poprawny!!!") << endl;
		}
	} while (czy_ok);

	//wyświetlenie stanu początkowego
	cout << tr("Oto jak wygląda początkowy stan naszej planszy:") << endl;
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < k; j++)
		{
			cout << plansza[i][j];
		}
		cout << endl;
	}

	//wyświetlenie symulacji
	cout << tr("Czas rozpocząć symulację!") << endl;
	cout << tr("Jeżeli chce Pan, aby kolejne kroki symulacji wystepowały w równych odstępach czasu - proszę wpisać 1!") << endl;
	cout << tr("Jeśli chce Pan, aby kolejne kroki symulacji występowały po naciśnięciu klawisza enter - proszę wpisać 0!") << endl;
	bool wybor;
	cin >> wybor;
	system("cls");
	if (wybor)
	{
		int czas;
		cout << tr("Proszę podać, co ile milisekund ma występować następny krok.") << endl;
		cin >> czas;
		cin.get();
		int ile;
		cout << tr("Ile kroków symulacji ma zostać wykonanych?") << endl;
		cin >> ile;
		cin.get();
		for (int i = 0; i < ile; i++)
		{
			jeden_krok();
			cout << tr("Krok nr ") << i + 1 << "!" << endl;
			for (int j = 0; j < w; j++)
			{
				for (int l = 0; l < k; l++)
				{
					cout << plansza[j][l];
				}
				cout << endl;
			}
			Sleep(czas);
			system("cls");
		}
	}
	else
	{
		int ile;
		cout << tr("Ile kroków symulacji ma zostać wykonanych?") << endl;
		cin >> ile;
		cin.get();
		for (int i = 0; i < ile; i++)
		{
			jeden_krok();
			cout << tr("Krok nr ") << i + 1 << "!" << endl;
			for (int j = 0; j < w; j++)
			{
				for (int l = 0; l < k; l++)
				{
					cout << plansza[j][l];
				}
				cout << endl;
			}
			_getch();
			system("cls");
		}
	}
	cout << tr("Bardzo dziękuję za uwagę!") << endl;
	cout << tr("To już koniec naszej przygody z grą w życie!") << endl;
	cout << tr("Do następnego razu!") << endl;
	_getch();
    return 0;
}

