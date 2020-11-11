/*
  ==============================================================================

    CurveView.h
    Created: 13 Mar 2017 8:27:13am
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

#ifndef CURVEVIEW_H_INCLUDED
#define CURVEVIEW_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"
#include <deque>
#include "../types/SSMultiCurve.h"
#include "SSHandle.h"

//==============================================================================
/*
*/
class CurveView    : public juce::Component
{
protected:
public:
    CurveView(SSMultiCurve*);
    ~CurveView();
    
    static const int &VIEW_HEIGHT;
    static const int &VIEW_WIDTH;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void addHandle(SSHandle*);
    
private:
    bool mouseOver;
    SSMultiCurve* curves;
    int highlightRegion;
    float origPow;
    juce::Point<float> mouseLocSnap;
    juce::Image playhead;
    
    
    void mouseEnter(const juce::MouseEvent &event) override;
    void mouseExit(const juce::MouseEvent &event) override;
    void mouseMove(const juce::MouseEvent &event) override;
    void mouseDown(const juce::MouseEvent &event) override;
    void mouseDrag(const juce::MouseEvent &event) override;
    void mouseUp(const juce::MouseEvent &event) override;
    
    static int CV_HEIGHT;             // view height, adjustable
    static int CV_WIDTH;              // view width,  adjustable
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CurveView)
};

#endif  // CURVEVIEW_H_INCLUDED
