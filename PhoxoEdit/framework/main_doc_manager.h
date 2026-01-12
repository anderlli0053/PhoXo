#pragma once

class CMainDocManager : public CDocManager
{
public:
    BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate) override
    {
        unique_ptr<CFileDialog>   dlg;
        if (bOpenFileDialog)
        {
            dlg = make_unique<PhoxoImageOpenDialog>(AfxGetMainWnd(), LanguageText::Get(L"FILE", L"open_type"));
        }
        else
        {
            dlg = make_unique<PhoxoImageSaveDialog>(AfxGetMainWnd(), fileName);
        }

        auto   result = dlg->DoModal();
        if (result == IDOK)
        {
            fileName = dlg->GetPathName();
            return TRUE;
        }
        return FALSE;
    }
};
