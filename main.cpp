#include <QImage>
#include <QColor>
#include <QApplication>
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

    QTextStream cout(stdout);

	// image width and height
	// TODO: prompt user on command line for dimensions
    double width = 400;
    double height = 400;

	// create new image
	QImage image(width, height, QImage::Format_RGB32);

    Colour * bgColour = new Colour(0, 0, 0);
    Scene * scene = new Scene(*bgColour, 5);
    Colour *circColour = new Colour(0, 1, 0);
    //Colour *k_d = new Colour(1, 1, 1);
    Colour *k_a = new Colour(0, 0, 0);
    Colour *k_d = new Colour(0.5, 0.5, 0.5);

    Colour *k_s = new Colour(0.6, 0.6 ,0.6);

    Colour *k_reflect = new Colour(1, 1, 1);
    double exp = 0.25;
    Point3D *circ_center = new Point3D(-4, 0, 4);
    Material *circ_Material = new Material(* circColour, *k_a,  *k_d, *k_s,exp, *k_reflect);
    Circle *circ = new Circle( *circ_center, *circColour, 3, *circ_Material);
    scene->objects.push_back(circ);


    Point3D *circ2_center = new Point3D(4, 0, 4);
    Colour  *circ2_color = new Colour(1, 0, 0);
    Material *circ2_Material = new Material(*circ2_color, *k_a, *k_d, *k_s, exp, *k_reflect);
    Circle *circ2 = new Circle(*circ2_center, *circ2_color, 3, *circ2_Material );
    scene->objects.push_back(circ2);

    Point3D *eye = new Point3D(0, 0,-8);
    Point3D *lightLoc = new Point3D(0, 0, -8);
    Point3D *light2Loc = new Point3D(-4, 0, -4);
    Point3D *light3Loc = new Point3D(0, 0, -4);
    Colour *Ia = new Colour(1, 1, 1);
    Colour *Id = new Colour(0.9, 0.9, 0.9);
    //Colour *Id = new Colour(0.8, 0.1,0.8);
    Colour *Is = new Colour(0.5, 0.5, 0.5);
    Light *light = new Light(*lightLoc, *Ia, *Id, *Is );
    Light *light2 = new Light(*light2Loc, *Ia, *Id, *Is);
    Light *light3 = new Light(*light3Loc, *Ia, *Id, *Is);
    //Multiple light code
    //scene->lights.push_back(light);
    //scene->lights.push_back(light2);

    scene->lights.push_back(light3);

    scene->eye = eye;
    scene->max = 40;
    printf("Starting the raytracer");
	// iterate over the pixels & set colour values
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
            double r = 0.0;
            double g = 0.0;
            double b = 0.0;

            Point3D *P1 = new Point3D(-10, 10, 0);
            Point3D *P2 = new Point3D(10, 10, 0);
            Point3D *P3 = new Point3D(-10, -10, 0);

            double x_x = ((double)x)/((double)(width - 1));
            double y_y = ((double)y)/((double)(height - 1));
            Point3D e = *P1 + x_x * (*P2 - *P1) + y_y * (*P3 - *P1);
            //Point3D *p = new Point3D( x/(width - 1),  y/(height -1) , 1); //Point in world coordinates
			// compute rgb values
            // TODO: replace with values from ray tracing

            //Point3D *p= new Point3D(x, y, 0);
            Vector3D d =  *eye - e ;
            d.normalize();
            //Ray *ray = new Ray(&p, &d);
            //Ray * ray2 = new Ray(*p, d);

            Colour c = scene->trace(*eye, d, 0 );

            r = c.R();
            g = c.G();
            b = c.B();

            //Point3D center = new Point3D(5, 5,0);

            //Circle circ = new Circle(center,(float) 30.0);



            /*
            if (x > width / 2 && y < height / 2) r = 1.0;
            if (x > width/4  && y < height / 4 ) r = 0.5;
            if (x > width/8  && y < height / 8 ) r = 0.25;
            if (x < width / 2 && y > height / 2) g = 1.0;
            if (x < width / 4 && y > height / 4) g = 0.5;
            if (x < width / 8 && y > height / 8) g = 0.25;
            if (x > width / 2 && y > height / 2) b = 1.0;
            if (x > width / 4 && y > height / 4) b = 0.5;
            if (x > width / 8 && y > height / 8) b = 0.25;
            */

            /*
            if ( x>= 100 && y>= 100){
                r, g, b = 0.5;
                r = 1.0;

            }*/
			// set pixel value
			image.setPixel(x, y, 
				qRgb(r * 255, g * 255, b * 255));
            //QTextStream cout(stdout);
            //delete &c;
            //cout << "The x value is " << x << "The y value is " << y << "\n";
		}
	}


	// save to file
	// TODO: prompt user on command line for output name
    image.save("output7.png");
    printf("Created the file \n");
	
	// application successfully returned
	return 0;
}
