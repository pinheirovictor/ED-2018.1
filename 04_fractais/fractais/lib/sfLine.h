#ifndef SFLINE_H
#define SFLINE_H

#include <SFML/Graphics.hpp>

class sfLine : public sf::Drawable
{
public:
    sfLine(const sf::Vector2f& point1, const sf::Vector2f& point2,
           float thickness = 1, sf::Color color = sf::Color::Red):
        _begin(point1), _end(point2), _color(color), _thickness(thickness)
    {
        updateVertices();
    }

    sf::Vector2f getBegin(){
        return _begin;
    }

    sf::Vector2f getEnd(){
        return _end;
    }

    float getThickness(){
        return _thickness;
    }

    sf::Color getColor(){
        return _color;
    }


    void setColor(sf::Color color){
        this->_color = color;
        updateVertices();
    }

    void setEnd(sf::Vector2f end){
        this->_end = end;
        updateVertices();
    }
    void setBegin(sf::Vector2f begin){
        this->_begin = begin;
        updateVertices();
    }
    void setThickness(float thickness){
        _thickness = thickness;
        updateVertices();
    }


    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        (void)states;
        target.draw(_vertices,4,sf::Quads);
    }


private:
    sf::Vector2f _begin;
    sf::Vector2f _end;
    sf::Vertex _vertices[4];
    sf::Color _color;
    float _thickness;


    void updateVertices(){
        sf::Vector2f direction = _end - _begin;
        sf::Vector2f unitDirection = direction/std::sqrt(direction.x*direction.x+direction.y*direction.y);
        sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

        sf::Vector2f offset = (_thickness/2.f)*unitPerpendicular;

        _vertices[0].position = _begin + offset;
        _vertices[1].position = _end + offset;
        _vertices[2].position = _end - offset;
        _vertices[3].position = _begin - offset;

        for (int i=0; i<4; ++i)
            _vertices[i].color = _color;
    }
};
#endif // SFLINE_H
