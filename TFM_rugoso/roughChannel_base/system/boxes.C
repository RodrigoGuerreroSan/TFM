
// C++ script that generates a file 'boxes.txt' that contains the coordinates
// to 3D bars, of which heights follow a normal distribution
#include <iostream>
#include <fstream>
#include <random>
#include <math.h>
using namespace std;
int main()
{
const double d50=1; // mean grain diameter
const double c=3; // scaling factor
const double x=4; // streamwise domain size
const double z=2; // spanwise domain size
const double mean=0; // mean
const double sigma=0.5*d50; // standard deviation
double dx=c*d50; // streamwise spacing
double dz=c*d50; // spanwise spacing
const int nx=ceil(x/dx); // number of boxes streamwise
const int nz=ceil(z/dz); // number of boxes spanwise
// outputs to terminal
cout << "Mean grain diameter: " << d50 << endl;
cout << "Number of boxes in streamwise direction: " << nx << endl;
cout << "Number of boxes in spanwise direction: " << nz << endl;
cout << "Streamwise bar size: " << dx << endl;
cout << "Spanwise bar size: " << dz << endl;
// generate coordinates with the depthwise being random
default_random_engine generator;
normal_distribution<double> distribution(mean,sigma);
double X[nx+1];
double Z[nz+1];
double number[nx][nz];
double small = number[0][0];
for (int i=0; i<nx; i++)
{
for (int j=0; j<nz; j++)
{
number[i][j] = distribution(generator);
}
}
// find the lowest depthwise coordinate and scale all so it becomes 0
for (int i=0; i<nx; i++)
{
for (int j=0; j<nz; j++)
{
if(small>number[i][j])
small = number[i][j];
}
}
cout << "Mean 0 bed located " << abs(small) << " above bottomWall" << endl;
for (int i=0; i<nx; i++)
{
for (int j=0; j<nz; j++)
{
number[i][j] += abs(small) ;
}
}
// output coordinates to file
for (int i=0; i<nx+1; i++)
{
X[i] = i*dx;
}
for (int i=0; i<nz+1; i++)
{
Z[i] = i*dz;
}
ofstream myfile;
myfile.open ("boxes.txt");
for (int i=0; i<nx; i++)
{
for (int j=0; j<nz; j++)
{
myfile << "(" << X[i] << " 0 " << Z[j] << ")(" << X[i+1] << " " <<
number[i][j] << " " << Z[j+1] << ")\n";
}
}
myfile.close();
return 0;
}
