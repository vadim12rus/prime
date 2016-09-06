#include <cstdio>
#include <iostream>

static const char FILE_NAME[] = "file/surname.txt";
static const char REPLACEMENT = '*';

struct Surname
{
	std::string surname;
	long startBytes;
	int amountChar;
};

FILE* OpenFile()
{
	FILE* file;
	fopen_s(&file, FILE_NAME, "r+b");
	return file;
}

int CompareStrings(std::string const& a, std::string const& b)
{
	return (strcmp(a.c_str(), b.c_str()));
}

std::string ReadSurname(FILE* const& file, long & position)
{
	std::string str = "";
	char ch;
	while (((ch = getc(file)) != '\n') && (ch != '\r') &&  (ch != EOF))
	{
		position = ftell(file);
		str += ch;
	}
	return str;
}

Surname SearchSurname(FILE* & file)
{
	long position = ftell(file);
	std::string str1 = ReadSurname(file, position);
	std::string str2 = "";
	while (!feof(file))
	{
		str2 = ReadSurname(file, position);
		if ((CompareStrings(str1, str2) > 0) && (str2 != "") || ((str1 == "") && (str2 != "")) /*&& IsReplaced(surname[i])*/)
		{
			str1 = str2;
		}
	}
	Surname surname;
	surname.surname = str1;
	surname.amountChar = str1.length();
	surname.startBytes = position - str1.length();
	return surname;
}

std::string GetStringReplacement(Surname const& surname)
{
	std::string buf = "";
	for (int i = 0; i != surname.amountChar; i++)
	{
		buf += REPLACEMENT;
	}
	return buf;
}

void ReplaceWord(FILE* & file, Surname const& surname)
{
	std::string replacement = GetStringReplacement(surname);
	fseek(file, surname.startBytes, SEEK_SET);
	fwrite(replacement.c_str(), surname.amountChar, 1, file);
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
		if (surname.amountChar > 1)
		{
			ReplaceWord(ptrFile, surname);
		}
		std::cout << "Word: " << surname.surname.c_str() << std::endl;
		std::cout << "startBytes: " << surname.startBytes << std::endl;
		std::cout << "amountChar: " << surname.amountChar << std::endl;
		fclose(ptrFile);
	}
	system("pause");
	return 0;
}
