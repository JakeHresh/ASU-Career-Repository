// The below comments explain what this program does. My insertion
// is here to indicate that my changes, which include timer code and
// a banner image, will indicate what changes I made.
// - Jacob Hreshchyshyn
//===================================================================
// mandelbrot.cpp
//
// This is a simple program that computes the mandelbrot set on a
// range from x = [-1,1] y = [-1, 1]
//
// Copyright � 2020, Arizona State University
// This document may not be copied or distributed except for the 
// purposes described in the assignment instructions within the 
// course shell. Posting the document, derivative works, in full or 
// in part, on web sites other than that used by its associated 
// course is expressly prohibited without the written consent of 
// the author.
#include <fstream>
#include <iostream>
#include <chrono>

using namespace std;

//===================================================================
// calcatePoint()
//
// Calculate a single point in the Mandelbrot set and return the
// value.  The Mandelbrot calculation iterates the following 
// equation until either a specified number of iterations is met
// (limit), or the value diverges beyond a magnitude of 2 from 
// the complex plane-origin.
//     Z(n+1) = Z(n)*Z(n) + C
// Z and C are complex numbers, where C is the location of the point.
//
// Parameters:
//    xpos, ypos - the location of the point in the complex plane
//    limit - the maximum number of iterations to run when checking
//       for divergence.
// Returns:
//    the number of iterations before divergence (or limit)
long calculatePoint(double xpos, double ypos, long limit) {
    double zx = 0.0;
    double zy = 0.0;
    long count = 0;
    while (count < limit) {
        // note that z(n)*z(n) =
        //   (zreal(n)*zrean(n) - (zimaginary(n)*zimaginary(n)) +
        //   2.0*i*(zreal(n)*zimaginary(n))
        double zx_next = zx * zx - zy * zy + xpos;
        double zy_next = 2 * zx * zy + ypos;
        zx = zx_next;
        zy = zy_next;
        if (zx * zx + zy * zy > 4.0) break;
        count++;
    }
    return count;
}

//===================================================================
// calcateImage()
//
// Calculate all the points in a Mandelbrot image using the given
// input parameters.
//
// Parameters:
//   image - the array to place the image in
//   imagewidth - the width (and height) of the image (in points)
//   centerx, centery - the center of the image in the complex plane
//   zoom - the width of the image in the complex plane
//   limit - the maximum iterations to check at each point
// Returns:
//   void
void calculateImage(long image[], long imagewidth,
    double centerx, double centery, double zoom, unsigned long limit) {
    double resolution = zoom / (double)imagewidth;
    // The below line gets the initial time before the points are calculated.
    auto begin = chrono::high_resolution_clock::now();
    for (long row = 0; row < imagewidth; row++) {
        double y = centery + resolution * ((double)row) - zoom / 2.0;
        for (long column = 0; column < imagewidth; column++) {
            double x = centerx + resolution * ((double)column) - zoom / 2.0;
            image[row*imagewidth+column] = calculatePoint(x, y, limit);
        }
    }
    // The below three lines are used first to get the time after the points are
    // calculated, then find the difference between start and end time to find the
    // duration, then print that duration
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - begin;
    cout << duration.count() << " seconds"<< endl;
}

//===================================================================
// main()
//
// the main program entry point.
//
// Returns:
//   always returns 0;
int main()
{
    unsigned long width = 1000;
    // insert banner message here that displays your name
    // and the course number
    // The below two lines represent my banner for this project.
    cout << "------------ WELCOME TO MANDELBROT SET BENCHMARKING! ------------\n";
    cout << "------------- Jacob Hreshchyshyn SER450 - Project 2 -------------\n\n";
    // allocate memory for the image
    long* image = new long[(unsigned long)(width * width)];
    
    // call routine to create the image
    cout << "calculating the image" << endl;
    calculateImage(image, width, 0.0, 0.0, 2.0, 10000);

    // output the image to a file
    cout << "writing the image file" << endl;
    ofstream ofile;
    ofile.open("outfile.csv");
    for (unsigned long row = 0;row < width;row++) {
        for (unsigned long column=0;column<width;column++) {
            ofile << image[row * width + column];
            if (column + 1 < width) ofile << ",";
        }
        ofile << endl;
    }
    ofile.close();

    // dealocate memory from the image
    delete[] image;
    cout << "done" << endl;
    return 0;
}
