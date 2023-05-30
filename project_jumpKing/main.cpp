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

class map
{
private:
public:
    vector<string> lines;
    size_t px;
    size_t py;
    int coup;
    int dir = 1;
    map(string file_name);
    ~map();

    void render();
    void jump(float time);
};

map::map(string file_name)
{
    fstream map("lvl1.txt");
    if (map.is_open())
    {
        string line;
        while (getline(map, line))
        {
            cout << line << endl;
            lines.push_back(line);
            if (line.find("w") != string::npos)
            {
                px = line.find("w");
                py = lines.size() - 1;
                lines[py][px] = ' ';
            }
        }
    }
    else
    {
        cout << "Error opening file" << endl;
    }
}

map::~map()
{
}



void map::render()
{
    string res;
    char tmp = lines[py][px];
    lines[py][px] = 'w';

    int copy = coup;
    for (int i=0; copy; i++)
    {
        lines[2][3-i] = copy%10 + '0';
        copy /= 10;
    }
    for (int i = 0; i < lines.size(); i++)
        res += lines[i] + "\n";
    cout << res << endl;
    cout.flush();
    lines[py][px] = tmp;
}

float get_time()
{
    timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec + ((float)time.tv_usec / 1000000);
}

void map::jump(float time)
{
    float power = 1 - exp(-2 * time);

    float x = px;
    float y = py;

    // cout << px << " " << py << endl;
    // cout.flush();

    if (string("_><").find(lines[py][px]) == string::npos)
        power *= 0.55;

    float vx = dir * power * 0.1;
    float vy = -power * 0.2;
    float start;
    coup++;
    if (lines[py][px] == '>')
    {
        dir = 1;
        vx = abs(vx) * 2;
        vy /= 2;
    }
    else if (lines[py][px] == '<')
    {
        dir = -1;
        vx = -abs(vx) * 2;
        vy /= 2;
    }

    while (1)
    {
        // start = get_time();
        vy += 0.0001;
        x += vx * 0.1;
        y += vy * 0.1;
        if ((int)y != py || (int)x != px)
        {
            if (string("+-_ ><").find(lines[(int)y][(int)x]) == string::npos)
            {
                if (py < (int)y)
                {
                    // cout << power << endl;
                    break;
                }
                else if (py > (int)y)
                {
                    y = py;
                    vy = 0;
                }
                if (px != (int)x)
                {
                    x = px;
                    vx = -vx;
                    dir = -dir;
                }

            }
            py = y;
            px = x;
            render();
        }
        
        usleep(50);
        // while (get_time() - start < 0.1)
        // {
        //     // cout << "waiting" << endl;
        //     // cout << get_time() << endl;
        // }

    }

}

struct input_event event;

int get_keyevent()
{
    
    //open the file for reading
    static ifstream file("/dev/input/event5");
    
    //temp storage for event
    char data[sizeof(event)];
    
    //check if file opened!
    if(file.is_open()) {
        //lets get to work
        file.read(data, sizeof(event));

        //now copy the data to the struct
        memcpy(&event, data, sizeof(event));
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

int main(int argc, char const *argv[])
{
    map map("map.txt");
    timeval start;
    gettimeofday(&start, NULL);
    
    while (1)
    {
        get_keyevent();
        if (event.code == 272 && event.type == EV_KEY)
        {
            if (event.value == 1)
                gettimeofday(&start, NULL);
            if (event.value == 0)
            {
                timeval end;
                gettimeofday(&end, NULL);
                map.jump(((end.tv_sec - start.tv_sec) + (float)(end.tv_usec - start.tv_usec) / 1000000));
                if (map.lines[map.py][map.px] == '-'|| map.lines[map.py][map.px] == '+')
                {
                    cout << "You win!" << endl;
                    break;
                }
            }
        }
    }
    
    return 0;
}
