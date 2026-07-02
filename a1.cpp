/*Создать генератор лабиринтов - любого размера.
пример:*/

#include <iostream>
#include <ctime>
#include <vector>

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

void CreateStartFinish(const int& vidth, const int& height, int& start_x, int& start_y, int& finish_x, int& finish_y) {
    int start = 0 + std::rand() % (2 * (vidth + height)); 
    int finish = 0 + std::rand() % (2 * (vidth + height)); 
    std::cout << "start = " << start;
    
    // start
    if ((vidth / start) && true) {
        start_x = start;
        start_y = 1;
    } else if (((vidth + height) / start) && true) {
        start_x = vidth;
        start_y = start - vidth;
    } else if (((vidth + height + vidth) / start) && true) {
        start_x = vidth - (start - (vidth + height)) + 1;
        start_y = height;
    } else if (((vidth + height + vidth + height) / start) && true) {
        start_x = 1;
        start_y = (vidth + height + vidth + height) - start;
    }
    
    std::cout << " -> (" << start_x << "; " << start_y << ")" << std::endl;
    
    std::cout << "finish = " << finish;
    // finish
    if ((vidth / finish) && true) {
        finish_x = finish;
        finish_y = 1;
    } else if (((vidth + height) / finish) && true) {
        finish_x = vidth;
        finish_y = finish - vidth;
    } else if (((vidth + height + vidth) / finish) && true) {
        finish_x = vidth - (finish - (vidth + height)) + 1;
        finish_y = height;
    } else if (((vidth + height + vidth + height) / finish) && true) {
        finish_x = 1;
        finish_y = (vidth + height + vidth + height) - finish;
    }
    
    std::cout << " -> (" << finish_x << "; " << finish_y << ")" << std::endl;
}

void TemperaryFind(const int& x, const int& y, std::pair<int, int> temporary_xy) {
    
}

void CreateMoving(std::vector<std::pair<int, int>>& WinRoute, std::vector<std::vector<char>>& labirint, const int& vidth, const int& height, 
    const int& start_x, const int& start_y, const int& finish_x, const int& finish_y) {
    int count = ((vidth - 1) + (height - 1)) / 5;
    
    std::pair<int, int> temporary_xy(0, 0); 
    
    // Первый проход - назначем точки победных поворотов
    for (int i = 0; i < count; ++i) {
        temporary_xy = {1 + std::rand() % (vidth - 2), 1 + std::rand() % (height - 2)};
        WinRoute.push_back(temporary_xy);
        labirint[temporary_xy.second][temporary_xy.first] = '+';
    }
    ShowLabirint(labirint);
    
    std::cout << "Create ROADS!" << std::endl;
    
    // Старая идея - 1 проход: случайные точки; 2 проход: пытаемся соединить случайные точки
    
    // Второй проход - соединяем точки в единый маршрут
    // Cлева
    if (start_x == 1) {
        labirint[start_y - 1][WinRoute[0].first] = 'A';
        // До поворота
        for (int i = 1; i < WinRoute[0].first; ++i)
            labirint[start_y - 1][i] = '1';
        // До точки
        for (int i = WinRoute[0].second; i < WinRoute[0].first; ++i)
            labirint[start_y - 1][i] = '1';
    // Справа
    } else if (start_x == vidth) {
        labirint[start_y - 1][WinRoute[0].first] = 'B';
        for (int i = WinRoute[0].first + 1; i < start_x - 1; ++i)
            labirint[start_y - 1][i] = '2';
    // Сверху
    } else if (start_y == 1) {
        labirint[WinRoute[0].second][start_x - 1] = 'C';
        for (int i = 1; i < WinRoute[0].second; ++i)
            labirint[i][start_x - 1] = '3';
    // Снизу
    } else if (start_y == height) {
        labirint[WinRoute[0].second][start_x - 1] = 'D';
        for (int i = WinRoute[0].second + 1; i < start_y - 1; ++i)
            labirint[i][start_x - 1] = '4';
    }
    
    // for (int i = 1; i < WinRoute.size(); ++i) {
    //     if () {
            
    //     }
    // }
    
    ShowLabirint(labirint);
    
    
    
}

int main() {
    std::srand(time(NULL));
    int vidth_min(40), vidth_max(140);
    int height_min(10), height_max(45);
    int vidth(0), height(0);
    CreateShape(vidth, height, vidth_min, vidth_max, height_min, height_max);
    std::vector<std::vector<char>> labirint(height, std::vector<char>(vidth, '_'));
    ShowLabirint(labirint);
    
    int start_x(0), start_y(0);
    int finish_x(0), finish_y(0);
    CreateStartFinish(vidth, height, start_x, start_y, finish_x, finish_y);
    labirint[start_y - 1][start_x - 1] = 'S';
    labirint[finish_y - 1][finish_x - 1] = 'F';
    ShowLabirint(labirint);
    
    std::vector<std::pair<int, int>> WinRoute;
    std::cout << "Create route!"<< std::endl;
    CreateMoving(WinRoute, labirint, vidth, height, start_x, start_y, finish_x, finish_y);
    //ShowLabirint(labirint);    
    
    return 0;
}