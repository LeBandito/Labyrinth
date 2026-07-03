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
        start_x = start - 1;
        start_y = 0;
    } else if (((vidth + height) / start) && true) {
        start_x = vidth - 1;
        start_y = start - vidth - 1;
    } else if (((vidth + height + vidth) / start) && true) {
        start_x = vidth - (start - (vidth + height));
        start_y = height - 1;
    } else if (((vidth + height + vidth + height) / start) && true) {
        start_x = 0;
        start_y = (vidth + height + vidth + height) - start - 1;
    }
    
    std::cout << " -> (" << start_x + 1<< "; " << start_y + 1<< ")" << std::endl;
    
    std::cout << "finish = " << finish;
    // finish
    if ((vidth / finish) && true) {
        finish_x = finish - 1;
        finish_y = 0;
    } else if (((vidth + height) / finish) && true) {
        finish_x = vidth - 1;
        finish_y = finish - vidth - 1;
    } else if (((vidth + height + vidth) / finish) && true) {
        finish_x = vidth - (finish - (vidth + height));
        finish_y = height - 1;
    } else if (((vidth + height + vidth + height) / finish) && true) {
        finish_x = 0;
        finish_y = (vidth + height + vidth + height) - finish - 1;
    }
    
    std::cout << " -> (" << finish_x + 1<< "; " << finish_y + 1 << ")" << std::endl;
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
    // Новая идея - 1 проход: случайные точки; 2 проход: случайные УГЛОВЫЕ точки 
    // Второй проход - соединяем точки в единый маршрут
    // Cлева
    if (start_x == 0) {
        labirint[start_y][WinRoute[0].first] = 'A';
        // До поворота
        for (int i = 1; i < WinRoute[0].first; ++i)
            labirint[start_y][i] = '1';
        // До точки
        for (int i = std::min(WinRoute[0].second, start_y) + 1; i < std::max(WinRoute[0].second, start_y); ++i)
            labirint[i][WinRoute[0].first] = '2';
    // Справа
    } else if (start_x == vidth - 1) {
        labirint[start_y][WinRoute[0].first] = 'B';
        // До поворота
        for (int i = WinRoute[0].first + 1; i < start_x; ++i)
            labirint[start_y][i] = '3';
        // До точки
        for (int i = std::min(WinRoute[0].second, start_y) + 1; i < std::max(WinRoute[0].second, start_y); ++i)
            labirint[i][WinRoute[0].first] = '4';
    // Сверху
    } else if (start_y == 0) {
        labirint[WinRoute[0].second][start_x] = 'C';
        // До поворота
        for (int i = 1; i < WinRoute[0].second; ++i)
            labirint[i][start_x] = '5';
        // До точки
        for (int i = std::min(WinRoute[0].second, start_y) + 1; i < std::max(WinRoute[0].second, start_y); ++i)
            labirint[i][WinRoute[0].first] = '6';
    // Снизу
    } else if (start_y == height - 1) {
        labirint[WinRoute[0].second][start_x] = 'D';
        // До поворота
        for (int i = WinRoute[0].second + 1; i < start_y; ++i)
            labirint[i][start_x] = '7';
        // До точки
        for (int i = std::min(WinRoute[0].second, start_y) + 1; i < std::max(WinRoute[0].second, start_y); ++i)
            labirint[i][WinRoute[0].first] = '8';
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
    labirint[start_y][start_x] = 'S';
    labirint[finish_y][finish_x] = 'F';
    ShowLabirint(labirint);
    
    std::vector<std::pair<int, int>> WinRoute;
    std::cout << "Create route!"<< std::endl;
    CreateMoving(WinRoute, labirint, vidth, height, start_x, start_y, finish_x, finish_y);
    //ShowLabirint(labirint);    
    
    return 0;
}