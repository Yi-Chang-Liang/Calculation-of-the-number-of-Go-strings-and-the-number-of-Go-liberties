#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <iomanip>
#define edge 9
using namespace std;

class GO
{
    public:
        void input();
        void output();
        void initialization();//初始化//
        void visit(int x, int y);
        void add_path(int x, int y);//將已拜訪點加入path中//
        int path_back_x();//取得path中某一點的x座標//
        int path_back_y();//取得path中某一點的y座標//
        void behavior(int x, int y, int color);
        void execut();
    private:
        int n;//統計氣數//
        int go[edge][edge];
        int ans[edge][edge];
        bool gocnt[edge][edge];//紀錄棋子是否已拜訪//
        bool gocnt2[edge][edge];//紀錄此氣點是否已被計算//
        vector<int> path_x;//紀錄search path//
        vector<int> path_y;//紀錄search path//
};

void GO::input()
{
    ifstream gofile;
    gofile.open("goinput.txt");
    for (int i = 0; i < edge; i++)
    {
        for (int j = 0; j < edge; j++)
            gofile >> go[i][j];
    }
    gofile.close();
}

void GO::output()
{
   ofstream ansfile;
    ansfile.open("gooutput_R.txt");
    for (int i = 0; i < edge; i++)
    {
        for (int j = 0; j < edge; j++)
        {
            if(j != edge - 1)
                ansfile << setw(5) << ans[i][j] << " ";
            else
                ansfile << setw(5) << ans[i][j] << endl;
        }
    }
}

void GO::initialization()
{
    for (int i = 0; i < edge; i++)
    {
        for (int j = 0; j < edge; j++) 
        {
            gocnt[i][j] = false;
            gocnt2[i][j] = false;
            ans[i][j] = 0;
        }
    }
}

void GO::visit(int x, int y)
{
    gocnt[x][y] = true;
}

void GO::add_path(int x, int y)
{
    path_x.push_back(x);
    path_y.push_back(y);
}

int GO::path_back_x()
{
    int x;
    x = path_x.back();
    path_x.pop_back();
    return x;
}

int GO::path_back_y()
{
    int y;
    y = path_y.back();
    path_y.pop_back();
    return y;
}

void GO::behavior(int x, int y, int color)
{
	visit(x,y);//將點(x,y)設為已拜訪//
    add_path(x, y);//將點加入path//
    if((x + 1) < edge)//檢查點(x+1,y)是否合法//
    {    
        if(go[x + 1][y] == 0 && gocnt2[x + 1][y] == false)//若為空格且尚未計算氣//
        {    
            n++;
            gocnt2[x + 1][y] = true;
        }
        if(go[x + 1][y] == color && gocnt[x + 1][y] == false)//該點有棋子且與自己同色且尚未拜訪// 
            behavior(x + 1, y, go[x][y]);
    }

    if((x - 1) >= 0)
    {    
        if(go[x - 1][y] == 0 && gocnt2[x - 1][y] == false)
        {    
            n++;
            gocnt2[x - 1][y] = true;
        }
        if(go[x - 1][y] == color && gocnt[x - 1][y] == false)
            behavior(x - 1, y, go[x][y]);
    }
   
    if((y + 1) < edge)
    {    
        if(go[x][y + 1] == 0 && gocnt2[x][y + 1] == false)
        {    
            n++;
            gocnt2[x][y + 1] = true;
        }
        if(go[x][y + 1] == color && gocnt[x][y + 1] == false)
            behavior(x, y + 1, go[x][y]);
    }

    if((y - 1) >= 0)
    {    
        if(go[x][y - 1] == 0 && gocnt2[x][y - 1] == false)
        {    
            n++;
            gocnt2[x][y - 1] = true;
        }
        if(go[x][y - 1] == color && gocnt[x][y - 1] == false)
            behavior(x, y - 1, go[x][y]);
    }
}

void GO::execut()
{
    for (int i = 0; i < edge; i++)
    {
        for (int j = 0; j < edge; j++)
        {
            if(gocnt[i][j] == true || go[i][j] == 0)//該點已拜訪或為空格//
                continue;
            else
            {
                n = 0;//初始化總氣數//
                behavior(i, j, go[i][j]);
                while(!path_x.empty())//將答案寫入矩陣//
                {
                    int x, y;
                    x = path_back_x();
                    y = path_back_y();
                    ans[x][y] = n;
                }
                for (int k = 0; k < edge; k++)//棋串氣數計算完需初始化//
                {
                    for (int q = 0; q < edge; q++) 
                        gocnt2[k][q] = false;
                }
            }
        }
    }
}

int main()
{
    long double timestart = 0;
	long double timeend = 0;
	long double Executiontime = 0; 
    timestart = clock();
    GO go;
    go.input();
    go.initialization();
	go.execut();
    go.output();
    timeend = clock();
	Executiontime = (timeend - timestart) / CLOCKS_PER_SEC;
	printf("Execution time = %.16Lf Second\n", Executiontime);
	cout << "Execution Completed!" << endl;
    system("pause");
    return 0;
}
