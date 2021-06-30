#include <windows.h>
#include <sstream>
#include <iostream>
#include "graphics.h"
#include "data.h"

int main()
{

    HANDLE hMapFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, false, "KindleEDMFile");
    LPCTSTR pBuf = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, MAX_PATH);

    Graphics graphics;
    Data data;

    graphics.init();

    while (!graphics.should_close())    
    {
        pBuf = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, MAX_PATH);

        // Convert LPCTSTR to std::string
        std::stringstream ss;
        ss << pBuf;
        std::string data_str = ss.str();

        data.parse_data(data_str);

        graphics.draw(data);
        
    }

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile); 

    graphics.close();       
    
    return 0;
}