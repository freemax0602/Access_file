#include "stdafx.h"
int count = 0;
char Username[500] = { 0 };
int cfileexists(const char * filename)
{
	FILE *file;
	if (file = fopen(filename, "r"))
	{
		fclose(file);
		return 1;
	}
	return 0;
}
void soft(char* Message)
{
	switch (*(DWORD*)Message)
	{
	case REGISTER_USER: //кейс с регистрацией
	{
		unsigned char digest[16] = { 0 };
		char FinalPath[MAX_PATH + 6] = { 0 };
		char TempBuf[MAX_PATH] = { 0 };
		char Password[MAX_PATH] = { 0 };
		if (strcmp(Username, "Admin") != 0)
		{
			printf("you have no rights \n");
			/*условие,благодоря которому регистрацию может проводить

			только заранее созданный администратор*/
			break;
		}
		printf("enter your username \n");
		/*Вводим логин и пароль сохраняя их в переменный
		типа char*/
		scanf("%s", TempBuf);
		printf("enter your password \n");
		scanf("%s", Password);

		sprintf(FinalPath, "users\\%s", TempBuf);
		if (cfileexists(FinalPath))
		{
			printf("file already exists \n");
			//проверка на уже сущетсвующий аккаунт
			break;
		}
		FILE *Login;
		Login = fopen(FinalPath, "w");
		memset(TempBuf, 0, MAX_PATH);
		/*Создаём файл с названием соответвующему имени
		пользователя,
		записываем в файл переменную с паролем*/
		fputs(Password, Login);
		fclose(Login);
		printf("registration successful \n"); //сообщение о успешной регистрации
			break;
	}

	case LOGIN: // кейc авторизации
	{
		unsigned char digest[16] = { 0 };
		char FinalPath[MAX_PATH + 6] = { 0 };
		char TempBuf[MAX_PATH] = { 0 };
		char Password[MAX_PATH] = { 0 };
		char FileData[100] = { 0 };
		printf("\nALLERT\nafter three incorrect attempts to enter your username and password, \nyour account will be blocked\n");
			printf("\nenter your username \n");
		scanf("%s", TempBuf);
		printf("enter your password \n");
		scanf("%s", Password);
		sprintf(FinalPath, "users\\%s", TempBuf);
		FILE *Login;
		Login = fopen(FinalPath, "r");
		if (Login == NULL)
		{
			printf("wrong username or password \n");
			break;
		}
		GetLastError();
		if (fread(FileData, 1, sizeof(FileData), Login))
		{
			printf("login successful \n");
		}
		else
		{
			printf("Wrong password \n");
		}
		if (strcmp(FileData, Password) != 0)
		{
			/*автоматическое блокирование ученой записи
			при превышении числа неудачных попыток входа
			Если счетчик будет равен 3-м,то файл с
		   аккаунтом удалиться*/
			count += 1;
			if (count == 1)
			{
				printf("You have two attempts left \n");
			}
			if (count == 2)
			{
				printf("ATTENTION\n");
				printf("you have one more try\n");
			}
			if (count == 3)
			{
				fclose(Login);
				remove(FinalPath);
				printf("your account is blocked");
			}
			break;
		}
		sprintf(Username, "%s", TempBuf);
		break;
	}
	/*case CREATE_FILE: //кейс создания файла
	{
		//алгоритм такой же,как при регистрации
		unsigned char digest[16] = { 0 };
		char FinalPath[MAX_PATH + 6] = { 0 };
		char TempBuf[MAX_PATH] = { 0 };
		char FileData[100] = { 0 };
		if (strcmp(Username, "Admin") != 0)
		{
			printf("you have no rights \n");
			break;
		}
		printf("Name the file \n");
		scanf("%s", TempBuf);
		sprintf(FinalPath, "files\\%s", TempBuf);
		if (cfileexists(FinalPath))
		{
			printf("file already exists \n");
			//проверка на уже сущетсвующий файл
			break;
		}
		FILE *CRT;
		CRT = fopen(FinalPath, "w");
		fclose(CRT);
		memset(TempBuf, 0, MAX_PATH);
		printf("file is created \n");
		break;
	}
	case DELETE_FILE: //кейс удаления файла
	{
		unsigned char digest[16] = { 0 };
		char FinalPath[MAX_PATH + 6] = { 0 };
		char TempBuf[MAX_PATH] = { 0 };
		char FileData[100] = { 0 };
		if (strcmp(Username, "User1") != 0)
		{
			printf("you have no rights \n");
			break;
		}
		printf("Name the file \n");
		scanf("%s", TempBuf);
		sprintf(FinalPath, "files\\%s", TempBuf);
		if (cfileexists(FinalPath) != 1)
		{
			printf("file already exists \n");
			//проверка на удаление несуществующего файла
			break;
		}
		remove(FinalPath); //функция remove, удаляет файл
		printf("file deleted \n");
		break;
	}*/
	case READ_FILE: //кейс чтения файла
	{
		unsigned char digest[16] = { 0 };
		char FinalPath[MAX_PATH + 6] = { 0 };
		char TempBuf[MAX_PATH] = { 0 };
		char FileData[100] = { 0 };
		if (strcmp(Username, "User2") != 0)
		{
			printf("you have no rights \n");
			break;
		}
		printf("Name the file \n");
		scanf("%s", TempBuf);
		sprintf(FinalPath, "files\\%s", TempBuf);
		if (cfileexists(FinalPath) != 1)
		{
			printf("file already exists \n");
			//проверка на чтение несуществующего файла
			break;
		}
		FILE *File;
		File = fopen(FinalPath, "r");
		while (fgets(FinalPath, 50, File) != NULL)
			printf("%s", FinalPath);
		break;
	}
	case RECORD_FILE: //кейс записи в файл файла
	{
		unsigned char digest[16] = { 0 };
		char FinalPath[MAX_PATH + 6] = { 0 };
		char TempBuf[MAX_PATH] = { 0 };
		char TextFile[MAX_PATH] = { 0 };
		char FileData[100] = { 0 };
		if (strcmp(Username, "User3") != 0)
		{
			printf("you have no rights \n");
			break;
		}
		printf("Name the file \n");
		scanf("%s", TempBuf);
		printf("Input text \n");
		scanf("%s", TextFile);
		sprintf(FinalPath, "files\\%s", TempBuf);
		sprintf(FinalPath, "files\\%s", TempBuf);
		if (cfileexists(FinalPath) != 1)
		{
			printf("file already exists \n");
			//проверка на чтение несуществующего файла
			break;
		}
		FILE *File;
		File = fopen(FinalPath, "w");
		fprintf(File, "%s", TextFile);
		fclose(File);
		break;
	}
	case COPY_FILE: //кейс копирования
	{
		if (strcmp(Username, "User4") != 0)
		{
			printf("you have no rights \n");
			break;
		}
		unsigned char digest[16] = { 0 };
		char FinalPath[MAX_PATH + 6] = { 0 };
		char TempBuf[MAX_PATH] = { 0 };
		char FilePath[MAX_PATH + 6] = { 0 };
		char TextFile[MAX_PATH] = { 0 };
		char FileName[MAX_PATH] = { 0 };
		char FileData[MAX_PATH] = { 0 };
		printf("Name the file \n");
		scanf("%s", TempBuf);
		sprintf(FinalPath, "files\\%s", TempBuf);
		if (cfileexists(FinalPath) != 1)
		{
			printf("file already exists \n");
			//проверка на копирование несуществующего файла
			break;
		}
		FILE *File;
		File = fopen(FinalPath, "r");
		while (fscanf(File, "%s", TextFile) == 1)
			printf("enter the name of the copied file \n");
		scanf("%s", FileName);
		sprintf(FilePath, "files2\\%s", FileName);
		FILE *File_new;
		File_new = fopen(FilePath, "w");
		fprintf(File_new, "%s", TextFile);
		fclose(File_new);
		printf("the file was copied \n");
		break;
	}
	case MOVE_FILE: //кейс перемещения
	{
		if (strcmp(Username, "User5") != 0)
		{
			printf("you have no rights \n");
			break;
		}
		unsigned char digest[16] = { 0 };
		char FinalPath[MAX_PATH + 6] = { 0 };
		char TempBuf[MAX_PATH] = { 0 };
		char FilePath[MAX_PATH + 6] = { 0 };
		char TextFile[MAX_PATH] = { 0 };
		char FileName[MAX_PATH] = { 0 };
		char FileData[MAX_PATH] = { 0 };
		printf("Name the file \n");
		scanf("%s", TempBuf);
		sprintf(FinalPath, "files\\%s", TempBuf);
		if (cfileexists(FinalPath) != 1)
		{
			printf("file already exists \n");
			//проверка на перенос несуществующего файла
			break;
		}
		FILE *File;
		File = fopen(FinalPath, "r");
		while (fscanf(File, "%s", TextFile) == 1)
			fclose(File);
		remove(FinalPath);
		printf("enter the name of the copied file \n");
		scanf("%s", FileName);
		sprintf(FilePath, "files2\\%s", FileName);
		FILE *File_new;
		File_new = fopen(FilePath, "w");
		fprintf(File_new, "%s", TextFile);
		fclose(File_new);
		printf("the file has been moved \n");
		break;
	}
	case BLOCK_USER: //админ может заблокировать аккаунт
	{
		if (strcmp(Username, "Admin") != 0)
		{
			printf("you have no rights \n");
			break;
		}
		unsigned char digest[16] = { 0 };
		char FinalPath[MAX_PATH + 6] = { 0 };
		char TempBuf[MAX_PATH] = { 0 };
		char FilePath[MAX_PATH + 6] = { 0 };
		char TextFile[MAX_PATH] = { 0 };
		char FileName[MAX_PATH] = { 0 };
		char FileData[MAX_PATH] = { 0 };
		printf("Name the user \n");
		scanf("%s", TempBuf);
		sprintf(FinalPath, "users\\%s", TempBuf);
		if (cfileexists(FinalPath) != 1)
		{
			printf("account already exists \n");
			//проверка на блокировку несущетсвующего аккаунта
			break;
		}
		FILE *File;
		File = fopen(FinalPath, "r");
		while (fscanf(File, "%s", TextFile) == 1)
			fclose(File);
		remove(FinalPath);
		printf("enter the name of the copied file \n");
		scanf("%s", FileName);
		sprintf(FilePath, "blocked_users\\%s", FileName);
		FILE *File_new;
		File_new = fopen(FilePath, "w");
		fprintf(File_new, "%s", TextFile);
		fclose(File_new);
		printf("account blocked \n");
		break;
	}
	case UNLOCK_USER: //админ может разблокировать аккаунт
	{
		if (strcmp(Username, "Admin") != 0)
		{
			printf("you have no rights \n");
			break;
		}
		unsigned char digest[16] = { 0 };
		char FinalPath[MAX_PATH + 6] = { 0 };
		char TempBuf[MAX_PATH] = { 0 };
		char FilePath[MAX_PATH + 6] = { 0 };
		char TextFile[MAX_PATH] = { 0 };
		char FileName[MAX_PATH] = { 0 };
		char FileData[MAX_PATH] = { 0 };
		printf("Name the user \n");
		scanf("%s", TempBuf);
		sprintf(FinalPath, "blocked_users\\%s", TempBuf);
		if (cfileexists(FinalPath) != 1)
		{
			printf("account already exists \n");
			//проверка на разблокировку несущетсвующего аккаунта
			break;
		}
		FILE *File;
		File = fopen(FinalPath, "r");
		while (fscanf(File, "%s", TextFile) == 1)
			fclose(File);
		remove(FinalPath);
		printf("enter the name of the copied file \n");
		scanf("%s", FileName);
		sprintf(FilePath, "users\\%s", FileName);
		FILE *File_new;
		File_new = fopen(FilePath, "w");
		fprintf(File_new, "%s", TextFile);
		fclose(File_new);
		printf("account unblocked \n");
		break;
	}
	default:
	{
		int i = 0;
		break;
	}
	}
}
int main()
{
	char Messege[100] = { 0 };
	while (1)
	{
		printf("\n\n");
		printf("type the command \n");
		scanf("%s", Messege);
		soft(Messege);
	}
}