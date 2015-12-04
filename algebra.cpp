//---------------------------------------------------------------------------
//
// CPSC453 -- Introduction to Computer Graphics
// Assignment 2
//
// Classes and functions for manipulating points, vectors, matrices, 
// and colours.  You probably won't need to modify anything in these
// two files.
//
// Adapted from CS488 A2 University of Waterloo Computer Graphics Lab / 2003
//
//---------------------------------------------------------------------------

#include "algebra.h"

double Vector3D::normalize()
{
  double denom = 1.0;
  double x = (v_[0] > 0.0) ? v_[0] : -v_[0];
  double y = (v_[1] > 0.0) ? v_[1] : -v_[1];
  double z = (v_[2] > 0.0) ? v_[2] : -v_[2];

  if(x > y) {
    if(x > z) {
      if(1.0 + x > 1.0) {
        y = y / x;
        z = z / x;
        denom = 1.0 / (x * sqrt(1.0 + y*y + z*z));
      }
    } else { /* z > x > y */ 
      if(1.0 + z > 1.0) {
        y = y / z;
        x = x / z;
        denom = 1.0 / (z * sqrt(1.0 + y*y + x*x));
      }
    }
  } else {
    if(y > z) {
      if(1.0 + y > 1.0) {
        z = z / y;
        x = x / y;
        denom = 1.0 / (y * sqrt(1.0 + z*z + x*x));
      }
    } else { /* x < y < z */
      if(1.0 + z > 1.0) {
        y = y / z;
        x = x / z;
        denom = 1.0 / (z * sqrt(1.0 + y*y + x*x));
      }
    }
  }

  if(1.0 + x + y + z > 1.0) {
    v_[0] *= denom;
    v_[1] *= denom;
    v_[2] *= denom;
    return 1.0 / denom;
  }

  return 0.0;
}

/*
 * Define some helper functions for matrix inversion.
 */

static void swaprows(Matrix4x4& a, size_t r1, size_t r2)
{
  std::swap(a[r1][0], a[r2][0]);
  std::swap(a[r1][1], a[r2][1]);
  std::swap(a[r1][2], a[r2][2]);
  std::swap(a[r1][3], a[r2][3]);
}

static void dividerow(Matrix4x4& a, size_t r, double fac)
{
  a[r][0] /= fac;
  a[r][1] /= fac;
  a[r][2] /= fac;
  a[r][3] /= fac;
}

static void submultrow(Matrix4x4& a, size_t dest, size_t src, double fac)
{
  a[dest][0] -= fac * a[src][0];
  a[dest][1] -= fac * a[src][1];
  a[dest][2] -= fac * a[src][2];
  a[dest][3] -= fac * a[src][3];
}

/*
 * invertMatrix
 *
 * I lifted this code from the skeleton code of a raytracer assignment
 * from a different school.  I taught that course too, so I figured it
 * would be okay.
 */
Matrix4x4 Matrix4x4::invert() const
{
  /* The algorithm is plain old Gauss-Jordan elimination 
     with partial pivoting. */

  Matrix4x4 a(*this);
  Matrix4x4 ret;

  /* Loop over cols of a from left to right, 
     eliminating above and below diag */

  /* Find largest pivot in column j among rows j..3 */
  for(size_t j = 0; j < 4; ++j) { 
    size_t i1 = j; /* Row with largest pivot candidate */
    for(size_t i = j + 1; i < 4; ++i) {
      if(fabs(a[i][j]) > fabs(a[i1][j])) {
        i1 = i;
      }
    }

    /* Swap rows i1 and j in a and ret to put pivot on diagonal */
    swaprows(a, i1, j);
    swaprows(ret, i1, j);

    /* Scale row j to have a unit diagonal */
    if(a[j][j] == 0.0) {
      // Theoretically throw an exception.
      return ret;
    }

    dividerow(ret, j, a[j][j]);
    dividerow(a, j, a[j][j]);

    /* Eliminate off-diagonal elems in col j of a, doing identical 
       ops to b */
    for(size_t i = 0; i < 4; ++i) {
      if(i != j) {
        submultrow(ret, i, j, a[i][j]);
        submultrow(a, i, j, a[i][j]);
      }
    }
  }

  return ret;
}

Line3D::Line3D() { }

Line3D::Line3D(const Point3D &p1, Point3D &p2) : p1_(p1), p2_(p2) { }

Line3D::Line3D(const Line3D &other) : p1_(other.p1_), p2_(other.p2_) { }

Line3D::~Line3D() { }

Point3D &Line3D::getP1()
{
    return p1_;
}

Point3D &Line3D::getP2()
{
    return p2_;
}

void Point4D::homogenize()
{
    v_[0] = (v_[0]/v_[3]);
    v_[1] = (v_[1]/v_[3]);
    v_[2] = (v_[2]/v_[3]);
    v_[3] = 1.0;
}


Triangle::Triangle()
{
    verts_.push_back(Point3D(0,0,0));
    verts_.push_back(Point3D(0,100,0));
    verts_.push_back(Point3D(0,100,0));
    verts_.push_back(Point3D(100,0,0));
    verts_.push_back(Point3D(100,0,0));
    verts_.push_back(Point3D(0,0,0));
}

Triangle::~Triangle() { }

Matrix4x4 Triangle::getTrasform() const
{
    return this->transform_;
}

