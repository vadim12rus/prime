#include <cstdio>
#include <iostream>

static const char FILE_NAME[] = "file/surname.txt";
static const char REPLACEMENT = '*';

struct Surname
{
	std::string word;
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

std::string ReadSurname(FILE* const& file, long & positionCurr)
{
	std::string str = "";
	char ch;
	while (((ch = getc(file)) != '\n') && (ch != '\r') &&  (ch != EOF))
	{
		str += ch;
		positionCurr = ftell(file);
	}
	return str;
}

void SaveInStructure(Surname & surname, std::string const& str1, long const& position)
{
	surname.word = str1;
	surname.amountChar = str1.length();
	surname.startBytes = position - str1.length();
}

Surname SearchSurname(FILE* & file)
{
	long positionCurr;
	std::string str1 = ReadSurname(file, positionCurr);
	std::string str2 = "";
	long positionMaxSurname = positionCurr;
	while (!feof(file))
	{
		str2 = ReadSurname(file, positionCurr);
		if ((CompareStrings(str1, str2) > 0) && (str2 != "") || ((str1 == "") && (str2 != "")))
		{
			str1 = str2;
			positionMaxSurname = positionCurr;
		}
	}
	Surname surname;
	SaveInStructure(surname, str1, positionMaxSurname);
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

void OutputDataSurname(Surname const& surname)
{
	std::cout << "Word: " << surname.word.c_str() << std::endl;
	std::cout << "startBytes: " << surname.startBytes << std::endl;
	std::cout << "amountChar: " << surname.amountChar << std::endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	FILE * ptrFile = OpenFile();
	if (ptrFile != NULL)
	{
		Surname surname = SearchSurname(ptrFile);
		if (surname.amountChar > 1)
		{
			ReplaceWord(ptrFile, surname);
		}
		OutputDataSurname(surname);
		fclose(ptrFile);
	}
	else
	{
		std::cout << "An error with the file!!!" << std::endl;
		return 1;
	}
	system("pause");
	return 0;
}
