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



    Colour *planeColour = new Colour(1, 1, 0);
    Point3D *p1_plane = new Point3D(-10, -10, 3);
    Point3D *p2_plane = new Point3D(10, -10, 3);
    Point3D *p3_plane = new Point3D(10, 10, 100);




    Colour *circColour = new Colour(0, 1, 0);
    //Colour *k_d = new Colour(1, 1, 1);
    Colour *k_a = new Colour(0, 0, 0);
    Colour *k_d = new Colour(0.5, 0.5, 0.5);

    Colour *k_s = new Colour(0.6, 0.6 ,0.6);

    Colour *k_reflect = new Colour(0.1, 0.1, 0.1);
    double exp = 5;
    Point3D *circ_center = new Point3D(0, 0, 4);
    Material *circ_Material = new Material(* circColour, *k_a,  *k_d, *k_s,exp, *k_reflect);
    Circle *circ = new Circle( *circ_center, *circColour, 5, *circ_Material);
    //scene->objects.push_back(circ);


    Material *c_plane = new Material(*planeColour, *k_a, *k_d, *k_s, exp, *k_reflect);
    Plane *plane = new Plane(*p1_plane, *p2_plane, *p3_plane, *c_plane);
    //scene->objects.push_back(plane);


    //Triangle code
    Point3D *p3 = new Point3D(10, 10, 4);
    Point3D *p2 = new Point3D( 10,  0, 4);
    Point3D *p1 = new Point3D(0, 0, 4);
    Colour *pColour = new Colour(0, 0, 1);
    Material *p_Material = new Material(*pColour, *k_a, *k_d, *k_s, exp, *k_reflect);
    Pyriamid *p = new Pyriamid(*p1,*p2, *p3, *p_Material);
    scene->objects.push_back(p);


    Point3D *tri2_p1 = new Point3D(10, 10, 4);
    Point3D *tri2_p2 = new Point3D(0, 10, 4);
    Point3D *tri2_p3 = new Point3D(0, 0, 4);

    Pyriamid *pry_2 = new Pyriamid(*tri2_p1, *tri2_p2, *tri2_p3, *p_Material);
    scene->objects.push_back(pry_2);


    Point3D *circ2_center = new Point3D(4, 0, 16);
    Colour  *circ2_color = new Colour(1, 0, 0);
    Material *circ2_Material = new Material(*circ2_color, *k_a, *k_d, *k_s, exp, *k_reflect);
    Circle *circ2 = new Circle(*circ2_center, *circ2_color, 5, *circ2_Material );
    //scene->objects.push_back(circ2);

    Point3D *eye = new Point3D(0, 0,-8);
    Point3D *lightLoc = new Point3D(0, 0, -8);
    Point3D *light2Loc = new Point3D(-4, 0, -16);
    Point3D *light3Loc = new Point3D(0, 0, -8);
    Colour *Ia = new Colour(1, 1, 1);
    Colour *Id = new Colour(0.9, 0.9, 0.9);
    //Colour *Id = new Colour(0.8, 0.1,0.8);
    Colour *Is = new Colour(0.5, 0.5, 0.5);
    Light *light = new Light(*lightLoc, *Ia, *Id, *Is );
    Light *light2 = new Light(*light2Loc, *Ia, *Id, *Is);
    Light *light3 = new Light(*light3Loc, *Ia, *Id, *Is);
    //Multiple light code
    scene->lights.push_back(light);
    //scene->lights.push_back(light2);

    //scene->lights.push_back(light3);

    scene->eye = eye;
    scene->max = 0;
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



	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
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
            //Ray *ray = new Ray(&p, &d);
            //Ray * ray2 = new Ray(*p, d);

            /*
            if (scene->doesHit(*eye, d)){

                Colour c = scene->trace(*eye, d, 0 );

                r = c.R();
                g = c.G();
                b = c.B();

                image.setPixel(x, y,
                    qRgb(r * 255, g * 255, b * 255));

                /*
                double yNext = ((double)y -1)/((double)(height - 1));

                Point3D neighbour = *P1 + x_x * (*P2 - *P1) + yNext * (*P3 - *P1);


                    for (int i = 0; i < 10; i++){
                        y--;
                        yNext = ((double)y)/((double)(height - 1));
                        neighbour = *P1 + x_x * (*P2 - *P1) + yNext * (*P3 - *P1);
                        cout << "Y is "<< y << "\n";
                        if (scene->doesHit(neighbour, *eye - neighbour)){
                           continue;
                        } else {
                            printf("Toon shading");
                            r = 0.0;
                            g = 0.0;
                            b = 0.0;

                            image.setPixel(x, y,
                                qRgb(r * 255, g * 255, b * 255));

                        }

                    }

                y +=10;

            } else {
                image.setPixel(x, y,
                    qRgb(r * 255, g * 255, b * 255));

            }
        */





            /*
            if (!prev){
                if (scene->intersect(*eye, d)){
                    r = 1.0;
                    g = 1.0;
                    b = 1.0;
                    prev = true;
                }
            } else if (scene->intersect(*eye, d)){
                prev = true;
                r = 1.0;
                g = 1.0;
                b = 1.0;
                image.setPixel(x, y,
                    qRgb(r * 255, g * 255, b * 255));
            } else {
                image.setPixel(x, y,
                    qRgb(r * 255, g * 255, b * 255));
                prev = false;
            }

            if (prev && !scene->intersect(*eye,d)){
                if ((x + 5) < width){
                    for (int i = 0; i < 5; i++){
                        r = 1.0;
                        g = 1.0;
                        b = 1.0;
                        image.setPixel(x, y,
                            qRgb(r * 255, g * 255, b * 255));
                        x++;
                    }

                }
            }*/

            //Comment this back in once toon shading has been implented


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
    image.save("Square.png");
    printf("Created the file \n");
	
	// application successfully returned
	return 0;
}
