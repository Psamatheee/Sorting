#include <iostream>
#include <SFML/Graphics.hpp>
#include<vector>
#include <random>


void rec_bubble_sort(std::vector<int> &ints, int index, std::vector<std::vector<int>> &v){
    if(index == 0) return;
    for(int i = 0; i < index; i++){
        if(ints[i] > ints[i+1]){
            int temp = ints[i];
            ints[i] = ints[i+1];
            ints[i+1] = temp;
            std::vector<int> vv = std::vector<int>(ints.begin(), ints.end());
            v.push_back(vv);

        }
    }
    rec_bubble_sort(ints, index-1, v);
}

void bubble_sort(std::vector<int> &ints, std::vector<std::vector<int>> &v){
    rec_bubble_sort(ints, ints.size()-1, v);
}
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

std::vector<int> merge_sort(std::vector<int> ints, int& count){
    if (ints.size() == 1) return ints;
    std::vector<int> b = std::vector<int>(ints.begin(), ints.begin() + floor(ints.size()/2));
    std::vector<int> c = std::vector<int>(ints.begin() + floor(ints.size() /2), ints.end());
    b = merge_sort(b,count);
    c = merge_sort(c,count);
    std::vector<int> merged = merge(b,c);
    for(int i : merged){
        std::cout<< i << " ";
    }
    std::cout<<"\n";
    count++;
    return merged;
}



void merge(std::vector<int> &ints, int l, int l_end, int r, std::vector<std::vector<int>> &vecs){
    int r_start = l_end + 1;

    std::vector<int> copy = std::vector<int>(ints.begin() + l, ints.begin()+r+1);
    int size = 0;
    int ia = 0;
    int ib = r_start - l;
    int i = l;
    while(size < copy.size()){
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
        std::vector<int> v =std::vector<int>(ints.begin(), ints.end());

        vecs.push_back(v);
    }


}

void merge_sort(std::vector<int> &ints, int l, int r, std::vector<std::vector<int>> &vecs){
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
    merge_sort(ints,l, l + floor(size /2 ) - 1, vecs );
    merge_sort(ints, l+ floor((size)/2),r, vecs);
    merge(ints,l,l + floor(size /2 ) - 1 ,r,vecs);

}
void index_merge_sort(std::vector<int> &ints, std::vector<std::vector<int>> &vecs){
    merge_sort(ints, 0,ints.size()-1, vecs);
}

int main() {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> gen(1,80);


    std::vector<int> vv {1,2};
    std::vector<int> ee{vv.begin() , vv.begin() + floor(vv.size()/2)};
    for (int tt : ee){
    }

    int size = 100;

    std::vector<int> nums(size);
    for(int i = 0; i < size; i++){
        nums[i] = gen(mt);
    }

    std::vector<int> dd{44,22,5,1,2,6,55,10,9};
    std::vector<std::vector<int>> dd_v;
    dd_v.push_back(dd);
    bubble_sort(dd, dd_v);

    int count = 0;
    std::vector<std::vector<int>> v;
    v.push_back(nums);
   // index_merge_sort(nums, v);
    bubble_sort(nums,v);
    for(int a : dd ){
        std::cout << a << " ";
    }
    std::cout << "\n";
    std::cout<<count<<"\n";
    bool reset = false;

    sf::RenderWindow window{sf::VideoMode::getDesktopMode(), "Sorting!"};
    int x = window.getSize().x;
    float width = (x-size*10) / size;
    float height = window.getSize().y;
    sf::Clock clock;
    int j = 1;
    nums = v[0];
    while(window.isOpen()){
        window.clear();

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        while(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
            reset = true;

        }

        if(j >= v.size()){reset= true;
            clock.restart();
            while(clock.getElapsedTime().asSeconds() < 1){}
        }

        if(reset){
            window.clear();

            for(int i = 0; i < size; i++){
                nums[i] = gen(mt);
            }
            v.clear();
            v.push_back(nums);
            index_merge_sort(nums, v);
            reset = false;
            nums = v[0];
            j = 1;
        }


        if(clock.getElapsedTime().asSeconds() >= 0.02){
           // insert_sort(nums);
            if(j < v.size()){
                nums = v[j];

                j++;
            }
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


