#include <iostream>  // cin cout
#include <iomanip>   // cout format
#include <windows.h> // windows API
#include <string>    // string

using namespace std;

// 顯示 / 影藏 Console 光標
void ShowConsoleCursor(bool showFlag) {
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(out, &cursorInfo);
  if (cursorInfo.bVisible != showFlag) {
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
  }
}

#define PROGRESSBAR_WIDTH 50
#define PROGRESSBAR_MAX 100
#define PROGRESSBAR_MIN 0

int8_t loaderIndex = 0;
const string LOADER[] = {"-", "\\", "|", "/"};

void PrintProgress(int value) {
  ShowConsoleCursor(false);
  int progressCount =
      value / ((PROGRESSBAR_MAX - PROGRESSBAR_MAX) / PROGRESSBAR_WIDTH);

  // "\r" 能讓光標移到最前面，讓之後 cout 出來的字能覆蓋過去
  cout << "\r[ Progress ] : [" << setw(progressCount) << setfill('=')
       << ((value != PROGRESSBAR_MAX) ? ">" : "");
  cout << setw(PROGRESSBAR_WIDTH - progressCount) << setfill(' ') << "";

  cout << "] " << setw(2) << setfill(' ') << value << " % ";

  if (value == PROGRESSBAR_MAX) {
    cout << "Done!" << endl;
    ShowConsoleCursor(true);
  } else {
    cout << LOADER[loaderIndex++] << " ";
    if (loaderIndex > 3) {
      loaderIndex = 0;
    }
  }
  cout.flush();
}

int main(void) {
  for (int n = 0; n <= 100; n++) {
    PrintProgress(n);
    Sleep(100);
  }
  return 0;
}