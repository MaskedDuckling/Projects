#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <linux/input.h>
#include <unistd.h>
#include <cstring>
#include <chrono>
#include <cmath>

using namespace std;

struct input_event event;

int get_keyevent()
{
    
    //open the file for reading
    static ifstream file("/dev/input/event5");
    
    //temp storage for event
    char data[sizeof(event)*100];
    
    //check if file opened!
    if(file.is_open()) {
        //lets get to work
        file.read(data, sizeof(event)*100);

        //now copy the data to the struct
        memcpy(&event, data, 100*sizeof(event));
        // cout << "Event type: " << event.type << endl;
        // cout << "Event code: " << event.code << endl;
        // cout << "Event value: " << event.value << endl;

    }
    else {
        
        cout << "Unable to open file!" << endl;
        return 1;
    }
    return 0;
}

string img[100];

class Paddle
{
private:
public:
    float px;
    float py;

    float bx;
    float by;
    float bvx;
    float bvy;
    Paddle(/* args */);
    ~Paddle();
    void display();
};

Paddle::Paddle(/* args */)
{
    px = 2;
    py = 50;

    bx = 50;
    by = 50;
    bvx = 1;
    bvy = 1;
}

Paddle::~Paddle()
{
}


void Paddle::display()
{
    for (int i = 0; i < 10; i++)
    {
        img[(int)py+i][(int)px] = 'X';
    }
}

void clear_img()
{
    for (int i = 0; i < 100; i++)
    {
        img[i] = string(100, ' ');
        img[i][99] = '0';
    }
}

void display(Paddle paddle, int score)
{
    clear_img();
    paddle.display();
    cout << "Score: " << score << endl;
    for (int i = 0; i < 100; i++)
    {
        cout << img[i] << endl;
    }
}

int main()
{
    Paddle paddle;
    int score = 0;

    while (score < 10)
    {
        get_keyevent();
        // cout << "Event type: " << event.type << endl;
        // cout << "Event code: " << event.code << endl;
        // cout << "Event value: " << event.value << endl;

        if (event.code == 272 && event.type == EV_KEY)
        {
            paddle.py += event.value;
            if (event.value == 1)
                display(paddle, score);
        }
        usleep(100000);
    }
    
}