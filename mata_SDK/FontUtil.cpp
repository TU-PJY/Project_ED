#include "FontUtil.h"
#include "StringUtil.h"
#include "Scene.h"

FontUtil fontUtil;

bool FontUtil::Load(const std::string& FontFilePath, bool LoadInThread) {
    std::wstring Path = stringUtil.Wstring(FontFilePath);
    DWORD NumFonts{};

    NumFonts = AddFontResourceEx(Path.c_str(), FR_PRIVATE, 0);

    if (NumFonts == 0) {
        scene.ErrorScreen(ERROR_TYPE_FONT_LOAD, FontFilePath);
        return false;
    }
    else
        std::cout << "Loaded Font " << FontFilePath << std::endl;

    if(LoadInThread)
        PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
    else
        SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);

    return true;
}

void FontUtil::LoadUserFont() {
    int TotalSize = sizeof(FONT_PATH);
    int ElementSize = sizeof(FONT_PATH[0]);
    int Length = TotalSize / ElementSize;
    for (int i = 0; i < Length; ++i)
        fontUtil.Load(FONT_PATH[i], true);
}
