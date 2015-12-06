#include "raytracing.h"

//Josh code reccomendations
//Dec 1 revised josh reccomendations
/*bool trace_ray(pt o, vec v, &col, depth) {
 *
 * //Find closest intersection
 *
 * obj = NULL;
 * t_min = infinity;
 * n_min = (0, 0, 0);
 * for every object {
 *
 *      t = object.intersect(p , v);
 *      if ( o < t < t_min) {
 *          tmin = t;
 *          obj = object;
 *          n_min = n;
 *  }
 * }
 *
 *  p = o + t_min * v;
 *
 * //Phong Shading returns a col
 *      p = o + tmin * v;
 *      //Phong shading
 *      col = obj.kd * obj.Ia;
 *      for (every light l) {
 *          if ( p in shadow) {
 *              continue;
 *          }
 *          l = lt.p - p;
 *          col += max(n * l, 0) * obj.kd * obj.Id;
 *
 *
 * r = v - 2(n * v) * n;
 * if ( depth < max_depth) {
 *     trace_ray(p, r, &r_col);
 *     col += k_reflect * r_col;
 * }
 *
 *
 *
 *
 *
 * /

/*
 *
 *
 * bool trace_ray(Point o, Vector v,  Colour &rgb, int depth) {
 *      //Found closest intersection
 *      if (not intersection)
 *          return false
 *      know p, n - point of intersection/normal
 *      know l - light vector
 *      r = -l + 2(l * n)  *n;
 *      for (each light {
 *          if  intersection_test(p, light.pos)
 *              continue;
 *          if ( ! intersection_test(p. light.pos)) {
 *              col += obj.I_d * obj * k_d * max(n * light.l, 0);
 *              col += diffuse;//I think the above may be the diffuse
 *              col += specular;
 *          }
 *   }
 *      col perfect_reflection
 *      //Might wanna modify below
 *      col = object.I_a * object.k_a;
 *      col += object.k_d * max(n.l, 0) * object.I_d;
 *      col += object.k_s * max(r.v, 0)^(object.p) * object.I_s;
 *
 *
 *      return true;
 *


/*
Intersect Scene::intersect(Ray *r)
{

}


Ray::Ray()
{
    p = new Point3D;
    d = new Vector3D;
}
*/


/*
Colour Scene::trace(Ray *r)
{
   Colour local, reflected, transmitted;
   Point3D q;

   if (objects.size() <= 0){
       //printf("There is no objects...");
       return Colour(1.0, 1.0, 1.0);
   }

   Object *obj = objects[0];
   Intersect inter = intersect(r);

   //obj->intersect(r);


   //for (int i = 0; i < objects.size(); i++){
       //Object *obj = objects[i];
       //float t = obj->intersect(r);


   //}
   //Vector3D n, r, t;




    //return trace(Ray.p, Ray.d, )
}*/

Colour Scene::trace(Point3D p, Vector3D d, int depth)
{


   Colour local, reflected, transmitted;
   Point3D q; //intersection point
   Vector3D n, r, t;    //normal, reflection, transmission

   d.normalize();
   double t_min = std::numeric_limits<float>::max();
   int obj_toDraw = 80;
   if (depth > max) return *bgColour;
   Object *obj;
   for (int i = 0; i <objects.size(); i++){
   Object * obj = objects[i];
   //Ray * ray = new Ray( p , d);


   double t = (double) obj->intersect(p, d);



   if (t != std::numeric_limits<float>::max() ){
       if (t < t_min){
           t_min = t;
           obj_toDraw = i;
       }
    }

   }
   if (t_min == std::numeric_limits<float>::max()){
       return *bgColour;
   }
   q = p + (t_min - 0.01) * d;//point that the ray intersected with
   n = (objects[obj_toDraw]->getOrigin() - q);
   //n =  (q - objects[obj_toDraw]->getOrigin());
  // n = 1.0 * (q - Point3D(0, 0, 0)); //hacky way to copy q

   n.normalize();
   //Intersect inter = obj->intersect(ray);
   //q = intersect(p, d, status);
   //if (status == noHit) return bgColour;
   //Might want to flip d

   Vector3D l = (q - p);
   r = -l + 2 * (l.dot(n)) * n ;
   r.normalize();
   //t = transmit(q, n);
   this->view_pos = &p;
   Material objectMaterial = objects[obj_toDraw]->getC();
   local = phong(q , n ,objectMaterial);
   reflected = * objectMaterial.k_reflect *trace(q, r, depth + 1);
   //transmitted = trace(q, t, depth + 1);
   //Clamp RGB to 0 or 1

   Colour ret = local + reflected;

   //Colour ret = Colour(t_min/13.7, t_min/13.7, t_min/13.7);
   QTextStream cout(stdout);

   cout << obj_toDraw << "\n";
   ret.clamp();
  // return *bgColour;


   return ret;

   //return local + reflected + transmitted;

}

Intersect Scene::intersect(Ray *r)
{




}

Scene::Scene()
{

}


