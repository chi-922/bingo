// bingo.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <Windows.h>   // 콘솔 형태 맞추기
using namespace std;

void SetConsole() {
    // 콘솔 제목 설정
    SetConsoleTitle(TEXT("ImChaeHyeon Bingo Game"));

    // 콘솔 핸들 가져오기
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 콘솔 배경색 및 글자색 설정 (배경: 하얀색, 글자: 검정색)
    SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    system("cls"); // 변경된 배경색을 적용하려면 화면 초기화가 필요

    // 콘솔 버퍼 크기 설정
    COORD bufferSize = {20, 20};  // 열, 행
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // 콘솔 창 크기 설정
    SMALL_RECT windowSize = {0, 0, 100, 50};  // 좌상단 (0,0)에서 우하단
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

int main() {
    SetConsole();
    cout << "Hello, World! This is a customized console window.\n";
    return 0;
}