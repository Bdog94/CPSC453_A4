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
   int obj_toDraw = 0;
   if (depth > max) return *bgColour;
   for (int i = 0; i <objects.size(); i++){
   Object * obj = objects[i];
   //Ray * ray = new Ray( p , d);


   double t = (double) obj->intersect(p, d);


   //delete ray;
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
   q = p + t_min * d;//point that the ray intersected with
  // n = (objects[obj_toDraw]->getOrigin() - q);
   n =  (q - objects[obj_toDraw]->getOrigin());
  // n = 1.0 * (q - Point3D(0, 0, 0)); //hacky way to copy q

   n.normalize();
   //Intersect inter = obj->intersect(ray);
   //q = intersect(p, d, status);
   //if (status == noHit) return bgColour;
   r = -d + 2 * (d.dot(n)) * n ;
   //t = transmit(q, n);
   this->view_pos = &p;
   local = phong(q , n ,objects[obj_toDraw]->getC());
   //reflected = trace(q, r, depth + 1);
   //transmitted = trace(q, t, depth + 1);
   //Clamp RGB to 0 or 1

   //Colour &ret = local;
   Colour ret = Colour(t_min/13.7, t_min/13.7, t_min/13.7);
   QTextStream cout(stdout);
   //cout << t_min << "\n";
   //ret.clamp();
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
            //inter = new Intersect(true);
            cout << roots[0] << " 0< " << roots[1] << "\n";
            return roots[0];
        } else {
            //cout << roots[1];
            cout << roots[1] << " 1< " << roots[0] << "\n";
            //cout << (roots[0] - roots[1]) << "\n";
           // inter = new Intersect(true);
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

    //cout << "n is " << n[0] << " , " << n[1] << " , " << n[2] << "\n";
    //cout << test << "\n";

    //TODO add a global ambient
    Colour *ret = C.ambient;
    //for each light
    for (int i = 0; i < lights.size(); i++)
    {
        Light *light = lights[i];
        //Vector3D shadowRay = ( p - *light->loc);
        Vector3D shadowRay = ( * light->loc - p); //Might not be the right way..
        shadowRay.normalize();
        //ObjectHit = interscect(shadowRay, p);
        //if nothing hit or if what we hit is beyond is beyond the light

        //Ambient
        *ret = *C.ambient * *light->Ia;
        //Diffuse:clamp to prevent subratction if normal faces away Might be ambient
        Colour light_Id = * light->Id;

        *ret = *ret + *C.k_d * *light->Id * fmax(n.dot(shadowRay), 0);//max(n.dot(shadowRay), (double) 0);

        //Diffuse
        //Vector3D l = p - *light->loc;
        //l.normalize();
        //*ret = *ret + *C.k_d * *light->Id * fmax(n.dot(shadowRay), 0);
        //*ret = *ret + *C.k_d * *light->Id * fmax((*light->loc - p).dot(n), 0);
        //Specular
        Vector3D l = (*view_pos - p);
        Vector3D R = 2 * (n.dot(l)) * n - l;
        Vector3D V = *eye -p;
        //*ret =  *ret + * C.k_s * *light->Is * pow( fmax(R.dot(V),0), C.exp);

    }

    //Clamp colour between 0-1 (or 0 - 255) before return!

    //if (ret->R() < 0) ret = new Colour(0, ret->G(), ret->B());

    ret->clamp();
    return *ret;
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
    Vector3D V1_n = *p2 - *p1;
    Vector3D V2_n = *p3 - *p1;
    Vector3D n = V1_n.cross(V2_n);
    n.normalize();

    //double t = -1 * (p + )
    Vector3D V1 = *p1 - p;
    Vector3D V2 = *p2 - p;
    Vector3D N = V1.cross(V2);
    N.normalize();

    double d1 = -1 * (p - Point3D(0, 0, 0)).dot(N);


}
