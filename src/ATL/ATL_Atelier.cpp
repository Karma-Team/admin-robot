/*
 * ASV_Asserv.cpp
 *
 *  Created on: 19 nov. 2020
 *      Author: thomas
 */

#include "ATL_Atelier.hpp"

#include "MOT_MoteurManager.hpp"
#include "MOT_MoteurPWM.hpp"


using namespace std;

ATL::CAtelier::CAtelier()
{

}

ATL::CAtelier::~CAtelier()
{
	// Rien a faire
}

void ATL::CAtelier::actionAtelier(SCsvAtelierAction p_scsvAtelierAction)
{

}

void ATL::CAtelier::debug()
{
	/*
	cout << "erreurOrientationKp " <<  << endl;
	cout << " erreurDistanceKp " << << endl;
	cout << " orientationPid " <<  << endl;
	cout << " distancePid " <<  << endl;
	cout << " cmdMoteurDroit " <<  << endl;
	cout << " cmdMoteurGauche " <<<< endl;
	*/
}
