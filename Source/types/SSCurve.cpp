/*
  ==============================================================================

    SSCurve.cpp
    Created: 13 Mar 2017 8:41:14am
    Author:  Armando Montanez

	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	*  Copyright © 2017 Armando Montanez                                      *
	*                                                                         *
	*  This file is part of SimpleSide.                                       *
	*                                                                         *
	*  SimpleSide is free software: you can redistribute it and/or modify     *
	*  it under the terms of the GNU General Public License as published by   *
	*  the Free Software Foundation, either version 3 of the License, or      *
	*  (at your option) any later version.                                    *
	*                                                                         *
	*  SimpleSide is distributed in the hope that it will be useful,          *
	*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
	*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
	*  GNU General Public License for more details.                           *
	*                                                                         *
	*  You should have received a copy of the GNU General Public License      *
	*  along with SimpleSide.  If not, see <http://www.gnu.org/licenses/>.    *
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  ==============================================================================
*/

#include "SSCurve.h"
SSCurve::SSCurve() {
    entry.setX(0.0f);
    entry.setY(1.0f);
    exit.setX(1.0f);
    exit.setY(0.0f);
    rawExp = -7.0f;
    setPow(rawExp);
}

SSCurve::SSCurve(Point<float> begin, Point<float> end, float pwr) {
    entry.setX(begin.getX());
    entry.setY(begin.getY());
    exit.setX(end.getX());
    exit.setY(end.getY());
    rawExp = pwr;
    setPow(rawExp);
}

double SSCurve::getY(double x) {
    //return pow((x-entry.getX())/(exit.getX()-entry.getX()), pwr)*(exit.getY()-entry.getY())+entry.getY();
    if (rawExp >= 0 && isRising())
        return pow((x-entry.getX())/(exit.getX()-entry.getX()), pwr)*(exit.getY()-entry.getY())+entry.getY();
    else if (rawExp >= 0 && !isRising())
        return -1*(pow(1.0f - (x-entry.getX())/(exit.getX()-entry.getX()), pwr)-1.0f)*(exit.getY()-entry.getY())+entry.getY();
    else if (rawExp < 0 && !isRising())
        return pow((x-entry.getX())/(exit.getX()-entry.getX()), pwr)*(exit.getY()-entry.getY())+entry.getY();
    else
        return -1*(pow(1.0f - (x-entry.getX())/(exit.getX()-entry.getX()), pwr)-1.0f)*(exit.getY()-entry.getY())+entry.getY();
}

bool SSCurve::isInRange(float x) {
    if (x >=entry.getX() && x < exit.getX())
        return true;
    else
        return false;
}


SSCurve* SSCurve::splitAt(Point<float> loc, float newPwr) {
    SSCurve* nc = new SSCurve(loc, exit, newPwr);
    exit.setX(loc.getX());
    setExitY(loc.getY());
    return nc;
}

SSCurve* SSCurve::rawSplitAt(Point<float> loc, float newPwr) {
    SSCurve* nc = new SSCurve(loc, exit, newPwr);
    exit.setX(loc.getX());
    exit.setY(loc.getY());
    return nc;
}

Point<float>* SSCurve::getEntry() {
    return &entry;
}
Point<float>* SSCurve::getExit() {
    return &exit;
}
void SSCurve::setExitY(float y) {
    bool before = isRising();
    exit.setY(y);
    bool after = isRising();
    if (before != after) {
        rawExp = -1.0*rawExp;
    }
}

void SSCurve::setEntryY(float y) {
    bool before = isRising();
    entry.setY(y);
    bool after = isRising();
    if (before != after) {
        rawExp = -1.0*rawExp;
    }
}

float SSCurve::getPow() {
    return rawExp;
}

void SSCurve::setPow(float newExp) {
    if (newExp > 63.0f) {
        newExp = 63.0f;
    } else if (newExp < -63.0f) {
        newExp = -63.0f;
    }
    
    pwr = powf(1.1f, std::abs(newExp));
    rawExp = newExp;
}
void SSCurve::rawSetPow(float newExp) {
    pwr = powf(1.1f, newExp);
    rawExp = newExp;
}

bool SSCurve::isRising() {
    if (entry.y < exit.y)
        return true;
    else
        return false;
}