float Circle::intersect(Point3D p, Vector3D D)
{

    //Point3D *p = r->p;
    //Vector3D *D = r->d;
    Vector3D d_1 = p - *center;


    double a = 1;
    double b = 2 * (D.dot(d_1));
    double c = (d_1.dot(d_1)) - (radius * radius);

    double * roots = new double[2];
    int num_roots = quadraticRoots( a, b, c,  roots);

    QTextStream cout(stdout);
    //Intersect * inter;
    if (num_roots == 0){
        //printf("No intersection  :(");
       // inter = new Intersect(false);
        return std::numeric_limits<float>::max();
        //return inter;
        //Intersect inter = new Intersect(0, false);
    } else if (num_roots == 1){
        //inter = new Intersect(true);
        return roots[0];
        //return inter;
    } else {
        if (roots[0] < roots[1]){
            return roots[0];
        } else {
            return roots[1];
        }
    }


}

Colour Circle::getColour()
{
    return * circ_colour;

}

Point3D Circle::getOrigin()
{
    return *origin;

}

Material Circle::getC()
{
    return * this->C;

}


Colour Scene::phong(Point3D p, Vector3D n, Material C)
{

    QTextStream cout(stdout);
    //double test = n.dot(Vector3D(0, 0, 0));

    //cout << "p is " << p[0] << " , " << p[1] << " , " << p[2] << "\n";
    //cout << test << "\n";

    //TODO add a global ambient
    Colour *ret = new Colour();
    Colour *ambient = new Colour();
    Colour *diffuse = new Colour();
    Colour *specular = new Colour();


    //Ambient
    *ambient = *C.ambient;

    //for each light
    for (int i = 0; i < lights.size(); i++)
    {
        Light *light = lights[i];
        //Vector3D shadowRay = ( p - *light->loc);
        Vector3D shadowRay = ( * light->loc - p);
        shadowRay.normalize();


        if ( intersect(p, shadowRay)){

            cout << "Something hit" << "\n";

        //ObjectHit = interscect(shadowRay, p);
        //if nothing hit or if what we hit is beyond is beyond the light





        //Diffuse:clamp to prevent subratction if normal faces away Might be ambient
        Colour light_Id = * light->Id;

        *diffuse = (*C.k_d * *light->Id) * fmax(n.dot(shadowRay), 0);//max(n.dot(shadowRay), (double) 0);
        //Diffuse
        //Vector3D l = p - *light->loc;
        //l.normalize();
        //*ret = *ret + *C.k_d * *light->Id * fmax(n.dot(shadowRay), 0);
        //*ret = *ret + *C.k_d * *light->Id * fmax((*light->loc - p).dot(n), 0);
        //Specular
        Vector3D l = (*view_pos - p);
        l.normalize();
        Vector3D R = 2 * (n.dot(l)) * n - l;
        R.normalize();
        Vector3D V = *eye -p;
        V.normalize();

        *specular = (* C.k_s * *light->Is) * pow( fmax(R.dot(V),0), C.exp);
        *ret = *ret + *ambient + *diffuse + *specular;
        }
    }

    //Clamp colour between 0-1 (or 0 - 255) before return!

    //if (ret->R() < 0) ret = new Colour(0, ret->G(), ret->B());
    //cout << ret->B() << ret->G() << ret->B() << "\n";
    ret->clamp();
    return *ret;
}

bool Scene::intersect(Point3D p, Vector3D d)
{

    bool ret = false;
    for (int i = 0; i < objects.size(); i++){
     Object *obj = objects[i];
     double t = obj->intersect(p, d);

     if ( t > 0 && t < std::numeric_limits<float>::max()){

         ret = true;
     }

    }
    return ret;
}



Circle::~Circle()
{

}

/*
float Circle::intersect(Ray *r)
{

}
*/


float Object::intersect(Point3D p, Vector3D d)
{

}

Colour Object::getColour()
{

}

Material Object::getC()
{

}

Point3D Object::getOrigin()
{

}

float Pyriamid::intersect(Point3D p, Vector3D d)
{

    Point3D center = (1/3) * (*p1 + *p2 + *p3);
    Vector3D n = center - p;
    n.normalize();
    Point3D P;

    Vector3D temp_p = p - Point3D(0, 0, 0);
    double t = - (temp_p.dot(n))/(d.dot(n));

    //double t = -(p.dot())


    //Inside test!




    Vector3D V1_n = *p2 - *p1;
    Vector3D V2_n = *p3 - *p1;
    //Vector3D n = V1_n.cross(V2_n);
    n.normalize();

    //double t = -1 * (p + )
    Vector3D V1 = *p1 - p;
    Vector3D V2 = *p2 - p;
    Vector3D N = V1.cross(V2);
    N.normalize();

    double d1 = -1 * (p - Point3D(0, 0, 0)).dot(N);


}

Colour Pyriamid::getColour()
{

}

Point3D Pyriamid::getOrigin()
{

}

Material Pyriamid::getC()
{

}
