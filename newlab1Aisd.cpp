#include <cstdio>
#include <iostream>

FILE* OpenFile()
{
	FILE* file;
	fopen_s(&file, "file/surname.txt", "r+");
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
		str += ch;
	}
	std::cout << str.c_str() << std::endl;
	return str;
}

void SearchSurname(FILE* const& file)
{
	std::string str1 = ReadSurname(file);
	std::string str2 = "";
	while (!feof(file))
	{
		str2 = ReadSurname(file);
		if ((CompareStrings(str1, str2) > 0) && (str2 != "")  /*&& IsReplaced(surname[i])*/)
		{
			str1 = str2;
		}
	}
	std::cout << "Замена: |" << str1.c_str() << "|" << std::endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	FILE * ptrFile = OpenFile();
	if (ptrFile != NULL) 
	{
		//fseek(ptrFile, 0, SEEK_SET);
		long size = ftell(ptrFile); 
		SearchSurname(ptrFile);
		fclose(ptrFile);               
		std::cout << "Размер файла file.txt: " << size << " байт\n";
	}
	system("pause");
	return 0;
}
