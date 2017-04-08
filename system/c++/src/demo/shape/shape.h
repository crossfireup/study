#ifndef _SHAPE_H
#define _SHAPE_H

class Shape {
    public:
        virtual Point center() const = 0;
        virtual void move(Point to) = 0;
        
        virtual void draw() const = 0;
        virtual void rotate(int angle) = 0;

        virtual ~Shape() {}
};

#endif /* _SHAPE_H */
