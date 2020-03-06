#include <iostream> //нужен для вывода строк "cout<<"
#include "conio.h" //нужен намеренно для "getche()" , а не "cin>>"
#include <fstream>
#include <string>
#include "windows.h" //библиотека audiere её требует
#include "audiere.h" //сама библиотека


using namespace std;
using namespace audiere; //определяем пространства имён для более короткой записи кода

int main()
{
	ifstream out;
	string str;

	setlocale(0, "Russian"); //пусть наша консоль говорит по-русски
	cout << "Простейшее воспроизведение звука" << endl;

	AudioDevicePtr device = OpenDevice(); //Для начала нужно открыть AudioDevice
	if (!device) {
		cout << "Ошибка открытия AudioDevice. Нажмите любую клавишу для выхода..";
		_getch();
		return 0; //выходим из программы
	}

	OutputStreamPtr sound = OpenSound(device, "track.mp3", false); //открываем наш звук
	if (!sound) {
		cout << "Ошибка открытия файла! Для выхода нажмите любую клавишу..";
		_getch();
		return 0;
	}

	sound->play(); //проигрываем наш звук
	out.open("dib.txt");
	if (out.is_open())
	{
		while (!out.eof())
		{
			out >> str;
			cout << str << endl;
			str = "";
		}
	}

	_getch(); //ждём нажатия любой клавиши прежде чем выйти из программы
}