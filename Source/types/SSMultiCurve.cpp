/*
  ==============================================================================

    SSMultiCurve.cpp
    Created: 13 Mar 2017 9:28:16am
    Author:  Armando Montanez

	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	*  Copyright � 2017 Armando Montanez                                      *
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

#include "SSMultiCurve.h"
#include "../ui/CurveView.h"

SSMultiCurve::SSMultiCurve() : parent(NULL) {
    curves.push_back(new SSCurve);
    handles.push_back(new SSHandle(this));
    ensureWrap();
}

SSMultiCurve::~SSMultiCurve() {
    while (!curves.empty()) {
        delete curves[0];
        curves.pop_front();
        delete handles[0];
        handles.pop_front();
    }
}

const Point<float>* SSMultiCurve::handleStart(int i) {
    return curves[i]->getEntry();
}
const Point<float>* SSMultiCurve::curveEnd(int i) {
    return curves[i]->getExit();
}

int SSMultiCurve::count() {
    return curves.size();
}

double SSMultiCurve::smoothedAt(float t) {
    double a = t - 0.000001;
    double b = t + 0.000001;
    a = fmodf(a, 1.0f);
    b = fmodf(b, 1.0f);
    a = at(a);
    b = at(b);
    double c = at(t);
    return (a+b+c)/3;
}

double SSMultiCurve::at(float t) {
    int i = 0;
    while (!curves[i]->isInRange(t)) {
        i++;
        if (i == curves.size())
            return -1;
    }
    return curves[i]->getY(t);
}

void SSMultiCurve::splitAt(float x, float y, float newCurvePwr) {
    std::deque<SSCurve*>::iterator ic = curves.begin();
    std::deque<SSHandle*>::iterator ih = handles.begin();
    int i = 0;
    while (!(*ic)->isInRange(x)) {
        ic++;
        ih++;
        i++;
    }
    i++;
    curves.insert(ic+1, (*ic)->splitAt(Point<float>(x, y), newCurvePwr));
    handles.insert(ih+1, new SSHandle(this, curves[i]->getEntry()->x, curves[i]->getEntry()->y));
    if (parent != NULL) {
        ((CurveView*)parent)->addHandle(handles[i]);
    }
    ensureWrap();
}

void SSMultiCurve::rawSplitAt(float x, float y, float newCurvePwr) {
    std::deque<SSCurve*>::iterator ic = curves.begin();
    std::deque<SSHandle*>::iterator ih = handles.begin();
    int i = 0;
    while (!(*ic)->isInRange(x)) {
        ic++;
        ih++;
        i++;
    }
    i++;
    curves.insert(ic+1, (*ic)->rawSplitAt(Point<float>(x, y), newCurvePwr));
    handles.insert(ih+1, new SSHandle(this, curves[i]->getEntry()->x, curves[i]->getEntry()->y));
    if (parent != NULL) {
        ((CurveView*)parent)->addHandle(handles[i]);
    }
    
    ensureWrap();
}

void SSMultiCurve::setParent(juce::Component *p) {
    parent = p;
}

void SSMultiCurve::ensureWrap() {
    curves[curves.size()-1]->setExitY(curves[0]->getEntry()->getY());
}

void SSMultiCurve::remove(SSHandle* h) {
    if (h == handles[0])
        return;
    int i = 0;
    while (h != handles[i])
        i++;
    SSHandle* th = handles[i];
    SSCurve*  tc = curves[i];
    handles.erase(handles.begin()+i);
    curves.erase(curves.begin()+i);
    if (parent != NULL)
        parent->removeChildComponent(th);
    delete th;
    delete tc;
    if (i != curves.size()) {
        curves[i-1]->getExit()->setX(curves[i]->getEntry()->getX());
        curves[i-1]->getExit()->setY(curves[i]->getEntry()->getY());
    } else {
        curves[i-1]->getExit()->setX(1.0f);
        ensureWrap();
    }
    
    if (parent != NULL)
        parent->repaint();
}

int SSMultiCurve::getIndex(SSHandle *h) {
    int i = 0;
    while (h != handles[i])
        i++;
    return i;
}

void SSMultiCurve::setNewPos(int i, Point<float> newPos) {
    if (i != 0) {
        curves[i]->setEntryY(newPos.y); // use to update curve direction
        *(curves[i]->getEntry()) = newPos;
        curves[i-1]->setExitY(newPos.y); // use to update curve direction
        *(curves[i-1]->getExit()) = newPos;
    } else {
        curves[i]->setEntryY(newPos.y); // use to update curve direction
        ensureWrap();
    }
}

int SSMultiCurve::curveAt(float loc) {
    int i = 0;
    while (i < curves.size()) {
        if (curves[i]->isInRange(loc))
            break;
        i++;
    }
    if (i == curves.size())
        i = -1;
    return i;
}

float SSMultiCurve::getPow(int i) {
    return curves[i]->getPow();
}

void SSMultiCurve::setPow(int i, float newPow) {
    curves[i]->setPow(newPow);
}

void SSMultiCurve::rawSetPow(int i, float newPow) {
    curves[i]->rawSetPow(newPow);
}

bool SSMultiCurve::isRising(int i) {
    return curves[i]->isRising();
}

void SSMultiCurve::clearCurve() {
    while (count() != 1) {
        remove(handles[count()-1]);
    }
    curves[0]->setPow(-7.0f);
    curves[0]->setEntryY(0.0);
    handles[0]->setBounds((int)(0*CurveView::VIEW_WIDTH-SSHandle::baseSize/2+1), (int)(0*CurveView::VIEW_HEIGHT-SSHandle::baseSize/2+1), SSHandle::baseSize, SSHandle::baseSize);;
}
