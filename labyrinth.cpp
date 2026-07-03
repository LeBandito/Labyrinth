/*Создать генератор лабиринтов - любого размера.
пример:*/

#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>

void CreateShape(int& vidth, int& height, const int& vidth_min, const int& vidth_max, const int& height_min, const int& height_max) {
    vidth = vidth_min + std::rand() % (vidth_max - vidth_min + 1);
    height = height_min + std::rand() % (height_max - height_min + 1);
    std::cout << vidth_min << " <= vidth <= " << vidth_max << " :\t" << vidth << std::endl;
    std::cout << height_min << " <= height <= " << height_max << " :\t" << height << std::endl;
}

void ShowLabirint(const std::vector<std::vector<char>>& labirint) {
    for (int i = 0; i < labirint.size(); ++i) {
        for (int j = 0; j < labirint[i].size(); ++j) 
            std::cout << labirint[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Create_X_Y(const int& vidth, const int& height, const int& need, int& need_x, int& need_y) {
    if (need < vidth) {
        need_x = need - 1;
        need_y = 0;
    } else if (need < vidth + height) {
        need_x = vidth - 1;
        need_y = need - vidth - 1;
    } else if (need < vidth + height + vidth) {
        need_x = vidth - (need - (vidth + height));
        need_y = height - 1;
    } else if (need < vidth + height + vidth + height) {
        need_x = 0;
        need_y = (vidth + height + vidth + height) - need - 1;
    }
}

void CreateStartFinish(const int& vidth, const int& height, int& start_x, int& start_y, int& finish_x, int& finish_y) {
    int start(0);
    do {
        // start = std::rand() % (2 * (vidth + height));
        // Будем двигаться только по чётным; P.S: + 1, чтобы не было 0 сразу
        start = 1 + std::rand() % (vidth + height) * 2; 
    } while ((start == vidth) || (start == vidth + height) || (start == vidth + height + vidth));
    
    int finish(0);
    do {
        // finish = std::rand() % (2 * (vidth + height));
        // Будем двигаться только по чётным; P.S: + 1, чтобы не было 0 сразу
        finish = 1 + std::rand() % (vidth + height) * 2; 
    } while ((finish == vidth) || (finish == vidth + height) || (finish == vidth + height + vidth));
     
    std::cout << "start = " << start;
    Create_X_Y(vidth, height, start, start_x, start_y);
    std::cout << " -> (" << start_x + 1<< "; " << start_y + 1<< ")" << std::endl;
    
    std::cout << "finish = " << finish;
    Create_X_Y(vidth, height, finish, finish_x, finish_y);
    std::cout << " -> (" << finish_x + 1<< "; " << finish_y + 1 << ")" << std::endl;
}

void StaticRoutes(std::vector<std::vector<char>>& labirint, const int& vidth, const int& height, 
    const int& Win_x, const int& Win_y, const int& need_x, const int& need_y) {
    // Win - точка, в которую идем. need - точка, из которой идем
    // По горизонтали
    if ((need_x == 0) || (need_x == vidth - 1)) {
        labirint[need_y][Win_x] = ' ';
        // До поворота
        for (int i = std::min(Win_x, need_x) + 1; i < std::max(Win_x, need_x); ++i)
            labirint[need_y][i] = ' ';
        // До точки
        for (int i = std::min(Win_y, need_y) + 1; i < std::max(Win_y, need_y); ++i)
            labirint[i][Win_x] = ' ';
    // По вертикали
    } else if ((need_y == 0) || (need_y == height - 1)) {
        labirint[Win_y][need_x] = ' ';
        // До поворота
        for (int i = std::min(Win_y, need_y) + 1; i < std::max(Win_y, need_y); ++i)
            labirint[i][need_x] = ' ';
        // До точки
        for (int i = std::min(Win_x, need_x) + 1; i < std::max(Win_x, need_x); ++i)
            labirint[Win_y][i] = ' ';
    }
}

void RandomMoving(std::vector<std::vector<char>>& labirint, const int& vidth, const int& height, 
    const int& Win_x, const int& Win_y, const int& need_x, const int& need_y) {
    // Win - точка, в которую идем. need - точка, из которой идем
    // Выбираем случайно
    if (std::rand() & 1) {
        labirint[Win_y][need_x] = ' ';
        // До поворота
        for (int i = std::min(Win_y, need_y) + 1; i < std::max(Win_y, need_y); ++i)
            labirint[i][need_x] = ' ';
        // До точки
        for (int i = std::min(Win_x, need_x) + 1; i < std::max(Win_x, need_x); ++i)
            labirint[Win_y][i] = ' ';
    } else {
        labirint[need_y][Win_x] = ' ';
        // До поворота
        for (int i = std::min(Win_x, need_x) + 1; i < std::max(Win_x, need_x); ++i)
            labirint[need_y][i] = ' ';
        // До точки
        for (int i = std::min(Win_y, need_y) + 1; i < std::max(Win_y, need_y); ++i)
            labirint[i][Win_x] = ' ';
    }
}

void CreateMoving(std::vector<std::pair<int, int>>& WinRoute, std::vector<std::vector<char>>& labirint, const int& vidth, const int& height, 
    const int& start_x, const int& start_y, const int& finish_x, const int& finish_y) {
    int count = ((vidth - 1) + (height - 1)) / 2;
    std::pair<int, int> temporary_xy(0, 0);
    
    // Первый проход - назначем точки победных поворотов
    for (int i = 0; i < count; ++i) {
        temporary_xy = {1 + std::rand() % (vidth / 2 - 2) * 2, 1 + std::rand() % (height / 2 - 2) * 2};
        WinRoute.push_back(temporary_xy);
        labirint[temporary_xy.second][temporary_xy.first] = ' ';
    }
    
    std::cout << "Create First ROADS!" << std::endl;
    // Новая идея - 1 проход: случайные точки; 2 проход: случайные УГЛОВЫЕ точки 
    // Второй проход - соединяем точки в единый маршрут
    
    // По горизонтали
    StaticRoutes(labirint, vidth, height, WinRoute[0].first, WinRoute[0].second, start_x, start_y);
    // По вертикали
    StaticRoutes(labirint, vidth, height, WinRoute[WinRoute.size() - 1].first, WinRoute[WinRoute.size() - 1].second, finish_x, finish_y);
    
    std::cout << "Create Second ROADS!" << std::endl;
    for (int i = 0; i < WinRoute.size() - 1; ++i) {
        RandomMoving(labirint, vidth, height, WinRoute[i + 1].first, WinRoute[i + 1].second, WinRoute[i].first, WinRoute[i].second);
    }
}

void ToTXT(const std::vector<std::vector<char>>& labirint) {
    std::ofstream file("labirint.txt");
    for (int i = 0; i < labirint.size(); ++i) {
        for (int j = 0; j < labirint[i].size(); ++j) {
            file << labirint[i][j];
        }
        file << std::endl;
    }
}

int main() {
    std::srand(time(NULL));
    int vidth_min(100), vidth_max(220);
    int height_min(60), height_max(180);
    int vidth(0), height(0);
    CreateShape(vidth, height, vidth_min, vidth_max, height_min, height_max);
    std::vector<std::vector<char>> labirint(height, std::vector<char>(vidth, '#'));
    
    int start_x(0), start_y(0);
    int finish_x(0), finish_y(0);
    CreateStartFinish(vidth, height, start_x, start_y, finish_x, finish_y);
    // S = Start
    labirint[start_y][start_x] = 'S';
    // F = Finish
    labirint[finish_y][finish_x] = 'F';
    
    std::vector<std::pair<int, int>> WinRoute;
    std::cout << "Create route!"<< std::endl;
    CreateMoving(WinRoute, labirint, vidth, height, start_x, start_y, finish_x, finish_y);
    ShowLabirint(labirint);
    ToTXT(labirint);
    
    return 0;
}