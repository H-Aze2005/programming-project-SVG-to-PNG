
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace svg
{
    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
        
        // TODO complete code -->
        
        // Code to traverse the XML child nodes and parse the SVG elements that are defined
        for (XMLElement* child = xml_elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
            string element_name = child->Name();

            SVGElement* element = nullptr;
            if (element_name == "ellipse")
            {
                // Parse ellipse attributes and create a new Ellipse object
                Color fill = parse_color(child->Attribute("fill"));
                Point center = Point{child->IntAttribute("cx"), child->IntAttribute("cy")};
                Point radius = Point{child->IntAttribute("rx"), child->IntAttribute("ry")};
                element = new Ellipse(fill, center, radius);
            }
            else if (element_name == "circle")
            {
                // Parse circle attributes and create a new Circle object
                Color fill = parse_color(child->Attribute("fill"));
                Point center = Point{child->IntAttribute("cx"), child->IntAttribute("cy")};
                Point radius = Point{child->IntAttribute("rx"), child->IntAttribute("ry")};
                element = new Circle(fill, center, radius);
            }
        }
    }
}