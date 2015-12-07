#include <QImage>
#include <QColor>
#include <QApplication>
#include <QString>
#include <stdlib.h>
#include <algebra.h>
#include "raytracing.h"
#include <QTextStream>
int main(int argc, char *argv[])
{

    int i;
    // currently unused parameters
	Q_UNUSED(argc);
	Q_UNUSED(argv);
    double width = 200;
    double height = 200;

    double eyeX  = 0, eyeY = 0, eyeZ = -4;
    QTextStream qin(stdin);
    QTextStream qout(stdout);


    /*
    qout << "Enter the eyeX " <<endl;
    qin >> eyeX;

    qout << "Enter the eyeY " << endl;
    qin >> eyeY;

    qout << "Enter the eyeZ" << endl;
    qin >> eyeZ;

    qout << "Enter image width: " << endl;
    qin >> width;
    qout << "Enter image height: " << endl;
    qin >> height;
    */
	// image width and height


	// create new image
	QImage image(width, height, QImage::Format_RGB32);

    Colour * bgColour = new Colour(0.5, 0.5, 0.5);
    Scene * scene = new Scene(*bgColour, 5);



    Colour *planeColour = new Colour(1, 1, 0);
    Point3D *p1_plane = new Point3D(-10, -10, 3);
    Point3D *p2_plane = new Point3D(10, -10, 3);
    Point3D *p3_plane = new Point3D(10, 10, 100);




    Colour *circColour = new Colour(0, 0, 1);
    //Colour *k_d = new Colour(1, 1, 1);
    Colour *k_a = new Colour(0, 0, 0);
    Colour *k_d = new Colour(0.5, 0.5, 0.5);

    Colour *k_s = new Colour(0.6, 0.6 ,0.6);

    Colour *k_reflect = new Colour(0.3, 0.3, 0.3);
    double exp = 5;
    Point3D *circ_center = new Point3D(-4, 0, 8);
    Material *circ_Material = new Material(* circColour, *k_a,  *k_d, *k_s,exp, *k_reflect);
    Circle *circ = new Circle( *circ_center, *circColour, 6, *circ_Material);
    scene->objects.push_back(circ);


    Material *c_plane = new Material(*planeColour, *k_a, *k_d, *k_s, exp, *k_reflect);
    Plane *plane = new Plane(*p1_plane, *p2_plane, *p3_plane, *c_plane);
    //scene->objects.push_back(plane);


    //Triangle code
    Point3D *p3 = new Point3D(8, 8, 0);
    Point3D *p2 = new Point3D( -8,  8, 0);
    Point3D *p1 = new Point3D(8, 0, 0);
    Colour *pColour = new Colour(0.1, 0.1, 0.1);
    Material *p_Material = new Material(*pColour, *k_a, *k_d, *k_s, exp, *k_reflect);
    Pyriamid *p = new Pyriamid(*p1,*p2, *p3, *p_Material);
    scene->objects.push_back(p);


    Point3D *tri2_p1 = new Point3D(8, 0, 10);
    Point3D *tri2_p2 = new Point3D(-8, 0, 0);
    Point3D *tri2_p3 = new Point3D(-8, 8, 0);

    Pyriamid *pry_2 = new Pyriamid(*tri2_p1, *tri2_p2, *tri2_p3, *p_Material);
    //scene->objects.push_back(pry_2);


    Point3D *tri_floor_p1 = new Point3D(-10, -10, 0);
    Point3D *tri_floor_p2 = new Point3D(-10, -10, 10);
    Point3D *tri_floor_p3 = new Point3D(10, -10, 0);

    Pyriamid *floor1 = new Pyriamid(*tri_floor_p1, *tri_floor_p2, *tri_floor_p3, *p_Material);
    //scene->objects.push_back(floor1);

    Point3D *tri_floor2_p1 = new Point3D(10, -10, 0);
    Point3D *tri_floor2_p2 = new Point3D(10, -10, 10);
    Point3D *tri_floor2_p3 = new Point3D(-10, -10, 10);

    Pyriamid *floor2 = new Pyriamid(*tri_floor2_p1, *tri_floor2_p2, *tri_floor2_p3, *p_Material);
    //scene->objects.push_back(floor2);


    Point3D *circ2_center = new Point3D(0, 0, 20);
    Colour  *circ2_color = new Colour(1, 0, 0);
    Material *circ2_Material = new Material(*circ2_color, *k_a, *k_d, *k_s, exp, *k_reflect);
    Circle *circ2 = new Circle(*circ2_center, *circ2_color, 5, *circ2_Material );
   scene->objects.push_back(circ2);

    Point3D *eye = new Point3D(eyeX, eyeY,eyeZ);
    Point3D *lightLoc = new Point3D(0, 0, -8);
    Point3D *light2Loc = new Point3D(0, 40, 0);
    Point3D *topLightLoc = new Point3D(-40, -40, 0);
    Point3D *light3Loc = new Point3D(-40, 0, 0);
    Colour *Ia = new Colour(1, 1, 1);
    Colour *Id = new Colour(0.9, 0.9, 0.9);
    //Colour *Id = new Colour(0.8, 0.1,0.8);
    Colour *Is = new Colour(0.5, 0.5, 0.5);
    Light *light = new Light(*lightLoc, *Ia, *Id, *Is );
    Light *topLight = new Light(*topLightLoc, *Ia, *Id, *Is);
    Light *light2 = new Light(*light2Loc, *Ia, *Id, *Is);
    Light *light3 = new Light(*light3Loc, *Ia, *Id, *Is);
    //Multiple light code
    //scene->lights.push_back(light);
    //scene->lights.push_back(light2);
    //scene->lights.push_back(topLight);
    scene->lights.push_back(light3);

    //Scene set up stuff
    scene->eye = eye;
    scene->max = 0;
    scene->isNormalMode= true;

    bool prev = false;
    printf("Starting the raytracer");
	// iterate over the pixels & set colour values

    //Unit test code


    Point3D *P1 = new Point3D(-10, 10, 0);
    Point3D *P2 = new Point3D(10, 10, 0);
    Point3D *P3 = new Point3D(-10, -10, 0);

    double xHit = ((double) (width/2))/((double)(width -1));
    double yHit = ((double) (height/2))/((double)(height -1));

    Point3D hitPoint = *P1 + xHit * (*P2 - *P1) + yHit * (*P3 - *P1);
    Vector3D vecHit = *eye - hitPoint;
    if (scene->doesHit(hitPoint, vecHit)){
        printf("Hit test passed");
    }

    double xMiss = ((double) (0))/((double)(width -1));
    double yMiss= ((double) (0))/((double)(height -1));

    Point3D missPoint = *P1 + xMiss * (*P2 - *P1) + yMiss * (*P3 - *P1);
    Vector3D vecMiss = *eye - missPoint;

    if (!scene->doesHit(missPoint, vecMiss)){

        printf("Miss test passed");
    }



    bool isBlurryMode = false;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
            double delta = 0.002; //For anti aliasing

            if (isBlurryMode){
                delta = 0.3;
            }

            double r = 1.0;
            double g = 1.0;
            double b = 1.0;



            double x_x = ((double)x)/((double)(width - 1));
            double y_y = ((double)y)/((double)(height - 1));
            Point3D e = *P1 + x_x * (*P2 - *P1) + y_y * (*P3 - *P1);
            //Point3D *p = new Point3D( x/(width - 1),  y/(height -1) , 1); //Point in world coordinates
            // compute rgb values
            // TODO: replace with values from ray tracing

            //Point3D *p= new Point3D(x, y, 0);
            Vector3D d = *eye - e;
            d.normalize();

            Colour c = scene->trace(*eye, d, 0 );

            Point3D *eye2 = new Point3D((eyeX + delta), eyeY, eyeZ);
            d = *eye2 - e;

            Colour c2 = scene->trace(*eye2, d, 0);

            Point3D *eye3 = new Point3D(eyeX , (eyeY + delta), eyeZ);
            d = *eye3 - e;

            Colour c3 = scene->trace(*eye3, d, 0);

            Point3D *eye4 = new Point3D((eyeX + delta), (eyeY + delta), eyeZ);
            d = *eye4 - e;

            Colour c4 = scene->trace(*eye4, d, 0);

            Colour finalC = (c + c2 + c3 + c4) * Colour((double)1/4, (double)1/4, (double)1/4);





            r = finalC.R();
            g = finalC.G();
            b = finalC.B();


			// set pixel value


            image.setPixel(x, y,
                qRgb(r * 255, g * 255, b * 255));

            //QTextStream cout(stdout);
            //delete &c;
            //cout << "The x value is " << x << "The y value is " << y << "\n";
		}
	}
    /*
     QString filename;

    qout << "Enter the file name " << endl;
    qin >> filename;
    */
	// save to file
	// TODO: prompt user on command line for output name
    image.save("Triangles2.png");
    printf("Created the file \n");
	
	// application successfully returned
	return 0;
}
