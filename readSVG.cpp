#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include <algorithm>

using namespace std;
using namespace tinyxml2;

namespace svg
{
    void applyTransform(SVGElement* element, const char* transform_attr, const char* transform_origin_attr) 
    {
        if (transform_attr) 
        {
            string transform_str = transform_attr;
            replace(transform_str.begin(), transform_str.end(), ',', ' ');
            cout << transform_str << endl;
            int angle;
            int x_translate, y_translate;
            if (sscanf(transform_str.c_str(), "translate(%d %d)", &x_translate, &y_translate) == 2) 
            {
                // Successfully parsed the translation values
                Point t = Point{x_translate, y_translate};
                element->translate(t);
            }
            else if (sscanf(transform_str.c_str(), "rotate(%d)", &angle) == 1)
            {
                // Successfully parsed the rotation angle
                Point origin;
                if (transform_origin_attr)
                {
                    int x_origin, y_origin;
                    if (sscanf(transform_origin_attr, "%d %d", &x_origin, &y_origin) == 2)
                    {
                        // Successfully parsed the transform-origin values
                        origin = Point{x_origin, y_origin};
                    }
                }
                else
                {
                    // No transform-origin attribute, use (0,0) as the default rotation origin
                    origin = Point{0, 0};
                }
                element->rotate(origin, angle);
            }
            else if (sscanf(transform_str.c_str(), "scale(%d)", &x_translate) == 1)
            {
                // Successfully parsed the scale factor
                Point origin;
                if (transform_origin_attr)
                {
                    int x_origin, y_origin;
                    if (sscanf(transform_origin_attr, "%d %d", &x_origin, &y_origin) == 2)
                    {
                        // Successfully parsed the transform-origin values
                        origin = Point{x_origin, y_origin};
                    }
                }
                else
                {
                    // No transform-origin attribute, use (0,0) as the default scale origin
                    origin = Point{0, 0};
                }
                element->scale(origin, x_translate);
            }
        }
    }

    void readGroup(XMLElement* group_elem, vector<SVGElement *>& group_elements)
    {
    for (XMLElement* child = group_elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
        // Process child elements here, similar to in readSVG
        // If you encounter another "g", call readGroup recursively
        const char* element_name = child->Name();
        if (strcmp(element_name, "g") == 0)
        {
            vector<SVGElement *> nested_group_elements;
            readGroup(child, nested_group_elements);
            Group* nested_group = new Group(nested_group_elements);
            applyTransform(nested_group, child->Attribute("transform"), child->Attribute("transform-origin"));
            group_elements.push_back(nested_group);
        }
        // Process other elements as before
            if (strcmp(element_name, "ellipse") == 0)
            {
                // Create Color object from fill color string
                Color fill(parse_color(child->Attribute("fill")));
                // Create Point objects for center and radius
                Point center = Point{child->IntAttribute("cx"), child->IntAttribute("cy")};
                Point radius = Point{child->IntAttribute("rx"), child->IntAttribute("ry")};

                // Create Ellipse object and add to SVG elements vector
                Ellipse* ellipse = new Ellipse(fill, center, radius);

                applyTransform(ellipse, child->Attribute("transform"), child->Attribute("transform-origin"));
                group_elements.push_back(ellipse);
            
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

                applyTransform(circle, child->Attribute("transform"), child->Attribute("transform-origin"));
                group_elements.push_back(circle);
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

                applyTransform(polygon, child->Attribute("transform"), child->Attribute("transform-origin"));
                group_elements.push_back(polygon);
            }
            else if (strcmp(element_name, "rect") == 0)
            {
                // Create Color object from fill color string
                Color fill(parse_color(child->Attribute("fill")));
                // Create Point objects for top left and bottom right corners
                Point top_left = Point{child->IntAttribute("x"), child->IntAttribute("y")};
                Point bottom_right = Point{child->IntAttribute("x") + child->IntAttribute("width") - 1, child->IntAttribute("y") + child->IntAttribute("height") - 1};
                // Create Rect object and add to SVG elements vector
                Rect* rect = new Rect(fill, top_left, bottom_right);

                applyTransform(rect, child->Attribute("transform"), child->Attribute("transform-origin"));
                group_elements.push_back(rect);
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

                applyTransform(polyline, child->Attribute("transform"), child->Attribute("transform-origin"));
                group_elements.push_back(polyline);
            }
            else if (strcmp(element_name, "line") == 0)
            {
                // Create Color object from stroke color string
                Color stroke(parse_color(child->Attribute("stroke")));

                // Create Point objects for start and end points
                Point start = Point{child->IntAttribute("x1"), child->IntAttribute("y1")};
                Point end = Point{child->IntAttribute("x2"), child->IntAttribute("y2")};

                // Create Line object
                Line* line = new Line(stroke, start, end);

                applyTransform(line, child->Attribute("transform"), child->Attribute("transform-origin"));
                // Add to SVG elements vector
                group_elements.push_back(line);
            }
    }
}

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

                applyTransform(ellipse, child->Attribute("transform"), child->Attribute("transform-origin"));
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

                applyTransform(circle, child->Attribute("transform"), child->Attribute("transform-origin"));
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

                applyTransform(polygon, child->Attribute("transform"), child->Attribute("transform-origin"));
                svg_elements.push_back(polygon);
            }
            else if (strcmp(element_name, "rect") == 0)
            {
                // Create Color object from fill color string
                Color fill(parse_color(child->Attribute("fill")));
                // Create Point objects for top left and bottom right corners
                Point top_left = Point{child->IntAttribute("x"), child->IntAttribute("y")};
                Point bottom_right = Point{child->IntAttribute("x") + child->IntAttribute("width") - 1, child->IntAttribute("y") + child->IntAttribute("height") - 1};
                // Create Rect object and add to SVG elements vector
                Rect* rect = new Rect(fill, top_left, bottom_right);

                applyTransform(rect, child->Attribute("transform"), child->Attribute("transform-origin"));
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

                applyTransform(polyline, child->Attribute("transform"), child->Attribute("transform-origin"));
                svg_elements.push_back(polyline);
            }
            else if (strcmp(element_name, "line") == 0)
            {
                // Create Color object from stroke color string
                Color stroke(parse_color(child->Attribute("stroke")));

                // Create Point objects for start and end points
                Point start = Point{child->IntAttribute("x1"), child->IntAttribute("y1")};
                Point end = Point{child->IntAttribute("x2"), child->IntAttribute("y2")};

                // Create Line object
                Line* line = new Line(stroke, start, end);

                applyTransform(line, child->Attribute("transform"), child->Attribute("transform-origin"));
                // Add to SVG elements vector
                svg_elements.push_back(line);
            }
            else if (strcmp(element_name, "g") == 0)
            {
                vector<SVGElement *> group_elements;
                readGroup(child, group_elements);
                Group* group = new Group(group_elements);
                applyTransform(group, child->Attribute("transform"), child->Attribute("transform-origin"));
                svg_elements.push_back(group);
            }
            else if (element != nullptr)
            {
                svg_elements.push_back(element);
            }
        }
    }
}