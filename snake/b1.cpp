//Создать генератор лабиринтов - любого размера.

#include <iostream>
#include <ctime>
#include <vector>

// Случайные размеры
void RandomMainSize(int& width, int& height) {
    int min_width(60), max_width(160);
    int min_height(35), max_height(80);
    
    width = min_width + std::rand() % (max_width - min_width + 1);
    height = min_height + std::rand() % (max_height - min_height + 1);
    
    std::cout << min_width << " <= " << width << " <= " << max_width << std::endl;
    std::cout << min_height << " <= " << height << " <= " << max_height << std::endl;
}

// Главный вывод
void ShowLabirint(const std::vector<std::vector<char>>& Labarint) {
    for (int i = 0; i < Labarint.size(); ++i) {
        for (int j = 0; j < Labarint[i].size(); ++j)
            std::cout << Labarint[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Случайные координаты старта и финиша
void RandomStartFinish(std::pair<int, int>& start, std::pair<int, int>& finish, const int& width, const int& height, const bool& check) {
    // По горизонтали
    if (check) {
        start.second = 0;
        finish.second = width - 1;
        
        start.first = 1 + std::rand() % (height - 1);
        finish.first = 1 + std::rand() % (height - 1);
    // По вертикали
    } else {
        start.first = 0;
        finish.first = height - 1;
        
        start.second = 1 + std::rand() % (width - 1);
        finish.second = 1 + std::rand() % (width - 1);
    }
}

void CompleteRoute(std::vector<std::vector<char>>& Labarint, const int& start, const int& finish, const int& main, const bool& vert_hor) {
    if (vert_hor) {
        for (int i = start + 1; i < finish; ++i) 
            Labarint[main][i] = '1';
    } else {
        for (int i = start + 1; i < finish; ++i) 
            Labarint[i][main] = '2';
    }
}

void RouteSnake(std::vector<std::vector<char>>& Labarint, const std::pair<int, int>& start, const std::pair<int, int>& finish, 
    const int& width, const int& height, const bool& check) {
    int count_moving = ((Labarint.size() + 1) * (Labarint[0].size() + 1)) / 40;
    
    // Запоминаем горизонтальные маршруты
    std::vector<int> RememberX;
    // Запоминаем вертикальные маршруты
    std::vector<int> RememberY;
    
    std::pair<int, int> last;
    // По горизонтали
    if (check) {
        last.second = 1 + std::rand() % (width - 2);
        // Запоминаем для проверки!
        RememberX.push_back(last.second);
        last.first = start.first;
        // Заполняем
        CompleteRoute(Labarint, std::min(start.second, last.second), std::max(start.second, last.second), last.first, true);
        Labarint[last.first][last.second] = 'A';
    // По вертикали
    } else {
        last.first = 1 + std::rand() % (height - 2);
        // Запоминаем для проверки!
        RememberY.push_back(last.first);
        last.second = start.second;
        // Заполняем
        CompleteRoute(Labarint, std::min(start.first, last.first), std::max(start.first, last.first), last.second, false);
        Labarint[last.first][last.second] = 'B';
    }
    ShowLabirint(Labarint);
    
    int temporary(0);
    for (int i = 0; i < count_moving; ++i) {
        if (Labarint[last.first][last.second] == 'A') {
            temporary = 1 + std::rand() % (height - 2);
            // Заполняем
            CompleteRoute(Labarint, std::min(last.first, temporary), std::max(last.first, temporary), last.second, false);
            last.first = temporary;
            // Запоминаем для проверки!
            RememberY.push_back(last.first);
            Labarint[last.first][last.second] = 'B';
        } else {
            temporary = 1 + std::rand() % (width - 2);
            // Заполняем
            CompleteRoute(Labarint, std::min(last.second, temporary), std::max(last.second, temporary), last.first, true);
            last.second = temporary;
            // Запоминаем для проверки!
            RememberX.push_back(last.second);
            Labarint[last.first][last.second] = 'A';
        }
        // std::cout << i + 1 << ") \n";
        // ShowLabirint(Labarint);
    }
}

// first = Y -------- second = X ------- Для удобства

int main() {
    std:srand(time(NULL));
    // Случайные размеры
    int width(0), height(0);
    RandomMainSize(width, height);
    
    // Создание лабиринта
    std::vector<std::vector<char>> Labarint(height, std::vector<char>(width, '_'));
    
    // Случайные координаты старта и финиша
    std::pair<int, int> start(0, 0), finish(0, 0);
    // Чтобы запомнить вертикаль/горизонталь
    bool check = std::rand() & 1;
    RandomStartFinish(start, finish, width, height, check);
    Labarint[start.first][start.second] = 'S';
    Labarint[finish.first][finish.second] = 'F';
    ShowLabirint(Labarint);
    
    // Новая идея: "Маршрут змейки"!
    RouteSnake(Labarint, start, finish, width, height, check);
    ShowLabirint(Labarint);
    
    return 0;
}