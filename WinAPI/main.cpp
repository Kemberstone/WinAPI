#include<Windows.h>
#include"resource.h"

CONST CHAR g_cz_INVITE[] = "Введите имя пользователя"; 

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*MessageBox(NULL, "Hello WinAPI!", "MessageBox", MB_YESNOCANCEL | MB_ICONERROR | MB_DEFBUTTON3| MB_SYSTEMMODAL);*/
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG://выполняется 1 раз при запуске окна
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		//SetFocus(GetDlgItem(hwnd, IDC_EDIT_LOGIN));
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)g_cz_INVITE);
	}
			break;
	case WM_COMMAND://обрабатывает команды с клавиатуры и мыфши
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = "";
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, g_cz_INVITE)==0)
			{
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
			}
			if (HIWORD(wParam) == EN_KILLFOCUS && strcmp(sz_buffer, "") == 0)
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_cz_INVITE);
		}
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditLPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditLPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;
		case IDOK:
			MessageBox(NULL, "Была нажата кнопка 'OK'", "Info", MB_OK | MB_ICONINFORMATION);
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE://срабатывает при нажатии крестика 
		EndDialog(hwnd,0);
	}
	return FALSE;
}