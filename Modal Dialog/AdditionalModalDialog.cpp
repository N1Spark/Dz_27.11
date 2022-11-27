#include "AdditionalModalDialog.h"



CAdditionalModalDialog* CAdditionalModalDialog::ptr = NULL;

CAdditionalModalDialog::CAdditionalModalDialog(void)
{
	ptr = this;
}

CAdditionalModalDialog::CAdditionalModalDialog(LPCTSTR lpStr)
{
	ptr = this;
	_tcscpy(text, lpStr);
}

CAdditionalModalDialog::~CAdditionalModalDialog(void)
{

}

void CAdditionalModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CAdditionalModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hPay = GetDlgItem(hwnd, IDC_EDIT5);
	hHot = GetDlgItem(hwnd, IDC_HOTDOG);
	hBur = GetDlgItem(hwnd, IDC_BURGER);
	hCol = GetDlgItem(hwnd, IDC_COLA);
	hCof = GetDlgItem(hwnd, IDC_COFFE);
	hCPay = GetDlgItem(hwnd, IDC_KAFE);
	hList = GetDlgItem(hwnd, IDC_COMBO1);
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
	SendMessage(hList, CB_ADDSTRING, 0, LPARAM(TEXT("95")));
	SendMessage(hList, CB_ADDSTRING, 0, LPARAM(TEXT("93")));
	SendMessage(hList, CB_ADDSTRING, 0, LPARAM(TEXT("90")));
	hPrice1 = GetDlgItem(hwnd, IDC_EDIT3);
	hEdit = GetDlgItem(hwnd, IDC_EDIT1);
	hStatic = GetDlgItem(hwnd, IDC_STATIC1);
	SetWindowText(hStatic, text);
	return TRUE;
}


void CAdditionalModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	LRESULT count = SendDlgItemMessage(hwnd, IDC_RADIO2, BM_GETCHECK, 0, 0);
	LRESULT price = SendDlgItemMessage(hwnd, IDC_RADIO3, BM_GETCHECK, 0, 0);
	LRESULT check1 = SendDlgItemMessage(hwnd, IDC_CHECK1, BM_GETCHECK, 0, 0);
	LRESULT check2 = SendDlgItemMessage(hwnd, IDC_CHECK2, BM_GETCHECK, 0, 0);
	LRESULT check3 = SendDlgItemMessage(hwnd, IDC_CHECK3, BM_GETCHECK, 0, 0);
	LRESULT check4 = SendDlgItemMessage(hwnd, IDC_CHECK4, BM_GETCHECK, 0, 0);
	int index = SendMessage(hList, CB_GETCURSEL, 0, 0);
	if (id == IDC_COMBO1 && codeNotify == CBN_SELCHANGE)
	{
		switch (index)
		{
		case 2:
			SendMessage(hPrice1, WM_SETTEXT, 0, LPARAM(TEXT("50 грн/л")));
			break;
		case 1:
			SendMessage(hPrice1, WM_SETTEXT, 0, LPARAM(TEXT("45 грн/л")));
			break;
		case 0:
			SendMessage(hPrice1, WM_SETTEXT, 0, LPARAM(TEXT("40 грн/л")));
			break;
		}
	}
	if (id == IDC_EDIT1)
	{
		if (count == BST_CHECKED)
		{
			pay = 0;
			GetWindowText(hEdit1, edit, 20);
			pay = _tstoi(edit);
			if (index == 0)
				pay *= 40;
			else if (index == 1)
				pay *= 45;
			else if (index == 2)
				pay *= 50;
			wsprintf(edit, TEXT("%d"), pay);
			SendMessage(hPay, WM_SETTEXT, 0, LPARAM(edit));
		}
	}
	if (id == IDC_COFFE || id == IDC_COLA || id == IDC_HOTDOG || id == IDC_BURGER)
	{
		if (check1 == BST_CHECKED)
		{
			GetWindowText(hHot, edit, 20);
			hot_pay = _tstoi(edit) * 40;
			cafe_pay = hot_pay + coffe_pay + cola_pay + bur_pay;
			wsprintf(edit, TEXT("%d"), cafe_pay);
			SendMessage(hCPay, WM_SETTEXT, 0, LPARAM(edit));
		}
		if (check2 == BST_CHECKED)
		{
			GetWindowText(hBur, edit, 20);
			bur_pay = _tstoi(edit)* 45;
			cafe_pay = hot_pay + coffe_pay + cola_pay + bur_pay;
			wsprintf(edit, TEXT("%d"), cafe_pay);
			SendMessage(hCPay, WM_SETTEXT, 0, LPARAM(edit));
		}
		if (check3 == BST_CHECKED)
		{
			GetWindowText(hCol, edit, 20);
			cola_pay = _tstoi(edit) * 25;
			cafe_pay = hot_pay + coffe_pay + cola_pay + bur_pay;
			wsprintf(edit, TEXT("%d"), cafe_pay);
			SendMessage(hCPay, WM_SETTEXT, 0, LPARAM(edit));
		}
		if (check4 == BST_CHECKED)
		{
			GetWindowText(hCof, edit, 20);
			coffe_pay = _tstoi(edit) * 30;
			cafe_pay = hot_pay + coffe_pay + cola_pay + bur_pay;
			wsprintf(edit, TEXT("%d"), cafe_pay);
			SendMessage(hCPay, WM_SETTEXT, 0, LPARAM(edit));
		}
	}
	
	if (id == IDC_EDIT2)
	{
		if (price == BST_CHECKED)
		{

			pay = 0;
			GetWindowText(hEdit2, edit, 20);
			pay = _tstoi(edit);
			if (index == 0)
			{
				wsprintf(edit, TEXT("%d"), pay/40);
				SendMessage(hEdit1, WM_SETTEXT, 0, LPARAM(edit));
			}
			else if (index == 1)
			{
				wsprintf(edit, TEXT("%d"), pay/45);
				SendMessage(hEdit1, WM_SETTEXT, 0, LPARAM(edit));
			}
			else if (index == 2)
			{
				wsprintf(edit, TEXT("%d"), pay/50);
				SendMessage(hEdit1, WM_SETTEXT, 0, LPARAM(edit));
			}
			wsprintf(edit, TEXT("%d"), pay);
			SendMessage(hPay, WM_SETTEXT, 0, LPARAM(edit));
		}
	}
	if(id == IDOK)
	{
		EndDialog(hwnd, IDOK);
	}
	else if(id == IDCANCEL)
	{
		EndDialog(hwnd, IDCANCEL);
	}
}

BOOL CALLBACK CAdditionalModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
