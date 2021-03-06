#ifndef RAYTRACING_H
#define RAYTRACING_H
//#include <Material.h>
#include <algebra.h>
//#include <algebra.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include "polyroots.h"
#include <QTextStream>
#include <limits>
//class Point3D;
//class Vector3D;
//class Colour;
//class Polyroots;

class Intersect
{
public:
    double m_t;
    bool m_status;
    bool isEdge = false;
    Colour * colour;
    Intersect(double t,bool status){
        m_t = t;
        m_status = status;
    }
    Intersect(bool status){
        m_status = status;
        m_t = 0;
        //&colour  = new Colour()
    }



};
class Ray
{
public:

    Point3D * p;
    Vector3D * d;
    Ray(Point3D &p_p, Vector3D &p_d){
        p = &p_p;
        d = &p_d;
    }

};

class Material
{
public:

    //May want to make k a double/float
    Colour * ambient;
    Colour * k_a;
    Colour * k_d;
    Colour * k_s;
    double  exp;

    Colour * k_reflect;

    Material () {
        ambient = new Colour();
        k_d = new Colour();
        k_s = new Colour();
//        /exp = new Colour();
    }


    Material (Colour &ambient,Colour &k_a, Colour &k_d, Colour &k_s, double exp) {
        this->ambient = &ambient;
        this->k_a = &k_a;
        this->k_d = &k_d;
        this->k_s = &k_s;
        this->exp = exp;
        this->k_reflect = new Colour();

    }
    Material(Colour &ambient, Colour &k_a, Colour &k_d, Colour &k_s, double exp, Colour &k_reflect){
        this->ambient = &ambient;
        this->k_a = &k_a;
        this->k_d = &k_d;
        this->k_s = &k_s;
        this->exp = exp;
        this->k_reflect = &k_reflect;
    }

};

class Light
{
public:
    Point3D *loc;
    Colour *Ia;
    Colour *Id;
    Colour *Is;
    Light(){
        loc = new Point3D(0, 0,0);
        Id = new Colour();
        Is = new Colour();

    }
    Light(Point3D &loc,Colour &Ia, Colour &Id, Colour &Is){
        this->loc = &loc;
        this->Ia = &Ia;
        this->Id = &Id;
        this->Is = &Is;
    }

};
class Object
{
public:
    virtual Intersect intersect(Point3D p, Vector3D d);
    virtual Colour getColour();
    virtual Material getC();
    virtual Point3D getOrigin();
    virtual Vector3D getNormal(Point3D q);
    //Material * mat;

    Point3D *origin;
    Colour *colour;
    Material *C;
    Object(Point3D &p_origin, Colour &p_colour){

        origin = &p_origin;
        colour = &p_colour;
    }

    Object (){
        origin = new Point3D(0, 0, 0);
        colour = new Colour(0, 0.5, 0.5);
        C = new Material();
        //mat = new  Material();
    }



};

class Scene
{
public:
    Point3D * eye;
    Point3D * view_pos;
    Vector3D * d, * up;
    Point3D * imgMin, * imgMax;
    Colour *bgColour;
    int xPixels, yPixels;
    std:: vector <Light*> lights;
    std:: vector <Object*> objects;
    Colour trace(Ray * r);
    Colour trace(Point3D p, Vector3D d, int depth);
    Colour phong(Point3D, Vector3D n, Object &o);

    bool intersect(Point3D p, Vector3D d);
    bool doesHit(Point3D p, Vector3D d);

    bool isCel;
    bool isNormalMode;
    bool isInvertedMode;

    Intersect intersect(Ray *r);
    int max;
    Scene();
    Scene(Colour &p_bgColour, int max_depth){
        bgColour = &p_bgColour;
        max = max_depth;
   }


    //void addObject(Object *);


};


class Circle : public Object
{
public:
    Intersect intersect(Point3D p, Vector3D D);
    Point3D * center;
    Colour *circ_colour;
    float radius;
    Material *C;
    Colour getColour();
    Point3D getOrigin();
    Vector3D getNormal(Point3D q);
    Material getC();


    //using Object::Object;
    Circle (Point3D &p_center, Colour &p_colour, float p_raduis, Material &p_C){
        Object(p_center, p_colour);
        center = &p_center;
        circ_colour = &p_colour;
        radius = p_raduis;
        C = &p_C;
    }

    Circle(Point3D &origin, Colour &colour){
        Object(origin,colour);

    }

    ~Circle();
};
class Pyriamid : public Object
{
public:
    Intersect intersect(Point3D p, Vector3D d);
    Point3D *center;
    Colour *triColour;

    Colour getColour();
    Point3D getOrigin();
    Vector3D getNormal(Point3D q);
    Material getC();

    Point3D *p1;
    Point3D *p2;
    Point3D *p3;
    Material *C;

    Pyriamid(Point3D &p_p1, Point3D &p_p2, Point3D &p_p3, Material &p_C){

        p1 = &p_p1;
        p2 = &p_p2;
        p3 = &p_p3;
        C = &p_C;
    }

};
class Plane : public Object
{
public:
    Intersect intersect(Point3D p, Vector3D d);
    Colour *planeColour;

    Colour getColour();
    Point3D getOrigin();
    Vector3D getNormal(Point3D q);
    Material getC();

    Point3D *p1;
    Point3D *p2;
    Point3D *p3;
    Material *C;

    Plane(Point3D &p_p1, Point3D &p_p2, Point3D &p_p3, Material &p_C)
    {
        p1 = &p_p1;
        p2 = &p_p2;
        p3 = &p_p3;
        C = &p_C;

    }
};








#endif // RAYTRACING_H
