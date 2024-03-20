#include <iostream>
#include <glm/glm.hpp>
#include <memory>
//Геометричеcкие алгоритмы на плоскости (Боресков - Компьютерная графика)
class GeomAgloInPlane
{
    static constexpr float EPS = 0.001;
    enum Belong
    {
        START  = 0, LEFT   = 1, RIGHT  = 2, END    = 3, BEHIND = 4, BEYOND = 5, BETWEEN= 6
    };

public:
    //Определение положения точки относительно прямой или отрезка
    Belong classify ( const glm::vec2& a, const glm::vec2& b, const glm::vec2& p )
    {
        glm::vec2 a2b = b - a;
        glm::vec2 a2p = p - a;

        float area = a2b.x*a2p.y - a2p.x*a2b.y;
        if ( area > EPS )
            return LEFT;
        if ( area < -EPS )
            return RIGHT;
        if ( glm::length ( p - a ) < EPS )
            return START;
        if ( glm::length ( p - b ) < EPS )
            return END;
        if ((a2b.x*a2p.x < 0) || (a2b.y*a2p.y < 0))
            return BEHIND;
        if ( glm::length(a2b) < glm::length(a2p) )
            return BEYOND;
        return BETWEEN;
    }
 //Вычисление площади многоугольника
    float signedArea ( const glm::vec2 p [], int n )
    {
        float sum = p[0].x * (p[1].y - p[n-1].y) +
                    p[n-1].x * (p[0].y - p[n-2].y);
        for ( int i = 1; i < n - 1; i++ )
            sum += p[i].x * (p[i+1].y - p[i-1].y);
        //return 0.5f * glm::abs(sum);
        //Отслеживаем знак, если минус, то вершины расположены по часовой стрелке.
        return 0.5f * (sum);
    }

    bool doLinesCoincide ( const glm::vec2& n1, float d1,
                         const glm::vec2& n2, float d2 )
    {
        if ( glm::dot ( n1 , n2 ) > 0 ) // считаем нормали единичными dot-выполняет скалярное прозведение векторов, получаем число
            return fabs ( d1 - d2 ) < EPS;
        else
            return fabs ( d1 + d2 ) < EPS;
    }
    bool findLineIntersection ( const glm::vec2& n1, float d1,
                              const glm::vec2& n2, float d2,
                              glm::vec2& p )
    {
        const float
            det = n1.x * n2.y - n1.y * n2.x;
        if ( fabs ( det ) < EPS )
            return doLinesCoincide ( n1, d1, n2, d2 );
        p.x = (d2*n1.y - d1*n2.y)/det;
        p.y = (d1*n2.x - d2*n1.x)/det;
        return true;
    }

};

int main()
{
    auto obj = std::make_unique<GeomAgloInPlane>();
    //Определение положения точки относительно прямой или отрезка
    glm::vec2 a(0,0);
    glm::vec2 b(100,100);
    glm::vec2 p(40,80);
    //https://your-online.ru/math-calculators/land-plot-area-coordinates
    //Вычисление площади многоугольника (Для тестовых координат: 12.)
    glm::vec2 arrayData[6] {glm::vec2(1.,1.), glm::vec2(0.,2.), glm::vec2(2.,4.),
                            glm::vec2(5.,3.),glm::vec2(6.,2.), glm::vec2(5.,1.)};

    std::cout << obj->signedArea(arrayData, std::size(arrayData)) <<std::endl;

    glm::vec2 bData[4] = {glm::vec2(0.,0.), glm::vec2(5.,0.),
                          glm::vec2(5.,5.), glm::vec2(0.,5.) };
    std::cout << "Плащадь многоугольника:" <<obj->signedArea(bData, 4) <<std::endl;

    //Пересечение прямых
    //Уравнение прямой А: 5x - 2y -16 = 0;
    //Уравнение прямой В: 2x - 5y -19 = 0;
    //точка М0 с координатами (2, -3) является ли точкой пересечения?

    float x1 = 5/(sqrt(29)); //5/sqrt(25+4)
    float y1 = -2/(sqrt(29)); //-2/sqrt(25+4)
    float d1 = -16/(sqrt(29)); //-16/sqrt(25+4)


    float x2 = 2/(sqrt(29));
    float y2 = -5/(sqrt(29));
    float d2 = -19/(sqrt(29));
    glm::vec2 point;
    auto flag = obj->findLineIntersection (glm::vec2(x1,y1),d1, glm::vec2(x2,y2),d2,point);
    if (flag == true)
    {
        std::cout << "Прямые пересекаются:" << std::endl;
        std::cout << point.x <<" "<< point.y <<std::endl;
    }

    return 0;
}
