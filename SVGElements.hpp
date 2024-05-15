//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"

namespace svg
{
    //! @class SVGElement
    //! @brief Abstract class that represents an SVG element
    //! This class is the base
    //! class for all SVG elements. It provides
    //! the interface for drawing, translating,
    //! rotating, and scaling an SVG element.
    //! The class also provides a clone method
    //! that creates a deep copy of the object.
    //! The class is abstract and cannot be
    //! instantiated.
    //! @note The class is part of the svg namespace.
    //! @see svg::Ellipse, svg::Circle, svg::Polygon,
    //! svg::Rect, svg::Polyline, svg::Line, svg::Group
    class SVGElement
    {
    public:
        //! Default constructor
        SVGElement();
        //! Destructor
        virtual ~SVGElement();
        //! Draw the SVG element on the PNG image
        //! @param img PNG image
        virtual void draw(PNGImage &img) const = 0;
        //! Translate the SVG element by a given vector
        //! @param t Translation vector
        virtual void translate(Point &t) = 0;
        //! Rotate the SVG element around a given point
        //! @param origin Point to rotate around
        //! @param degrees Degrees to rotate
        virtual void rotate(const Point &origin, int degrees) = 0;
        //! Scale the SVG element around a given point
        //! @param origin Point to scale around
        //! @param v Scale factor
        virtual void scale(const Point &origin, int v) = 0;
        //! Create a deep copy of the SVG element
        //! @return Pointer to the cloned SVG element
        virtual SVGElement *clone() const = 0;
    };
    //! Reads an SVG file and creates the dimensions and elements
    //! @param svg_file SVG file name
    //! @param dimensions Dimensions of the SVG file
    //! @param svg_elements Vector of SVG elements
    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    //! Converts an SVG file to a PNG file
    //! @param svg_file SVG file name
    //! @param png_file PNG file name
    void convert(const std::string &svg_file,
                 const std::string &png_file);
    //! @class Ellipse
    //! @brief Class that represents an SVG ellipse
    //! The class provides methods for drawing,
    //! translating, rotating, and scaling the ellipse.
    //! The class also provides a clone method
    //! that creates a deep copy of the object.
    class Ellipse : public SVGElement
    {
    public:
        //! Constructor
        //! @param fill Color to use for the ellipse fill.
        //! @param center Coordinates for the ellipse center.
        //! @param radius Radius of the ellipse in X and Y axis.
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        //! Destructor
        ~Ellipse();
        //! Draw the ellipse on the PNG image
        //! @param img PNG image
        void draw(PNGImage &img) const override;
        //! Translate the ellipse by a given vector
        //! @param t Translation vector
        void translate(Point &t) override;
        //! Rotate the ellipse around a given point
        //! @param origin Point to rotate around
        //! @param degrees Degrees to rotate
        void rotate(const Point &origin, int degrees) override;
        //! Scale the ellipse around a given point
        //! @param origin Point to scale around
        //! @param v Scale factor
        void scale(const Point &origin, int v) override;
        //! Create a deep copy of the ellipse
        //! @return Pointer to the cloned ellipse
        Ellipse* clone() const override;
    protected:
        //! Fill color
        Color fill;
        //! Center coordinates
        Point center;
        //! Radius in X and Y axis
        Point radius;
    };
    //! @class Circle
    //! @brief Class that represents an SVG circle subclass of Ellipse
    //! The class provides methods for drawing,
    //! translating, rotating, and scaling the circle.
    //! The class also provides a clone method
    //! that creates a deep copy of the object.
    class Circle : public Ellipse
    {
    public:
        //! Constructor
        //! @param fill Color to use for the circle fill.
        //! @param center Coordinates for the circle center.
        //! @param radius Radius of the circle.
        Circle(const Color &fill, const Point &center, const int &radius);
        //! Destructor
        ~Circle();
        //! Draw the circle on the PNG image.
        //! @param img PNG image.
        void draw(PNGImage &img) const override;
        //! Translate the circle by a given vector.
        //! @param t Translation vector.
        void translate(Point &t) override;
        //! Rotate the circle around a given point.
        //! @param origin Point to rotate around.
        //! @param degrees Degrees to rotate.
        void rotate(const Point &origin, int degrees) override;
        //! Scale the circle around a given point.
        //! @param origin Point to scale around.
        //! @param v Scale factor.
        void scale(const Point &origin, int v) override;
        //! Create a deep copy of the circle.
        //! @return Pointer to the cloned circle.
        Circle* clone() const override;
    private:
        //! Radius of the circle
        int radius;
    };
    //! @class Polygon
    //! @brief Class that represents an SVG polygon
    //! The class provides methods for drawing,
    //! translating, rotating, and scaling the polygon.
    //! The class also provides a clone method
    //! that creates a deep copy of the object.
    class Polygon : public SVGElement
    {
    public:
        //! Constructor
        //! @param fill Color to use for the polygon fill.
        //! @param points Vector of points defining the polygon.
        Polygon(const Color &fill, const std::vector<Point> &points);
        //! Destructor
        ~Polygon();
        //! Draw the polygon on the PNG image.
        //! @param img PNG image.
        void draw(PNGImage &img) const override;
        //! Translate the polygon by a given vector.
        //! @param t Translation vector.
        void translate(Point &t) override;
        //! Rotate the polygon around a given point
        //! @param origin Point to rotate around.
        //! @param degrees Degrees to rotate.
        void rotate(const Point &origin, int degrees) override;
        //! Scale the polygon around a given point.
        //! @param origin Point to scale around.
        //! @param v Scale factor.
        void scale(const Point &origin, int v) override;
        //! Create a deep copy of the polygon.
        //! @return Pointer to the cloned polygon.
        Polygon* clone() const override;
    protected:
        //! Fill Color
        Color fill;
        //! Vector of points defining the polygon
        std::vector<Point> points;
    };
    //! @class Rect
    //! @brief Class that represents an SVG rectangle subclass of Polygon
    //! The class provides methods for drawing,
    //! translating, rotating, and scaling the rectangle.
    //! The class also provides a clone method
    //! that creates a deep copy of the object.
    class Rect : public Polygon
    {
    public:
        //! Constructor
        //! @param fill Color to use for the rectangle fill.
        //! @param top_left Coordinates for the top left corner.
        //! @param bottom_right Coordinates for the bottom right corner.
        Rect(const Color &fill, const Point &top_left, const Point &bottom_right);
        //! Destructor
        ~Rect();
        //! Draw the rectangle on the PNG image.
        //! @param img PNG image.
        void draw(PNGImage &img) const override;
        //! Translate the rectangle by a given vector.
        //! @param t Translation vector.
        void translate(Point &t) override;
        //! Rotate the rectangle around a given point.
        //! @param origin Point to rotate around.
        //! @param degrees Degrees to rotate.
        void rotate(const Point &origin, int degrees) override;
        //! Scale the rectangle around a given point.
        //! @param origin Point to scale around.
        //! @param v Scale factor.
        void scale(const Point &origin, int v) override;
        //! Create a deep copy of the rectangle.
        //! @return Pointer to the cloned rectangle.
        Rect* clone() const override;
    private:
        //! Top left corner coordinates
        Point top_left;
        //! Bottom right corner coordinates
        Point bottom_right;
    };
    //! @class Polyline
    //! @brief Class that represents an SVG polyline
    //! The class provides methods for drawing,
    //! translating, rotating, and scaling the polyline.
    //! The class also provides a clone method
    //! that creates a deep copy of the object.
    class Polyline : public SVGElement
    {
    public:
        //! Constructor
        //! @param stroke Color to use for the polyline stroke.
        //! @param points Vector of points defining the polyline.
        Polyline(const Color &stroke, const std::vector<Point> &points);
        //! Destructor
        ~Polyline();
        //! Draw the polyline on the PNG image.
        //! @param img PNG image.
        void draw(PNGImage &img) const override;
        //! Translate the polyline by a given vector.
        //! @param t Translation vector.
        void translate(Point &t) override;
        //! Rotate the polyline around a given point.
        //! @param origin Point to rotate around.
        //! @param degrees Degrees to rotate.
        void rotate(const Point &origin, int degrees) override;
        //! Scale the polyline around a given point.
        //! @param origin Point to scale around.
        //! @param v Scale factor.
        void scale(const Point &origin, int v) override;
        //! Create a deep copy of the polyline.
        //! @return Pointer to the cloned polyline.
        Polyline* clone() const override;
    protected:
        //! Stroke color
        Color stroke;
        //! Vector of points defining the polyline
        std::vector<Point> points;
    };
    //! @class Line
    //! @brief Class that represents an SVG line sublcass of Polyline
    //! The class provides methods for drawing,
    //! translating, rotating, and scaling the line.
    //! The class also provides a clone method
    //! that creates a deep copy of the object.
    class Line : public Polyline
    {
    public:
        //! Constructor
        //! @param stroke Color to use for the line stroke.
        //! @param start First point.
        //! @param end Second point.
        Line(const Color &stroke, const Point &start, const Point &end);
        //! Destructor
        ~Line();
        //! Draw the line on the PNG image.
        //! @param img PNG image.
        void draw(PNGImage &img) const override;
        //! Translate the line by a given vector.
        //! @param t Translation vector.
        void translate(Point &t) override;
        //! Rotate the line around a given point.
        //! @param origin Point to rotate around.
        //! @param degrees Degrees to rotate.
        void rotate(const Point &origin, int degrees) override;
        //! Scale the line around a given point.
        //! @param origin Point to scale around.
        //! @param v Scale factor.
        void scale(const Point &origin, int v) override;
        //! Create a deep copy of the line.
        //! @return Pointer to the cloned line.
        Line* clone() const override;
    private:
        //! First point
        Point start;
        //! Second point
        Point end;
    };
    //! @class Group
    //! @brief Class that represents an SVG group
    //! The class provides methods for drawing,
    //! translating, rotating, and scaling the group.
    //! The class also provides a clone method
    //! that creates a deep copy of the object.
    class Group : public SVGElement
    {
    public:
        //! Constructor
        //! @param elements Vector of SVG elements.
        Group(const std::vector<SVGElement *> &elements);
        //! Destructor
        ~Group();
        //! Draw the group on the PNG image.
        //! @param img PNG image.
        void draw(PNGImage &img) const override;
        //! Translate the group by a given vector.
        //! @param t Translation vector.
        void translate(Point &t) override;
        //! Rotate the group around a given point.
        //! @param origin Point to rotate around.
        //! @param degrees Degrees to rotate.
        void rotate(const Point &origin, int degrees) override;
        //! Scale the group around a given point.
        //! @param origin Point to scale around.
        //! @param v Scale factor.
        void scale(const Point &origin, int v) override;
        //! Create a deep copy of the group.
        //! @return Pointer to the cloned group.
        Group* clone() const override;
    private:
        //! Vector of SVG elements
        std::vector<SVGElement *> elements;
    };
}
#endif