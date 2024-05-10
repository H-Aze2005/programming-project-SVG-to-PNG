
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

            SVGElement* element = nullptr;
            const char* element_name = child->Name();
            if (strcmp(element_name, "ellipse") == 0)
            {
                // Create Color object from fill color string
                Color fill(parse_color(child->Attribute("fill")));
                // Create Point objects for center and radius
                Point center = Point{child->IntAttribute("cx"), child->IntAttribute("cy")};
                Point radius = Point{child->IntAttribute("rx"), child->IntAttribute("ry")};

                // Create Ellipse object and add to SVG elements vector
                Ellipse* ellipse = new Ellipse(fill, center, radius);
                svg_elements.push_back(ellipse);
            
            }
            else if (strcmp(element_name, "circle") == 0)
            {
                // Create Color object from fill color string
                Color fill(parse_color(child->Attribute("fill")));
                // Create Point objects for center and radius
                Point center = Point{child->IntAttribute("cx"), child->IntAttribute("cy")};
                int radius = child->IntAttribute("r");

                // Create Circle object and add to SVG elements vector
                Circle* circle = new Circle(fill, center, radius);
                svg_elements.push_back(circle);
            }
            else if (strcmp(element_name, "polygon") == 0) 
            {
                // Create Color object from fill color string
                Color fill(parse_color(child->Attribute("fill")));
                // Create vector of Point objects for polygon points
                vector<Point> points;
                const char* points_str = child->Attribute("points");
                string points_str_copy = points_str;
                size_t pos = 0;
                string token;
                while ((pos = points_str_copy.find(" ")) != string::npos) {
                    token = points_str_copy.substr(0, pos);
                    size_t comma_pos = token.find(",");
                    int x = stoi(token.substr(0, comma_pos));
                    int y = stoi(token.substr(comma_pos + 1));
                    points.push_back(Point{x, y});
                    points_str_copy.erase(0, pos + 1);
                }
                size_t comma_pos = points_str_copy.find(",");
                int x = stoi(points_str_copy.substr(0, comma_pos));
                int y = stoi(points_str_copy.substr(comma_pos + 1));
                points.push_back(Point{x, y});

                // Create Polygon object and add to SVG elements vector
                Polygon* polygon = new Polygon(fill, points);
                svg_elements.push_back(polygon);
            }
            else if (strcmp(element_name, "rect") == 0)
            {
                // Create Color object from fill color string
                Color fill(parse_color(child->Attribute("fill")));
                // Create Point objects for top left and bottom right corners
                Point top_left = Point{child->IntAttribute("x"), child->IntAttribute("y")};
                Point bottom_right = Point{child->IntAttribute("x") + child->IntAttribute("width") - 1, child->IntAttribute("y") + child->IntAttribute("height") - 1};
                cout << "Top left: " << top_left.x << ", " << top_left.y << ", " << child->IntAttribute("width") << ", " << dimensions.x << endl;
                // Create Rect object and add to SVG elements vector
                Rect* rect = new Rect(fill, top_left, bottom_right);
                svg_elements.push_back(rect);
            }
            else if (strcmp(element_name, "polyline") == 0)
            {
                // Create Color object from stroke color string
                Color stroke(parse_color(child->Attribute("stroke")));
                // Create vector of Point objects for polyline points
                vector<Point> points;
                const char* points_str = child->Attribute("points");
                string points_str_copy = points_str;
                size_t pos = 0;
                string token;
                while ((pos = points_str_copy.find(" ")) != string::npos) {
                    token = points_str_copy.substr(0, pos);
                    size_t comma_pos = token.find(",");
                    int x = stoi(token.substr(0, comma_pos));
                    int y = stoi(token.substr(comma_pos + 1));
                    points.push_back(Point{x, y});
                    points_str_copy.erase(0, pos + 1);
                }
                size_t comma_pos = points_str_copy.find(",");
                int x = stoi(points_str_copy.substr(0, comma_pos));
                int y = stoi(points_str_copy.substr(comma_pos + 1));
                points.push_back(Point{x, y});

                // Create Polyline object and add to SVG elements vector
                Polyline* polyline = new Polyline(stroke, points);
                svg_elements.push_back(polyline);
            }
            else if (strcmp(element_name, "line") == 0)
            {
                // Create Color object from stroke color string
                Color stroke(parse_color(child->Attribute("stroke")));
                // Create Point objects for start and end points
                Point start = Point{child->IntAttribute("x1"), child->IntAttribute("y1")};
                Point end = Point{child->IntAttribute("x2"), child->IntAttribute("y2")};

                // Create Line object and add to SVG elements vector
                Line* line = new Line(stroke, start, end);
                svg_elements.push_back(line);
            }
            else if (element != nullptr)
            {
                svg_elements.push_back(element);
            }
        }
    }
}