void Triangle::resetTransform()
{
    this->transform_ = Matrix4x4();
}

void Triangle::appendTransform(const Matrix4x4 &xform)
{
    this->transform_ = this->transform_ * xform;
}

std::vector<Line3D> Triangle::getLines()
{
    std::vector<Line3D> lines;

    for(std::vector<Point3D>::iterator it = verts_.begin(); it != verts_.end(); ++it)
    {
        Point3D p1 = *(it++), p2 = *it;
        lines.push_back(Line3D(p1,p2));
    }
    return lines;
}

Cube::Cube()
{



    //Begin back face
    verts_.push_back(Point3D(-1, -1, 1));
    verts_.push_back(Point3D(-1, 1, 1));

    verts_.push_back(Point3D(-1, -1, 1));
    verts_.push_back(Point3D(-1, 1, 1));

    verts_.push_back(Point3D(-1, 1, 1));
    verts_.push_back(Point3D(1, 1, 1));

    verts_.push_back(Point3D(1, 1, 1));
    verts_.push_back(Point3D(1, -1, 1));
    //End back face

    verts_.push_back(Point3D(-1, 1, 1));
    verts_.push_back(Point3D(-1, 1, -1));

    verts_.push_back(Point3D(-1, 1, -1));
    verts_.push_back(Point3D(1,  1, -1));

    verts_.push_back(Point3D(1, 1, -1));
    verts_.push_back(Point3D(1, 1, 1));

    //End bottom face

    verts_.push_back(Point3D(-1, 1, -1));
    verts_.push_back(Point3D(-1, -1, -1));

    verts_.push_back(Point3D(-1, -1, -1));
    verts_.push_back(Point3D(1, -1, -1));

    verts_.push_back(Point3D(1, -1, -1));
    verts_.push_back(Point3D(1, 1, -1));

    //end of back face

    verts_.push_back(Point3D(-1, -1, -1));
    verts_.push_back(Point3D(-1, -1, 1));

    verts_.push_back(Point3D(1, -1, -1));
    verts_.push_back(Point3D(1, -1, 1));
    //end of sides

    verts_.push_back(Point3D(1, -1, 1));
    verts_.push_back(Point3D(-1, -1, 1));



    //end of top








}

Cube::~Cube() { }

Matrix4x4 Cube::getTransform() const
{
    return this->transform_;
}

void Cube::resetTransform()
{
    this->transform_ = Matrix4x4();
}

void Cube::appendTransform(const Matrix4x4 &xform)
{
    this->transform_ = this->transform_ * xform;
}

std::vector<Line3D> Cube::getLines()
{
    std::vector<Line3D> lines;

    for(std::vector<Point3D>::iterator it = verts_.begin(); it != verts_.end(); ++it)
    {
        Point3D p1 = *(it++), p2 = *it;
        lines.push_back(Line3D(p1,p2));
    }
    return lines;
}

WorldGnomin::WorldGnomin()
{

    verts_.push_back(Point3D(0, 0, 0));
    verts_.push_back(Point3D(0.5, 0, 0));

    verts_.push_back(Point3D(0, 0  , 0));
    verts_.push_back(Point3D(0, 0.5, 0));

    verts_.push_back(Point3D(0, 0  , 0));
    verts_.push_back(Point3D(0, 0, 0.5));



}

std::vector<Line3D> WorldGnomin::getLines()
{
    std::vector<Line3D> lines;

    for(std::vector<Point3D>::iterator it = verts_.begin(); it != verts_.end(); ++it)
    {
        Point3D p1 = *(it++), p2 = *it;
        lines.push_back(Line3D(p1,p2));
    }
    return lines;
}

WorldGnomin::~WorldGnomin() { }

//Might be switched over to scene
/*
Colour Colour::trace(Point3D p, Vector3D, int depth)
{
   Colour local, reflected, transmitted;
   Point3D q; //intersection point
   Vector3D n, r, t;    //normal, reflection, transmission
   //if (depth > max) return bgColour;
   //q = intersect(p, d, status);
   //if (status == noHit) return bgColour;
   //n = normal(q);
   //r = reflect(q, n);
   //t = transmit(q, n);
   //local = phong(q, n, r); //shadows
   reflected = trace(q, r, depth + 1);
   transmitted = trace(q, t, depth + 1);
   //return local + reflected + transmitted;

}*/
/*
Colour Colour::phong(Point3D, Vector3D n, Material C)
{
   //Colour ret = C.ambient * GLOBAL_AMBIENT;
    //for each light
    {
        //shadowRay = (light -p).normalize;
        //ObjectHit = interscect(shadowRay, p);
        //if nothing hit or if what we hit is beyond is beyond the light
        {
            //Diffuse:clamp to prevent subratction if normal faces away
            //ret += C.kd * light.Id * max(n * shadowRay, 0);
            //Specular
            //Vector3D R = 2 * (n * shawowRay) * n - shadowRay;
            //Vector V = viewPos -p;
            //ret += C.ks * light.Is * pow(max(R * V, 0), C.exp);
        }
    }

    //Clamp colour between 0-1 (or 0 - 255) before return!

    //return ret;
}
*/


void Colour::clamp()
{
    if (r_ > 1) r_ = 1;
    if (g_ > 1) g_ = 1;
    if (b_ > 1) b_ = 1;
}
