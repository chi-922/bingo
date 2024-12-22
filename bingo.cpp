// bingo.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#define _CRT_NONSTDC_NO_WARNINGS    // 비표준 함수를 사용했을 때 에러 방지
#include <iostream>
#include <algorithm>
#include <vector>
#include <Windows.h>   // 콘솔 형태 맞추기
#include <conio.h>   // Visual Studio에서만 사용할 수 있고 리눅스나 OS X에서는 사용할 수 없습니다.
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()

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


void startScreen() {
    cout << "\n\n\n\n";
    cout << "\t\t"; cout << "@@@@@@@@@@@    @@@@@@@@@@@@    @@@@         @@      @@@@@@@@        @@@@@@@@    \n";
    cout << "\t\t"; cout << "@@        @@        @@         @@ @@        @@    @@              @@        @@  \n";
    cout << "\t\t"; cout << "@@        @@        @@         @@   @@      @@   @@              @@          @@ \n";
    cout << "\t\t"; cout << "@@@@@@@@@@@         @@         @@     @@    @@   @@              @@          @@ \n";
    cout << "\t\t"; cout << "@@        @@        @@         @@       @@  @@   @@     @@@@@    @@          @@ \n";
    cout << "\t\t"; cout << "@@        @@        @@         @@        @@ @@    @@        @@    @@        @@  \n";
    cout << "\t\t"; cout << "@@@@@@@@@@@    @@@@@@@@@@@@    @@         @@@@     @@@@@@@@@@       @@@@@@@@ \n\n\n\n\n";
    cout << "\t\t\t"; cout << "              게임을 시작하려면 아무키나 누르세요.\n\n\n\n\n\n\n";

    getch(); // 아무키 입력 기다림
    system("cls"); // 콘솔 창 clear
}


// 사용자가 빙고에 숫자 집어넣을 때 중복 탐색
bool isDuplicate(const vector<vector<int>>* userBingo, int* input) {
    for (const auto& row : *userBingo) {
        for (const auto& num : row) {
            if (num == *input) {
                return true;
            }
        }
    }
    return false;
}


// 컴퓨터의 빙고판 생성
void generateBingoBoard(vector<vector<int>>& bingoBoard) {
    srand(static_cast<unsigned>(time(0)));  // 랜덤 시드 초기화

    int count = 0;
    while (count < 25) {  // 5x5 빙고판을 채울 때까지 반복
        int num = rand() % 30 + 1;  // 1~30 사이의 랜덤 숫자 생성

        if (!isDuplicate(&bingoBoard, &num)) {
            bingoBoard[count / 5][count % 5] = num;  // 배열에 숫자 저장
            count++;
        }
    }
}

int main() {
    SetConsole();

    // 시작화면
    startScreen();

    // 본 게임 5 * 5
    const int SIZE = 5;
    vector<vector<int>> userBingo(SIZE, vector<int>(SIZE, 0)); // 2차원 벡터 초기화;
    int input; // 사용자의 입력값
    int count = 0; // 현재까지 입력된 숫자의 개수

    while (count < SIZE * SIZE) {
        // 잘 들어왔는지 확인용
        for (int i = 0; i < SIZE; i++)
        {
            cout << "----------------" << endl;
            for (int j = 0; j < SIZE; j++)
            {
                cout << "|" << userBingo[i][j];
                if (j == SIZE - 1) {
                    cout << "|" << endl;
                }
            }
            if (i == SIZE - 1) {
                cout << "----------------" << endl;
            }
        }
        
        cout << "\n\n\n";

        // userBingo에 수 넣기
        cout << "5x5 빙고 게임을 시작합니다! (1 ~ 30 사이의 숫자 입력)" << endl;
        cout << "빙고 " << count + 1 << "번째 칸 채우는 중  :  ";
        cin >> input;

        if (input < 1 || input > 30) {
            cout << "숫자 범위를 벗어났습니다. 다시 입력해주세요.";
            Sleep(1000);   // windows에 api 를 이용
            system("cls");
            continue;
        }
        else if (isDuplicate(&userBingo, &input)) {
            cout << "이미 입력된 숫자입니다. 다른 숫자를 입력해주세요." << endl;
            Sleep(1000);
            system("cls");
            continue;

        }

         // 입력값을 2차원 벡터에 저장
        userBingo[count / SIZE][count % SIZE] = input;
        count++; // 입력 개수 증가
        system("cls");
    }

    // 컴퓨터의 빙고 저장
    vector<vector<int>> computerBingo(SIZE, vector<int>(SIZE, 0)); // 2차원 벡터 초기화;
    generateBingoBoard(computerBingo);   // 컴퓨터 빙고판 채우기

    // 빙고판 보여주는 거 함수로 빼기 필요함
    // 유저 빙고 보여줌
    cout << " 내 빙고판\n" << endl;
    for (int i = 0; i < SIZE; i++)
    {
        cout << "----------------" << endl;
        for (int j = 0; j < SIZE; j++)
        {
            cout << "|" << userBingo[i][j];
            if (j == SIZE - 1) {
                cout << "|" << endl;
            }
        }
        if (i == SIZE - 1) {
            cout << "----------------" << endl;
        }
    }
    
    cout << "\n\n" << endl;
    // 컴퓨터 빙고 보여줌 (지금은 숫자 다 보이지만 추후 안 보이게 설정할 예정)
    cout << " 컴퓨터 빙고판\n" << endl;
    for (int i = 0; i < SIZE; i++)
    {
        cout << "----------------" << endl;
        for (int j = 0; j < SIZE; j++)
        {
            cout << "|" << computerBingo[i][j];
            if (j == SIZE - 1) {
                cout << "|" << endl;
            }
        }
        if (i == SIZE - 1) {
            cout << "----------------" << endl;
        }
    }

    cout << "Hello, World! This is a customized console window.\n";
    return 0;
}