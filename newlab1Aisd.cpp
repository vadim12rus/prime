#include <cstdio>
#include <iostream>

struct Surname
{
	std::string surname;
	int startBytes;
	int amountChar;
};

FILE* OpenFile()
{
	FILE* file;
	fopen_s(&file, "file/surname.txt", "r+b");
	return file;
}

int CompareStrings(std::string const& a, std::string const& b)
{
	return (strcmp(a.c_str(), b.c_str()));
}

std::string ReadSurname(FILE* const& file)
{
	std::string str = "";
	char ch;
	while (((ch = getc(file)) != '\n') && !feof(file))
	{
		if (isalpha(ch))
		{
			str += ch;
		}

	}
	return str;
}

Surname SearchSurname(FILE* const& file)
{
	std::string str1 = ReadSurname(file);
	std::string str2 = "";
	long position = ftell(file);;

	while (!feof(file))
	{
		str2 = ReadSurname(file);
		if ((CompareStrings(str1, str2) > 0) && (str2 != "") || ((str1 == "") && (str2 != "")) /*&& IsReplaced(surname[i])*/)
		{
			str1 = str2;
			position = ftell(file);
		}
	}
	Surname surname;
	surname.surname = str1;
	surname.amountChar = str1.length();
	surname.startBytes = position - str1.length();
	return surname;
}

int main()
{
	setlocale(LC_ALL, "rus");
	FILE * ptrFile = OpenFile();
	if (ptrFile != NULL)
	{
		//fseek(ptrFile, 0, SEEK_SET);
		long size = ftell(ptrFile);
		Surname surname = SearchSurname(ptrFile);
		std::cout << "Word: " << surname.surname.c_str() << std::endl;
		std::cout << "startBytes: " << surname.startBytes << std::endl;
		std::cout << "amountChar: " << surname.amountChar << std::endl;
		fclose(ptrFile);
	}
	system("pause");
	return 0;
}
