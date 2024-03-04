#include <SFML/Graphics.hpp>
#include <vector>

void FillRand(int A[],int n)
{
    for (int i=0;i<n;i++)
    {
        A[i]=rand()%10;
    }
}

int SelectSort(int A[], int n)
{
    int k, temp, m=0, c=0;
    for (int i=0; i<n-1; i++)
    {
        k = i;
        for (int j=i+1; j<n; j++)
        {
            c++;
            if (A[j] < A[k]) {k = j;}
        }
        temp = A[i];
        A[i] = A[k];
        A[k] = temp;
        m+=3;
        
    }
    return m+c;
}

int ShakerSort(int A[], int n)
{
    int L = 0, R = n - 1, k,m=0,c=0;
    do {
        k = R;
        for (int j = R; j > L; j--) {
            c++;
            if (A[j] < A[j - 1]) {
                int temp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = temp;
                k = j;
                m+=3;
            }
        }
        L = k;
        for (int j = L; j < R; j++) {
            c++;
            if (A[j] > A[j + 1]) {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
                k = j;
                m+=3;
            }
        }
        R = k;
        
    } while (L < R);
    return m+c;
}

int BubbleSort(int A[], int n)
{
    int temp,m=0,c=0;
    for (int i = 0; i < n; i++)
    {
        for (int j = n-1; j > i; j--)
        {
            c++;
            if (A[j] < A[j-1])
            {
                temp = A[j];
                A[j] = A[j-1];
                A[j-1] = temp;
                m+=3;
            }
        }
    }
    return m+c;
}

int InsertSort(int A[], int n)
{
    int i, t, j,m=0,c=0;

    for (i = 1; i < n; i++) 
    { 
        t = A[i];
        j = i - 1;
        c++;
        while (j >= 0 && A[j] > t) 
        {
            c++;
            A[j + 1] = A[j];
            j--;
            m++;
            
        }
        A[j + 1] = t;
        m+=2;
    }
    return m+c;
}

int ShellSort(int A[], int n) 
{
    
    int m=0,c=0;
    for (int interval = n / 2; interval > 0; interval /= 2) 
    {
        for (int i = interval; i < n; i += 1) 
        {
            int temp = A[i];
            int j;
            for (j = i; j >= interval && A[j - interval] > temp; j -= interval) 
            {
                A[j] = A[j - interval];
                m += 3;
                c++;
            }
            A[j] = temp;
            m+=2;
        }
    }
    return m+c;
}

int main()
{
    int textsSize=6;
    std::vector<sf::Text> texts;
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return 1;
    
    for (int i=0;i<textsSize;i++) texts.push_back(text);
    for (auto& txt : texts)        
    {
        txt.setCharacterSize(20);
        txt.setFont(font);
    }
    texts[0].setString("M+C");
    texts[0].setPosition(20,20);
    texts[0].setColor(sf::Color::White);
    texts[1].setString("N");
    texts[1].setPosition(1050,710);
    texts[1].setColor(sf::Color::White);
    texts[2].setString("SelectSort");
    texts[2].setPosition(20,770);
    texts[2].setColor(sf::Color::Green);
    texts[3].setString("BubbleSort");
    texts[3].setPosition(20,820);
    texts[3].setColor(sf::Color::Yellow);
    texts[4].setString("ShakerSort");
    texts[4].setPosition(20,870);
    texts[4].setColor(sf::Color::Cyan);
    texts[5].setString("InsertSort");
    texts[5].setPosition(160,770);
    texts[5].setColor(sf::Color::Red);
    sf::RenderWindow window(sf::VideoMode(1100, 950), "SFML works!");
    sf::VertexArray line(sf::LinesStrip, 4);
    line[0].position = sf::Vector2f(10, 0);
    
    line[1].position = sf::Vector2f(10, 750);
   
    line[2].position =sf::Vector2f(10,750);
    
    line[3].position =sf::Vector2f(1100,750);
    
    std::vector<sf::Vertex> selectSort;
    std::vector<sf::Vertex> bubbleSort;
    std::vector<sf::Vertex> shakerSort;
    std::vector<sf::Vertex> insertSort;
    std::vector<sf::Vertex> shellSort;
    

    for (int n=0; n<=700;n++)
    {
        int A[n];
        FillRand(A,n);
        int t=SelectSort(A,n);
        selectSort.push_back(sf::Vertex(sf::Vector2f(10 + n*2, 750 - t*0.05  ), sf::Color::Green));
        FillRand(A,n);
        t=BubbleSort(A,n);
        bubbleSort.push_back(sf::Vertex(sf::Vector2f(10 + n*2, 750 - t*0.05 ), sf::Color::Yellow));
        FillRand(A,n);
        t=ShakerSort(A,n);
        shakerSort.push_back(sf::Vertex(sf::Vector2f(10 + n*2, 750 - t*0.05 ), sf::Color::Cyan));
        FillRand(A,n);
        t=InsertSort(A,n);
        insertSort.push_back(sf::Vertex(sf::Vector2f(10 + n*2, 750 - t*0.05 ), sf::Color::Red));
        FillRand(A,n);
        t=ShellSort(A,n);
        shellSort.push_back(sf::Vertex(sf::Vector2f(10 + n*2, 750 - t*0.05 ), sf::Color::Magenta));
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(line);
        window.draw(selectSort.data(), selectSort.size(), sf::LinesStrip);
        window.draw(bubbleSort.data(), selectSort.size(), sf::LinesStrip);
        window.draw(shakerSort.data(), selectSort.size(), sf::LinesStrip);
        window.draw(insertSort.data(), selectSort.size(), sf::LinesStrip);
        window.draw(shellSort.data(), selectSort.size(), sf::LinesStrip);
        for (auto& txt: texts) window.draw(txt);
        window.display();
    }

    return 0;
}