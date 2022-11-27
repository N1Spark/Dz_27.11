#include "MainModalDialog.h"
#include "AdditionalModalDialog.h"

CMainModalDialog* CMainModalDialog::ptr = NULL;

CMainModalDialog::CMainModalDialog(void)
{
	ptr = this;
}

CMainModalDialog::~CMainModalDialog(void)
{

}

void CMainModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hStatic1 = GetDlgItem(hwnd, IDC_STATIC1);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
	hStatic2 = GetDlgItem(hwnd, IDC_STATIC2);
	hAllPrice = GetDlgItem(hwnd, IDC_ALL_PRICE);
	SetWindowText(hEdit1, TEXT("�������� ������ ��������������� �������!"));
	SetWindowText(hEdit2, TEXT("�������� ������ ��������������� �������!"));
	return TRUE;
}


void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		CAdditionalModalDialog dlg;
		TCHAR buffer[200];
		GetWindowText(hEdit1, buffer, 200);
		_tcscpy(dlg.text, buffer);
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CAdditionalModalDialog::DlgProc);
		if(result == IDOK)
		{
			SetWindowText(hStatic1, dlg.text);
		}
		allprice += dlg.pay;
		wsprintf(dlg.edit, TEXT("%d"), allprice);
		SendMessage(hAllPrice, WM_SETTEXT, 0, LPARAM(dlg.edit));
	}
	else if(id == IDC_BUTTON2)
	{
		TCHAR buffer[200];
		GetWindowText(hEdit2, buffer, 200);
		// �������� ������ ����� ����������� ������ CAdditionalModalDialog ��������������� �������
		CAdditionalModalDialog dlg(buffer);
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hwnd, CAdditionalModalDialog::DlgProc);
		if(result == IDOK)
		{
			SetWindowText(hStatic2, dlg.text);
		}
		allprice += dlg.cafe_pay;
		wsprintf(dlg.edit, TEXT("%d"), allprice);
		SendMessage(hAllPrice, WM_SETTEXT, 0, LPARAM(dlg.edit));
	}
}

BOOL CALLBACK CMainModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
