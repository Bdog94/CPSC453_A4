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
    Colour *circColour = new Colour(0.35, 0.5, 0.5);
    //Colour *k_d = new Colour(1, 1, 1);
    Colour *k_a = new Colour(1, 1, 1);
    Colour *k_d = new Colour(0.0000001, 0.0000001 ,0.0000001);
    Colour *k_s = new Colour(0.000001, 0.000001 ,0.000001);
    double exp = 2;
    Point3D *circ_center = new Point3D(0, 0, 40);
    Material *circ_Material = new Material(* circColour, *k_a,  *k_d, *k_s,exp);
    Circle *circ = new Circle( *circ_center, *circColour, 0.5, *circ_Material);
    scene->objects.push_back(circ);


    Point3D *circ2_center = new Point3D(0.2, 0.2, 8);
    Colour  *circ2_color = new Colour(0.2, 0.1, 0.2);
    Material *circ2_Material = new Material(*circ2_color, *k_a, *k_d, *k_s, exp);
    Circle *circ2 = new Circle(*circ2_center, *circ2_color, 0.2, *circ2_Material );
    scene->objects.push_back(circ2);

    Point3D *eye = new Point3D(0, 0,-4);
    Colour *Ia = new Colour(1, 1, 1);
    Colour *Id = new Colour(1, 1, 1);
    //Colour *Id = new Colour(0.8, 0.1,0.8);
    Colour *Is = new Colour(1, 1, 1);
    Light *light = new Light(*eye, *Ia, *Id, *Is );
    scene->lights.push_back(light);
    scene->eye = eye;
    scene->max = 3;
    printf("Starting the raytracer");
	// iterate over the pixels & set colour values
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
            double r = 0.0;
            double g = 0.0;
            double b = 0.0;

            Point3D *P1 = new Point3D(-0.5, 0.5, 0);
            Point3D *P2 = new Point3D(0.5, 0.5, 0);
            Point3D *P3 = new Point3D(-0.5, -0.5, 0);

            Point3D e = *P1 + x/(width -1) * (*P2 - *P1) + y/(height - 1) * (*P3 - *P1);
            //Point3D *p = new Point3D( x/(width - 1),  y/(height -1) , 1); //Point in world coordinates
			// compute rgb values
            // TODO: replace with values from ray tracing

            //Point3D *p= new Point3D(x, y, 0);
            Vector3D d = e - *eye;
            d.normalize();
            //Ray *ray = new Ray(&p, &d);
            //Ray * ray2 = new Ray(*p, d);

            Colour c = scene->trace(*eye, d, -1 );

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
    image.save("output2.png");
    printf("Created the file \n");
	
	// application successfully returned
	return 0;
}
