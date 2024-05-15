#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include <algorithm>
#include <map>

using namespace std;
using namespace tinyxml2;

namespace svg
{
    //! Helper function to apply transformations to SVG elements
    //! @param element The SVG element to apply the transformation to.
    //! @param transform_attr The transform attribute string.
    //! @param transform_origin_attr The transform-origin attribute string.
    void applyTransform(SVGElement* element, const char* transform_attr, const char* transform_origin_attr) 
    {
        if (transform_attr) 
        {
            string transform_str = transform_attr;
            replace(transform_str.begin(), transform_str.end(), ',', ' ');
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
    //! Helper function to handle the recurisve needs of the group element
    //! @param group_elem The XML element representing the group.
    //! @param group_elements The vector of SVG elements to add the group elements to.
    //! @param id_map The map of SVG elements with id attributes.
    void readGroup(XMLElement* group_elem, vector<SVGElement *>& group_elements, std::map<std::string, SVGElement*>& id_map)
    {
        for (XMLElement* child = group_elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) 
        {
            // Process child elements here, similar to in readSVG
            // If you encounter another "g", call readGroup recursively
            const char* element_name = child->Name();
            if (strcmp(element_name, "g") == 0)
            {
                vector<SVGElement *> nested_group_elements;
                readGroup(child, nested_group_elements, id_map);
                Group* nested_group = new Group(nested_group_elements);
                applyTransform(nested_group, child->Attribute("transform"), child->Attribute("transform-origin"));
                group_elements.push_back(nested_group);
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = nested_group;
                }
            }
            // Process other elements as before
            else if (strcmp(element_name, "ellipse") == 0)
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
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = ellipse;
                }
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
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = circle;
                }
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
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = polygon;
                }
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
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = rect;
                }
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
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = polyline;
                }
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
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = line;
                }
            }
            else if (strcmp(element_name, "use") == 0)
            {
            // Get href attribute
            const char* href = child->Attribute("href");
            // Remove '#' prefix from href
            std::string id = href + 1;
            // Find original element in map
            SVGElement* original = id_map[id];
            // Clone original element
            if (original != nullptr) {
                // Clone original element
                SVGElement* clone = original->clone();
                // Apply transformations to clone
                applyTransform(clone, child->Attribute("transform"), child->Attribute("transform-origin"));
                // Add clone to SVG elements vector
                group_elements.push_back(clone);
                // If the use element has an id, add the clone to the id_map
                if (child->Attribute("id")) {
                    id_map[child->Attribute("id")] = clone;
                }
                } else {
                    // Handle the error: the original element was not found in the map
                    std::cerr << "Error: original element with id " << id << " not found." << std::endl;
                }
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

        // Map to store elements with id attribute
        std::map<std::string, SVGElement*> id_map;
        
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
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = ellipse;
                }
            
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
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = circle;
                }
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
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = polygon;
                }
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
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = rect;
                }
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
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = polyline;
                }
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
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = line;
                }
            }
            else if (strcmp(element_name, "g") == 0)
            {
                vector<SVGElement *> group_elements;
                readGroup(child, group_elements, id_map);
                Group* group = new Group(group_elements);
                applyTransform(group, child->Attribute("transform"), child->Attribute("transform-origin"));
                svg_elements.push_back(group);
                if (child->Attribute("id"))
                {
                    id_map[child->Attribute("id")] = group;
                }
            }
            else if (strcmp(element_name, "use") == 0)
            {
            // Get href attribute
            const char* href = child->Attribute("href");
            // Remove '#' prefix from href
            std::string id = href + 1;
            // Find original element in map
            SVGElement* original = id_map[id];
            // Clone original element
            if (original != nullptr) {
                // Clone original element
                SVGElement* clone = original->clone();
                // Apply transformations to clone
                applyTransform(clone, child->Attribute("transform"), child->Attribute("transform-origin"));
                // Add clone to SVG elements vector
                svg_elements.push_back(clone);
                // If the use element has an id, add the clone to the id_map
                if (child->Attribute("id")) {
                    id_map[child->Attribute("id")] = clone;
                }
                } else {
                    // Handle the error: the original element was not found in the map
                    std::cerr << "Error: original element with id " << id << " not found." << std::endl;
                }
            }
            else if (element != nullptr)
            {
                svg_elements.push_back(element);
            }
        }
    }
}