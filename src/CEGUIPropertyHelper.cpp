/************************************************************************
	filename: 	CEGUIPropertyHelper.cpp
	created:	6/7/2004
	author:		Paul D Turner
	
	purpose:	Implementation of PropertyHelper methods
*************************************************************************/
/*************************************************************************
    Crazy Eddie's GUI System (http://www.cegui.org.uk)
    Copyright (C)2004 - 2005 Paul D Turner (paul@cegui.org.uk)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*************************************************************************/
#include "CEGUIPropertyHelper.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"
#include "CEGUIExceptions.h"

#include <cstdio>
#include <sstream>

// Start of CEGUI namespace section
namespace CEGUI
{
float PropertyHelper::stringToFloat(const String& str)
{
	using namespace std;

	float val = 0;
	sscanf(str.c_str(), " %f", &val);

	return val;
}


uint PropertyHelper::stringToUint(const String& str)
{
	using namespace std;

	uint val = 0;
	sscanf(str.c_str(), " %u", &val);

	return val;
}


int PropertyHelper::stringToInt(const String& str)
{
	using namespace std;

	uint val = 0;
	sscanf(str.c_str(), " %d", &val);

	return val;
}


bool PropertyHelper::stringToBool(const String& str)
{
	if ((str == "True") || (str == "true"))
	{
		return true;
	}
	else
	{
		return false;
	}

}


Size PropertyHelper::stringToSize(const String& str)
{
	using namespace std;

	Size val(0,0);
	sscanf(str.c_str(), " w:%f h:%f", &val.d_width, &val.d_height);

	return val;
}


Point PropertyHelper::stringToPoint(const String& str)
{
	using namespace std;

	Point val(0,0) ;
	sscanf(str.c_str(), " x:%f y:%f", &val.d_x, &val.d_y);

	return val;
}


Rect PropertyHelper::stringToRect(const String& str)
{
	using namespace std;

	Rect val(0, 0, 0, 0);
	sscanf(str.c_str(), " l:%f t:%f r:%f b:%f", &val.d_left, &val.d_top, &val.d_right, &val.d_bottom);

	return val;
}


const Image* PropertyHelper::stringToImage(const String& str)
{
	using namespace std;

    // handle empty string case
    if (str.empty())
        return 0;

	char imageSet[128];
	char imageName[128];

	sscanf(str.c_str(), " set:%127s image:%127s", imageSet, imageName);

	const Image* image;

	try
	{
		image = &ImagesetManager::getSingleton().getImageset(imageSet)->getImage(imageName);
	}
	catch (UnknownObjectException)
	{
		image = 0;
	}

	return image;
}


UDim PropertyHelper::stringToUDim(const String& str)
{
	using namespace std;

	UDim ud;
	sscanf(str.c_str()," {%f,%f}", &ud.d_scale, &ud.d_offset);

	return ud;
}


UVector2 PropertyHelper::stringToUVector2(const String& str)
{
	using namespace std;

	UVector2 uv;
	sscanf(str.c_str(), " {{%f,%f},{%f,%f}}", &uv.d_x.d_scale,&uv.d_x.d_offset, &uv.d_y.d_scale,&uv.d_y.d_offset);

	return uv;
}


URect PropertyHelper::stringToURect(const String& str)
{
	using namespace std;

	URect ur;
	sscanf(
		str.c_str(),
		" {{%f,%f},{%f,%f},{%f,%f},{%f,%f}}",
		&ur.d_min.d_x.d_scale, &ur.d_min.d_x.d_offset,
		&ur.d_min.d_y.d_scale, &ur.d_min.d_y.d_offset,
		&ur.d_max.d_x.d_scale, &ur.d_max.d_x.d_offset,
		&ur.d_max.d_y.d_scale, &ur.d_max.d_y.d_offset
	);

	return ur;
}


String PropertyHelper::floatToString(float val)
{
	/*using namespace std;

	char buff[64];
	sprintf(buff, "%f", val);

	return String(buff);*/

    std::ostringstream iss;
    iss << val;
    return String(iss.str());
}


String PropertyHelper::uintToString(uint val)
{
	/*using namespace std;

	char buff[64];
	sprintf(buff, "%u", val);

	return String(buff);*/

    std::ostringstream iss;
    iss << val;
    return String(iss.str());
}


String PropertyHelper::intToString(int val)
{
	/*using namespace std;

	char buff[64];
	sprintf(buff, "%d", val);

	return String(buff);*/

    std::ostringstream iss;
    iss << val;
    return String(iss.str());
}


String PropertyHelper::boolToString(bool val)
{
	if (val)
	{
		return String("True");
	}
	else
	{
		return String ("False");
	}

}


String PropertyHelper::sizeToString(const Size& val)
{
	/*using namespace std;

	char buff[128];
	sprintf(buff, "w:%f h:%f", val.d_width, val.d_height);

	return String(buff);*/

    std::ostringstream iss;
    iss << "w:" << val.d_width << " h:" << val.d_height;
    return String(iss.str());
}


String PropertyHelper::pointToString(const Point& val)
{
	/*using namespace std;

	char buff[128];
	sprintf(buff, "x:%f y:%f", val.d_x, val.d_y);

	return String(buff);*/

    std::ostringstream iss;
    iss << "x:" << val.d_x << " y:" << val.d_y;
    return String(iss.str());
}


String PropertyHelper::rectToString(const Rect& val)
{
	/*using namespace std;

	char buff[256];
	sprintf(buff, "l:%f t:%f r:%f b:%f", val.d_left, val.d_top, val.d_right, val.d_bottom);

	return String(buff);*/

    std::ostringstream iss;
    iss << "l:" << val.d_left << " t:" << val.d_top << " r:" << val.d_right << " b:" << val.d_bottom;
    return String(iss.str());
}


String PropertyHelper::imageToString(const Image* const val)
{
	if (val)
	{
		return String("set:" + val->getImagesetName() + " image:" + val->getName());
	}

	return String("");
}


String PropertyHelper::udimToString(const UDim& val)
{
	/*using namespace std;

	char buff[128];
	sprintf(buff, "{%f,%f}", val.d_scale, val.d_offset);

	return String(buff);*/

    std::ostringstream iss;
    iss << '{' << val.d_scale << ',' << val.d_offset << '}';
    return String(iss.str());
}


String PropertyHelper::uvector2ToString(const UVector2& val)
{
	/*using namespace std;

	char buff[256];
	sprintf(buff, "{{%f,%f},{%f,%f}}", val.d_x.d_scale, val.d_x.d_offset, val.d_y.d_scale, val.d_y.d_offset);

    return String(buff);*/

    std::ostringstream iss;

    iss << "{{"
        << val.d_x.d_scale << ',' << val.d_x.d_offset << "},{"
        << val.d_y.d_scale << ',' << val.d_y.d_offset << "}}";

	return String(iss.str());
}


String PropertyHelper::urectToString(const URect& val)
{
	/*using namespace std;

	char buff[512];
	sprintf(
		buff,
		"{{%f,%f},{%f,%f},{%f,%f},{%f,%f}}",
		val.d_min.d_x.d_scale,val.d_min.d_x.d_offset,
		val.d_min.d_y.d_scale,val.d_min.d_y.d_offset,
		val.d_max.d_x.d_scale,val.d_max.d_x.d_offset,
		val.d_max.d_y.d_scale,val.d_max.d_y.d_offset
	);

    return String(buff);*/

    std::ostringstream iss;

    iss << "{{"
        << val.d_min.d_x.d_scale << ',' << val.d_min.d_x.d_offset << "},{"
        << val.d_min.d_y.d_scale << ',' << val.d_min.d_y.d_offset << "},{"
        << val.d_max.d_x.d_scale<< ',' << val.d_max.d_x.d_offset << "},{"
        << val.d_max.d_y.d_scale << ',' << val.d_max.d_y.d_offset << "}}";

	return String(iss.str());
}


String PropertyHelper::colourToString(const colour& val)
{
	using namespace std;

	char buff[16];
	sprintf(buff, "%.8X", val.getARGB());

	return String(buff);
}


colour PropertyHelper::stringToColour(const String& str)
{
	using namespace std;

	argb_t val = 0xFF000000;
	sscanf(str.c_str(), " %8X", &val);

	return colour(val);

}


String PropertyHelper::colourRectToString(const ColourRect& val)
{
	using namespace std;

	char buff[64];
	sprintf(buff, "tl:%.8X tr:%.8X bl:%.8X br:%.8X", val.d_top_left.getARGB(), val.d_top_right.getARGB(), val.d_bottom_left.getARGB(), val.d_bottom_right.getARGB());

	return String(buff);
}


ColourRect PropertyHelper::stringToColourRect(const String& str)
{
	using namespace std;

	argb_t topLeft = 0xFF000000, topRight = 0xFF000000, bottomLeft = 0xFF000000, bottomRight = 0xFF000000;
	sscanf(str.c_str(), "tl:%8X tr:%8X bl:%8X br:%8X", &topLeft, &topRight, &bottomLeft, &bottomRight);

	return ColourRect(topLeft, topRight, bottomLeft, bottomRight);
}

} // End of  CEGUI namespace section