#include <iostream>
#include <SFML/Graphics.hpp>
#include<vector>
#include <random>
struct Vector{
    std::vector<int> &ints;
    int p = 1;
    int j = 1;

    void next(){

    }
};

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
int main() {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> gen(1,50);


    int size = 50;

    std::vector<int> nums(size);
    for(int i = 0; i < size; i++){
        nums[i] = gen(mt);
    }

    sf::RenderWindow window{sf::VideoMode::getDesktopMode(), "Sorting!"};
    int x = window.getSize().x;
    float width = (x-size*10) / size;
    float height = window.getSize().y;
    sf::Clock clock;
  //  std::thread first(insert_sort, std::ref(v));  // spawn new thread that calls foo()
    while(window.isOpen()){
        window.clear();

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        if(clock.getElapsedTime().asSeconds() >= 0.005){
            insert_sort(nums);
            clock.restart();
            for(int i : nums){
                std::cout << i << " ";
            }
            std::cout << "\n";
        }

        size_t vertex_num = 4 * size;
        sf::VertexArray rectangles {sf::Quads, vertex_num};
        for(int i = 0; i < size; i++){
            float ii = float(i);
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


