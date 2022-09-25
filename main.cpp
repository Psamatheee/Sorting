#include <iostream>
#include <SFML/Graphics.hpp>
#include<vector>
#include <thread>

struct Vector{
    std::vector<int> &ints;
    bool changed = false;
};

void insert_sort(Vector& vec){
    int p = 1;
    int j = 1;
    std::vector<int> &ints = vec.ints;
    while(p < ints.size()){
        while(p >= 1 && ints[p] < ints[p-1]){
            int temp = ints[p];
            ints[p] = ints[p-1];
            ints[p-1] = temp;
            p--;
            vec.changed = true;
        }
        vec.changed = false;
        j++;
        p = j;
    }
}
int main() {


    std::vector<int> nums {2,14,1,6,12,13,66,10,7,4};
    Vector v{nums, false};

    sf::RenderWindow window{sf::VideoMode::getDesktopMode(), "Sorting!"};

  //  std::thread first(insert_sort, std::ref(v));  // spawn new thread that calls foo()
    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        sf::VertexArray rectangles {sf::Quads, 40};
        for(int i = 0; i < 10; i++){
            float ii = float(i);
            rectangles[i*4] = sf::Vector2f{10+10*ii,10};
            rectangles[i*4 + 1] = sf::Vector2f{20+10*ii,10};
            rectangles[i*4 + 2] = sf::Vector2f{20+10*ii, static_cast<float>(nums[i]*10.0) + 10};
            rectangles[i*4 + 3] = sf::Vector2f{10+10*ii, static_cast<float>(nums[i]*10.0) + 10};
        }

        window.draw(rectangles);
        window.display();

    }
}


