#include <iostream>
#include <SFML/Graphics.hpp>
#include<vector>
#include <random>

void insert_sort(std::vector<int> &ints){
    int p = 1;
    int j = 1;
    while(p < ints.size()){
        while(p >= 1 && ints[p] < ints[p-1]){
            int temp = ints[p];
            ints[p] = ints[p-1];
            ints[p-1] = temp;
            p--;
            return;
        }
        j++;
        p = j;
    }
}

std::vector<int> merge(std::vector<int> a, std::vector<int> b){
    std::vector<int> merged;
    int size = 0;
    int ia = 0;
    int ib = 0;
    while(size < a.size() + b.size()){
        if(ib == b.size() ||(ia!=a.size() &&  a[ia] < b[ib])) {
            merged.push_back(a[ia]);
            ia++;
        }
        else {
            merged.push_back(b[ib]);
            ib++;
        }
        size++;
    }

    return merged;
}

std::vector<int> merge_sort(std::vector<int> ints){
    if (ints.size() == 1) return ints;
    std::vector<int> b = std::vector<int>(ints.begin(), ints.begin() + floor(ints.size()/2));
    std::vector<int> c = std::vector<int>(ints.begin() + floor(ints.size() /2), ints.end());
    b = merge_sort(b);
    c = merge_sort(c);
    return merge(b,c);
}

int main() {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> gen(1,50);


    std::vector<int> vv {1,2};
    std::vector<int> ee{vv.begin() , vv.begin() + floor(vv.size()/2)};
    for (int tt : ee){
    }

    int size = 100;

    std::vector<int> nums(size);
    for(int i = 0; i < size; i++){
        nums[i] = gen(mt);
    }

    std::vector<int> dd{4,22,5,17,2,6,55,9,10};
    std::vector<int> aa = merge_sort(dd);
    for(int a : aa ){
        std::cout << a << " ";
    }
    std::cout << "\n";

    sf::RenderWindow window{sf::VideoMode::getDesktopMode(), "Sorting!"};
    int x = window.getSize().x;
    float width = (x-size*10) / size;
    float height = window.getSize().y;
    sf::Clock clock;
    while(window.isOpen()){
        window.clear();

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        if(clock.getElapsedTime().asSeconds() >= 0.5){
            insert_sort(nums);
            clock.restart();

        }

        size_t vertex_num = 4 * size;
        sf::VertexArray rectangles {sf::Quads, vertex_num};
        for(int i = 0; i < size; i++){
            float left_x = 10;
            if(i != 0) left_x = rectangles[i*4-2].position.x + 10;
            rectangles[i*4].position = sf::Vector2f{left_x, height - 10};
            float right_x = rectangles[i*4].position.x + width;
            rectangles[i*4 + 1].position = sf::Vector2f{right_x ,height - 10};
            rectangles[i*4 + 2].position = sf::Vector2f{right_x, height - static_cast<float>(nums[i]*10.0) - 10};
            rectangles[i*4 + 3].position = sf::Vector2f{left_x, height - static_cast<float>(nums[i]*10.0) - 10};
        }


        window.draw(rectangles);
        window.display();

    }
}


