#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int main()
{
    // 读取所有链接
    ifstream infile;
    infile.open("source.txt", ios::in);
    if (!infile.is_open())
    {
        cout << "读取文件失败" << endl;
        return 0;
    }
    char buf[1024];
    vector<string> urls;
    while (infile.getline(buf, sizeof(buf)))
    {
        urls.push_back(buf);
    }

    // 拼接链接生成代码文本
    string output = "<div class=\"gallery-page\">\n<div class=\"img-list\">\n";
    for (int i = 0; i < urls.size(); i++)
    {
        if (i % 2 == 0)
            output += "<div class=\"img-column\">\n";
        char temp[10000];
        sprintf(temp, "<div class=\"img-item\">\n<a href=\"%s\" data-fancybox=\"1\"><img src=\"%s\" /></a>\n</div>\n", urls[i].c_str(), urls[i].c_str());
        output += temp;
        if (i % 2 == 1)
            output += "</div>\n";
    }
    cout << output;

   // 将代码复制到剪贴板 
    HWND hWnd = NULL;
    OpenClipboard(hWnd);                            // 打开剪切板
    EmptyClipboard();                               // 清空剪切板
    HANDLE hHandle = GlobalAlloc(GMEM_FIXED, 10000); // 分配内存
    char *pData = (char *)GlobalLock(hHandle);      // 锁定内存，返回申请内存的首地址
    strcpy(pData, output.c_str());
    SetClipboardData(CF_TEXT, hHandle); // 设置剪切板数据
    GlobalUnlock(hHandle);              // 解除锁定
    CloseClipboard();                   // 关闭剪切板
    return 0;
}
