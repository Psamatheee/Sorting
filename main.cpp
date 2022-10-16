#include <iostream>
#include <SFML/Graphics.hpp>
#include<vector>
#include <random>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>

bool running = true;
bool finished = true;
bool restart = false;
int milliseconds = 15;

std::condition_variable mcond;
std::mutex mmutex;

enum class Choice{MERGE, INSERT, BUBBLE};
Choice choice = Choice::MERGE;

void rec_bubble_sort(std::vector<int> &ints, int index){
    if(index == 0) return;
    for(int i = 0; i < index && !restart; i++ ){
        if(ints[i] > ints[i+1]){
            int temp = ints[i];
            ints[i] = ints[i+1];
            ints[i+1] = temp;

            if(!restart) std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

        }
    }
   if (!restart) rec_bubble_sort(ints, index-1);
}

void bubble_sort(std::vector<int> &ints){
    rec_bubble_sort(ints, ints.size()-1);
}
void insert_sort(std::vector<int> &ints){
    int p = 1;
    int j = 1;
    while(p < ints.size() && !restart){
        while(p >= 1 && ints[p] < ints[p-1] && !restart){
            int temp = ints[p];
            ints[p] = ints[p-1];
            ints[p-1] = temp;
            p--;
            if(!restart) std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        }
        j++;
        p = j;
    }
}

void merge(std::vector<int> &ints, int l, int l_end, int r){
    int r_start = l_end + 1;

    std::vector<int> copy = std::vector<int>(ints.begin() + l, ints.begin()+r+1);
    int size = 0;
    int ia = 0;
    int ib = r_start - l;
    int i = l;
    while(size < copy.size() && !restart){
        if(ib == copy.size() ||(ia!=r_start - l&&  copy[ia] < copy[ib])) {
            ints[i] = (copy[ia]);
            ia++;
            i++;
        }
        else {
            ints[i] = (copy[ib]);
            ib++;
            i++;
        }
        size++;
        if(!restart) std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }


}

void merge_sort(std::vector<int> &ints, int l, int r){
    if (r-l == 1) {
        if(ints[l] > ints[r]){
            int temp = ints[r];
            ints[r] = ints[l];
            ints[l] = temp;
        }
        return;
    }
    if(r==l){
        return;
    }

    int size = r - l + 1;
    if(!restart){
    merge_sort(ints,l, l + floor(size /2 ) - 1);
    merge_sort(ints, l+ floor((size)/2),r);
    merge(ints,l,l + floor(size /2 ) - 1 ,r);}

}


void randomize_nums(std::vector<int>& nums, std::mt19937& mt, std::uniform_int_distribution<int>& gen){
    while(running) {
        std::unique_lock<std::mutex> lock(mmutex);
        for (int i = 0; i < nums.size(); i++) {
            nums[i] = gen(mt);
        }
        finished = false;
        mcond.notify_one();
    }
}

void sort(std::vector<int>& nums){
    while(running){
        std::unique_lock<std::mutex> lck (mmutex);
        mcond.wait(lck,[] { return !finished; });
        restart = false;
        if(choice == Choice::MERGE){
            merge_sort(nums, 0, nums.size() - 1);
        }
        else if(choice == Choice::INSERT){
            insert_sort(nums);
        }else if(choice == Choice::BUBBLE){
            bubble_sort(nums);
        }
        finished = true;
        lck.unlock();
    }
}

int main() {

    std::random_device rd;
    std::mt19937 mt(rd());
    sf::Font arial;
    arial.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(arial);
    text.setCharacterSize(30);
    text.setString("Merge Sort");
    text.move(20,20);
    std::uniform_int_distribution<int> gen(1,80);
    int size = 100;
    bool switch_sort = false;
    int separation = 10;

    sf::RenderWindow window{sf::VideoMode::getDesktopMode(), "Sorting!"};
    int x = window.getSize().x;
    float width = (x-(size+1)*10) / size;
    if(size*separation + size*width > x){
        width = float(x)/size;
        separation = 0;
        std::cout<<width<<std::endl;
        std::cout<<x<<std::endl;

    }
    float height = window.getSize().y;
    std::vector<int> nums(size);
    std::thread reset_nums(randomize_nums, std::ref(nums), std::ref(mt), std::ref(gen) );
    std::thread test (sort, std::ref(nums));


    while(window.isOpen() && running){
        window.clear();

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
                running = false;
            }
        }

        Choice change = choice;
        while(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
            switch_sort = true;
            change = Choice::MERGE;
            text.setString("Merge Sort");
        } while(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
            switch_sort = true;
            change = Choice::INSERT;
            text.setString("Insert Sort");
        }while(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
            switch_sort = true;
            change = Choice::BUBBLE;
            text.setString("Bubble Sort");
        }

        if( switch_sort){
            restart = true;
            choice = change;
            switch_sort = false;
            finished = true;
        }

        size_t vertex_num = 4 * size;
        sf::VertexArray rectangles {sf::Quads, vertex_num};
        for(int i = 0; i < size; i++){
            float left_x = 0;
            if(i != 0) left_x = rectangles[i*4-2].position.x + separation;
            rectangles[i*4].position = sf::Vector2f{left_x, height};
            float right_x = rectangles[i*4].position.x + width;
            rectangles[i*4 + 1].position = sf::Vector2f{right_x ,height};
            rectangles[i*4 + 2].position = sf::Vector2f{right_x, height - static_cast<float>(nums[i]*10.0)};
            rectangles[i*4 + 3].position = sf::Vector2f{left_x, height - static_cast<float>(nums[i]*10.0)};
        }


        window.draw(text);
        window.draw(rectangles);
        window.display();

    }
    restart = true;
    running = false;
    test.join();
    reset_nums.join();


}


