#include <stdio.h>

//define PI
const double PI = 3.14;


//declare shape virtual table to use it
typedef struct ShapeVtable ShapeVtable;


typedef struct Shape
{
    //virtual table pointer to use it
    ShapeVtable* vtable;
} Shape;

struct ShapeVtable
{
    //function pointers for every function should be in Shape class
    double (*ShapeGetArea)(Shape*);
    void (*ShapePrintInfo)(Shape*);
    void (*ShapeDestroy)(Shape*);
};

//call the desired GetArea through the virtual table
double GetArea(Shape* shape)
{
    return shape->vtable->ShapeGetArea(shape);
}

//call the desired printInfo through the virtual table
void PrintInfo(Shape* shape)
{
    shape->vtable->ShapePrintInfo(shape);
}

////call the desired Destroy(Destructor) through the virtual table
void Destroy(Shape* shape)
{
    shape->vtable->ShapeDestroy(shape);
}

//Child Class Circle
typedef struct Circle
{
    //inheritance simulation
    Shape parent;
    //radius of the circle
    int r;
} Circle;

//actual implementation of GetArea for Circle
double CircleGetArea(Circle* circle)
{
    return 2*PI*circle->r;
}

//actual implementation of PrintInfo for Circle
void CirclePrintInfo(Circle* circle)
{
    printf("Circle Radius = %d\n",circle->r);
}

//actual implementation of destructor for Circle
void CircleDestroy(Circle* circle)
{
    //empty
}

//cast circle functions to match prototype of shape functions
ShapeVtable circleVtable =
{
    (double (*) (Shape*)) CircleGetArea,
    (void (*) (Shape*)) CirclePrintInfo,
    (void (*) (Shape*)) CircleDestroy
};

//initialize circle
void CircleInitialize(Circle* circle, int r)
{
    circle->parent.vtable = &circleVtable;
    circle->r = r;
}


//Child class Rectangle
typedef struct Rectangle
{
    //inheritance simulation
    Shape parent;
    int width, height;
} Rectangle;

//actual implementation of GetArea for Rectangle
double RectangleGetArea(Rectangle* rect)
{
    return (rect->width)*(rect->height);
}

//actual implementation of PrintInfo for Rectangle
void RectanglePrintInfo(Rectangle* rect)
{
    printf("Rectangle Width = %d, Height = %d\n", rect->width, rect->height);
}

//actual implementation of Destructor for Rectangle
void RectangleDestroy(Rectangle* rect)
{
    //empty
}


//cast rectangle functions to match prototype of shape functions
ShapeVtable rectangleVtable =
{
    (double (*) (Shape*)) RectangleGetArea,
    (void (*) (Shape*)) RectanglePrintInfo,
    (void (*) (Shape*)) RectangleDestroy
};

//initialize rectangle data members
void RectangleInitialize(Rectangle* rect, int w, int h)
{
    rect->parent.vtable = &rectangleVtable;
    rect->width = w;
    rect->height = h;
}


//Ellipse Child
typedef struct Ellipse
{
    Shape parent;
    //major & minor axis
    int A, B;
} Ellipse;


//actual implementation of GetArea for Ellipse
double EllipseGetArea(Ellipse* elli)
{
    return (elli->A)*(elli->B)*PI;
}

//actual implementation of PrintInfo for Ellipse
void EllipsePrintInfo(Ellipse* elli)
{
    printf("Ellipse A = %d, B = %d\n", elli->A, elli->B);
}

//actual implementation of Destructor for Ellipse
void EllipseDestroy(Ellipse* elli)
{
    //empty
}

//cast ellipse functions to match prototype of shape functions and save it as ellipse virtual table
ShapeVtable ellipseVtable =
{
    (double (*) (Shape*)) EllipseGetArea,
    (void (*) (Shape*)) EllipsePrintInfo,
    (void (*) (Shape*)) EllipseDestroy
};

//initialize ellipse data members
void EllipseInitialize(Ellipse* elli, int a, int b)
{
    elli->parent.vtable = &ellipseVtable;
    elli->A = a;
    elli->B = b;
}

int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10
    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5
    Ellipse ellipse;
    EllipseInitialize(&ellipse, 10, 12); // ellipse with radius 10, 12
    Shape* shapes[3];
    shapes[0]=(Shape*)&circle ;
    shapes[1]=(Shape*)&rectangle ;
    shapes[2]=(Shape*)&ellipse ;
    double total_area=0;
    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
        PrintInfo(shapes[i]); // prints the radius if circle, width and height if rectangle, ... etc
    }

    printf("total area = %.2lf\n", total_area); // check if the value is correct
    return 0;
}
