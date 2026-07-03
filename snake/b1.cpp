//Создать генератор лабиринтов - любого размера.

#include <iostream>
#include <ctime>
#include <vector>

// Случайные размеры
void RandomMainSize(int& width, int& height) {
    int min_width(60), max_width(200);
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

// Проверка занятости прямой 
bool CheckPoint(const int& temporary, const std::vector<int>& Remember) {
    for (int i = 0; i < Remember.size(); ++i) {
        if (Remember[i] == temporary)
            return true;
    }
    return false;
}

void RouteSnake(std::vector<std::vector<char>>& Labarint, const std::pair<int, int>& start, const std::pair<int, int>& finish, 
    const int& width, const int& height, const bool& check) {
    int count_moving = ((Labarint.size() + 1) * (Labarint[0].size() + 1)) / 10;
    
    // Запоминаем горизонтальные маршруты
    std::vector<int> RememberX;
    // Запоминаем вертикальные маршруты
    std::vector<int> RememberY;
    
    std::pair<int, int> last;
    // По горизонтали
    if (check) {
        last.second = 1 + std::rand() % (width - 2);
        // Запоминаем для проверки!
        RememberY.push_back(last.first);
        last.first = start.first;
        Labarint[last.first][last.second] = 'A';
    // По вертикали
    } else {
        last.first = 1 + std::rand() % (height - 2);
        // Запоминаем для проверки!
        RememberX.push_back(last.second);
        last.second = start.second;
        Labarint[last.first][last.second] = 'B';
    }
    
    int temporary(0);    
    for (int i = 0; i < count_moving; ++i) {
        if (Labarint[last.first][last.second] == 'A') {
            do {
                temporary = 1 + std::rand() % (height - 2);
                std::cout << "brUh" << std::endl;
            } while (CheckPoint(temporary, RememberY));
            std::cout << "AAAAAAA" << std::endl;
            
            last.first = temporary;
            Labarint[last.first][last.second] = 'B';
            // Запоминаем для проверки!
            RememberX.push_back(last.second);
        } else {
            do {
                temporary = 1 + std::rand() % (width - 2);
                std::cout << "bruH" << std::endl;
            } while (CheckPoint(temporary, RememberY));
            std::cout << "AAAAAAA" << std::endl;
            
            last.second = temporary;
            Labarint[last.first][last.second] = 'A';
            // Запоминаем для проверки!
            RememberY.push_back(last.first);
        }
    }
    
    ShowLabirint(Labarint);
    
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
    
    RouteSnake(Labarint, start, finish, width, height, check);
    
    // Новая идея: "Маршрут змейки"!
    
    
    
    
    return 0;
}