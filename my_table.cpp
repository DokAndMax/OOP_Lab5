#include "my_table.h"
#include "my_table.rh"
#include <commctrl.h>

static MyTable* pdlg = nullptr;
static INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND MyTable::Run(HWND hWnd) {
    if (!IsWindow(hWndDialog))
    {
        hWndDialog = CreateDialogParam(
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            MAKEINTRESOURCE(IDD_DIALOG1),
            hWnd,
            (DLGPROC)DlgProc,
            (LPARAM)this);

        HWND lvhWnd = GetDlgItem(hWndDialog, IDC_LIST1);

        ListView_SetExtendedListViewStyle(lvhWnd, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |
            LVS_EX_AUTOSIZECOLUMNS);

        LPWSTR columnText[]{
            (LPWSTR)L"Shape",
            (LPWSTR)L"x1",
            (LPWSTR)L"y1",
            (LPWSTR)L"x2",
            (LPWSTR)L"y2",
        };
        INT columnCount = sizeof(columnText) / sizeof(columnText[0]);

        RECT rect;
        INT width = 0;
        if (GetClientRect(lvhWnd, &rect))
            width = rect.right - rect.left;

        LVCOLUMN lvc{};
        lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
        lvc.fmt = LVCFMT_LEFT | LVCFMT_FIXED_WIDTH | LVCFMT_FIXED_RATIO;
        lvc.cx = width / columnCount;

        // Add the columns.
        for (int i = 0; i < columnCount; i++)
        {
            lvc.pszText = columnText[i];

            if (ListView_InsertColumn(lvhWnd, i + 1, &lvc) == -1)
                return FALSE;

            if (i < (width % columnCount))
                ListView_SetColumnWidth(lvhWnd, i, lvc.cx + 1);
        }
        return nullptr;
    }
    return (HWND)hWndDialog;
}

void MyTable::Show(HWND)
{
    if (!IsWindowVisible(hWndDialog))
        ShowWindow(hWndDialog, SW_SHOW);
    else
        ShowWindow(hWndDialog, SW_HIDE);
}

void MyTable::Save(HWND)
{
    FILE* fout;
    fopen_s(&fout, "myfile.txt", "wt");
    if (fout)
    {
        for (auto& item : items)
        {
            fwprintf(fout, L"%s\t%d\t%d\t%d\t%d\n", item.name.c_str(), item.shape.left,
                item.shape.top, item.shape.right, item.shape.bottom);
        }
        fclose(fout);
    }

}

void MyTable::Add(std::wstring name, RECT shape) {
    HWND lvhWnd = GetDlgItem(hWndDialog, IDC_LIST1);

    LVITEM lvI{};
    lvI.mask = LVIF_TEXT;
    lvI.iItem = ListView_GetItemCount(lvhWnd);
    lvI.pszText = (LPWSTR)name.c_str();

    if (ListView_InsertItem(lvhWnd, &lvI) == -1)
        return;
    WCHAR buffer[64];
    wsprintf(buffer, L"%d", shape.left);
    ListView_SetItemText(lvhWnd, lvI.iItem, 1, buffer);
    wsprintf(buffer, L"%d", shape.top);
    ListView_SetItemText(lvhWnd, lvI.iItem, 2, buffer);
    wsprintf(buffer, L"%d", shape.right);
    ListView_SetItemText(lvhWnd, lvI.iItem, 3, buffer);
    wsprintf(buffer, L"%d", shape.bottom);
    ListView_SetItemText(lvhWnd, lvI.iItem, 4, buffer);
    items.push_back(lvItem{ name, shape });
}

void MyTable::ItemActivated(std::function<void(INT)> func)
{
    itemActivatedListeners.push_back(func);
}

void MyTable::ItemDeleted(std::function<void(INT)> func)
{
    itemDeletedListeners.push_back(func);
}

void MyTable::OnItemActivate(HWND hDlg, LPARAM lParam)
{
    LPNMITEMACTIVATE item = (LPNMITEMACTIVATE)lParam;

    for (auto& func : itemActivatedListeners)
        func(item->iItem);
}

void MyTable::OnItemDeleted(HWND hDlg)
{
    HWND lvhWnd = GetDlgItem(hWndDialog, IDC_LIST1);
    int iPos = ListView_GetNextItem(lvhWnd, -1, LVNI_SELECTED);

    if (iPos == -1) return;

    ListView_DeleteItem(lvhWnd, iPos);
    items.erase(items.begin() + iPos);

    for (auto& func : itemDeletedListeners)
        func(iPos);
}

static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        pdlg = (MyTable*)lParam;
        break;
    case WM_NOTIFY:
    {
        LPNMHDR pnmh = (LPNMHDR)lParam;
        if (pnmh->idFrom == IDC_LIST1)
        {
            switch (pnmh->code)
            {
            case NM_CLICK:
                pdlg->OnItemActivate(hDlg, lParam);
                break;
            }
        }
        break;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);

        // Parse the menu selections:
        switch (wmId)
        {
        case IDCANCEL:
            ShowWindow(hDlg, SW_HIDE);
            /*DestroyWindow(hDlg);*/
            return (INT_PTR)TRUE;
        case IDDELETE:
            pdlg->OnItemDeleted(hDlg);
            break;
        }
        break;
    }
    }
    return (INT_PTR)FALSE;
}