#ifndef HELPER__H 
#define HELPER__H

double lin_interp(double x, double x1, double y1, double x2, double y2)
{
	return (y1 + (x - x1) * ((y2 - y1) / (x2 - x1)));
}

#endif
