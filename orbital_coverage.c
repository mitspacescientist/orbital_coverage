// C program orbital_coverage.c
// written 30 June 2011 by Dr. Lyman Hazelton
// Equations from Orbital Mechanics, Third Edition
// by Chobotov (AIAA)

// Variable definitions
// dh = satelite altitude
// dR = body radius (Earth, 6378.135 km)
// dEps = ground elevation angle, degrees
// dTheta = body central angle of coverage
// dAlpha = satellite field of view angle
// dDist = radius of coverage on body surface
// dRho = slant range distance to farthest circle

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main (int argc, char *argv[])
{
	double dh, dR, dA, dEps, dTheta, dAlpha, dDist, dRho;
	double dPi = 4.0 * atan2(1,0);
	double dRadianConvert = 180.0 / dPi;
	double dNumberOfPlanes, dNumberPerPlane;
	int iNumberOfPlanes, iNumberPerPlane;
	double dLineOfSightDistance;
	double dMinimumBeamAltitude;
	double dOrbitalPeriod;
	double dMuEarth = 3.986004e14;		// Mu = G*M, of course
	double dMuMultiplier = 1.0;
	double dTemp;
	int iarglen, i;
	int ichartest = 0;

		if(argc < 4)
	{
		printf("USAGE:\norbital_coverage <Body_Name> <Satellite Altitude> <Minimum Look Angle>\n");
		printf("or\n");
		printf("orbital_coverage <Body_Radius> <Satellite Altitude> <Minimum Look Angle>\n");
		printf("Radius and Altitude in Kilometers; Angle in Degrees.\n");
		return 1;
	}

	iarglen = strlen(argv[1]);
	for(i=0;i<iarglen;i++) ichartest += isalpha(argv[1][i]);
	if(ichartest)
	{
		if(strcmp(argv[1], "Earth") == 0)
		{
			dR = 6378.135;
			dMuMultiplier = 1.0;
		}
		else if(strcmp(argv[1], "Moon") == 0)
		{
			dR = 1738.0;
			dMuMultiplier = 1.23000383e-2;
		}
		else if(strcmp(argv[1], "Mercury") == 0)
		{
			dR = 2440.0;
			dMuMultiplier = 0.0553;
		}
		else if(strcmp(argv[1], "Venus") == 0)
		{
			dR = 6051.8;
			dMuMultiplier = 0.815;
		}
		else if(strcmp(argv[1], "Mars") == 0)
		{
			dR = 3397.0;
			dMuMultiplier = 0.107;
		}
		else if(strcmp(argv[1], "Jupiter") == 0)
		{
			dR = 71492.0;
			dMuMultiplier = 318.0;
		}
		else if(strcmp(argv[1], "Saturn") == 0)
		{
			dR = 60268.0;
			dMuMultiplier = 95.2;
		}
		else if(strcmp(argv[1], "Uranus") == 0)
		{
			dR = 25559.0;
			dMuMultiplier = 14.5;
		}
		else if(strcmp(argv[1], "Neptune") == 0)
		{
			dR = 24766.0;
			dMuMultiplier = 17.2;
		}
		else if(strcmp(argv[1], "Pluto") == 0)
		{
			dR = 1137.0;
			dMuMultiplier = 3.69e-3;
		}
		else
		{
			printf("\n%s is not a known planetary object.  Sorry, terminating.\n\n", argv[1]);
			return 2;
		}
	}
	else
		sscanf(argv[1], "%lf", &dR);
	sscanf(argv[2], "%lf", &dh);
	sscanf(argv[3], "%lf", &dEps);

	dEps = dEps / dRadianConvert;
	dA = dR + dh;
	dTemp = cos(dEps)/(1.0 + (dh / dR));
	dAlpha = asin(dTemp);
	dTheta = acos(dTemp) - dEps;
	dDist = dR * dTheta;
	dRho = sqrt(dR * dR + dA * dA - 2.0 * dR * dA * cos(dTheta));
	dLineOfSightDistance = 2.0 * dA * sin(dTheta);
	dMinimumBeamAltitude = dA * cos(dTheta) - dR;
	dNumberOfPlanes = dPi / (2.0 * dTheta);
	iNumberOfPlanes = (int) ceil(dNumberOfPlanes) + 1;
	iNumberPerPlane = 2 * iNumberOfPlanes - 1;
	dOrbitalPeriod = 2.0 * dPi / sqrt(dMuMultiplier * dMuEarth / (dA*dA*dA*1.0e9));

	printf("\nFor Body Radius %lf km\nSatellite Altitude %lf km\nMinimum Look Angle %lf degrees:\n\n",
			 dR, dh, dEps * dRadianConvert);
	printf("Orbital period = %lf seconds.\n", dOrbitalPeriod);
	printf("Body Central Half Angle = %lf degrees\n", dTheta * dRadianConvert);
	printf("Distance seen = %lf km\n", dDist);
	printf("Maximum Slant Range = %lf km\n", dRho);
	printf("Line Of Sight Distance Between Satellites in Plane = %lf km\n", dLineOfSightDistance);
	printf("MinimumBeamAltitude Between Satellites = %lf km\n\n", dMinimumBeamAltitude);
	printf("A global constellation at this altitude requires %d planes with %d satellites per plane.\n\n",
			 iNumberOfPlanes, iNumberPerPlane);

	return 0;
}
