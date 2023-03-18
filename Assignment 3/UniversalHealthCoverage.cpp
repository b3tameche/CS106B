/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);


int main() {
	Set<string> cities;
	cities += "A", "B", "C", "D", "E", "F";
	Vector< Set<string> > locations;
	Set<string> h1;
	h1 += "A", "B", "C";
	Set<string> h2;
	h2 += "A", "C", "D";
	Set<string> h3;
	h3 += "B", "F";
	Set<string> h4;
	h4 += "C", "E", "F";
	locations += h1, h2, h3, h4;
	int numHospitals = 3;
    Vector< Set<string> > result;

	if (canOfferUniversalCoverage(cities, locations, numHospitals, result)) cout << result << endl;
	else cout << "Unable to cover" << endl;
    return 0;
}

bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations, int numHospitals, Vector< Set<string> >& result) {
	if (numHospitals == 0) {
		Set<string> joint;
		foreach (Set<string> hosp in result) {
			joint += hosp;
		}
		return cities == joint;
	}
	// first "if" below is for little performance tweak, if result already satisfies upper "if" (e.i. h1 = ABC, h2=DEF, but not if h1,h2,h3 in total is ABCDE and h4 is ABCDEF)
	foreach (Set<string> hosp in locations) {
		if (canOfferUniversalCoverage(cities, locations, 0, result)) return 1;
		result.add(hosp);
		Vector< Set<string> > allButFirst = locations;
		allButFirst.remove(0);
		if (canOfferUniversalCoverage(cities, allButFirst, numHospitals-1, result)) return 1;
		else result.remove(result.size()-1);
	}
	return 0;
}
