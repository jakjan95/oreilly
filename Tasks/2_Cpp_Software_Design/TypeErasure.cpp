/**************************************************************************************************
*
* \file TypeErasure.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'Shape' class by means of Type Erasure. 'Shape' may require all types to
*       provide a 'free_draw()' function that draws them to the screen.
*
**************************************************************************************************/


//---- <GraphicsLibrary.h> (external) -------------------------------------------------------------

#include <string>
// ... and many more graphics-related headers

enum class Color
{
   red   = 0xFF0000,
   green = 0x00FF00,
   blue  = 0x0000FF
};

std::string to_string( Color color )
{
   switch( color ) {
      case Color::red:
         return "red (0xFF0000)";
      case Color::green:
         return "green (0x00FF00)";
      case Color::blue:
         return "blue (0x0000FF)";
      default:
         return "unknown";
   }
}


//---- <Point.h> ----------------------------------------------------------------------------------

struct Point
{
   double x;
   double y;
};


//---- <Shape.h> ----------------------------------------------------------------------------------

#include <memory>
#include <type_traits>
#include <utility>

class Shape
{
   // TODO: Implement the 'Shape' class by means of Type Erasure.
   public:
      
      template<typename ShapeT> //possibility to introduce a Strategy DP which allows inject strategy here
      Shape(ShapeT shape)
      : pimpl_{std::make_unique<Model<ShapeT>>(shape)}
      {}

      void draw() const{pimpl_->draw();}


      // Introduction of Shape copying using Prototype from Model
      Shape(Shape const& other)
         :pimpl_{other.pimpl_->clone()}
      {} 

      Shape& operator=(Shape const& other){
         Shape copy{other};
         pimpl_.swap(copy.pimpl_);
         return *this;
      }

      Shape(Shape&&) = default;
      Shape& operator=(Shape&&)=default;

   private:
   struct Concept //External Polymorphism design pattern
   {
      virtual ~Concept() = default;
      virtual void draw(/*parameters*/) const = 0;
      virtual std::unique_ptr<Concept> clone() const = 0; // Prototype design pattern
   };

   template <typename ShapeT>
   struct Model : public Concept
   {
      explicit Model(ShapeT shape) : shape_{shape}{}
      void draw() const override{free_draw(shape_); }
      std::unique_ptr<Concept> clone() const override {return std::make_unique<Model>(*this);}

      ShapeT shape_;
   };

   std::unique_ptr<Concept> pimpl_; // Bridge design pattern
};

void free_draw( Shape const& shape )
{
   shape.draw();
}


//---- <Circle.h> ---------------------------------------------------------------------------------

//#include <Point.h>

class Circle
{
 public:
   explicit Circle( double radius )
      : radius_( radius )
      , center_()
   {}

   double radius() const { return radius_; }
   Point  center() const { return center_; }

 private:
   double radius_;
   Point center_;
};


//---- <Square.h> ---------------------------------------------------------------------------------

//#include <Point.h>

class Square
{
 public:
   explicit Square( double side )
      : side_( side )
      , center_()
   {}

   double side() const { return side_; }
   Point center() const { return center_; }

 private:
   double side_;
   Point center_;
};


//---- <Draw.h> -----------------------------------------------------------------------------------

class Circle;
class Square;

void free_draw( Circle const& circle );
void free_draw( Square const& square );


//---- <Draw.cpp> ---------------------------------------------------------------------------------

//#include <Draw.h>
//#include <Circle.h>
//#include <Square.h>
//#include <GraphicsLibrary.h>
#include <iostream>

void free_draw( Circle const& circle )
{
   std::cout << "circle: radius=" << circle.radius() << std::endl;
}

void free_draw( Square const& square )
{
   std::cout << "square: side=" << square.side() << std::endl;
}


//---- <TestDrawStrategy.h> -----------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <GraphicsLibrary.h>
#include <iostream>

class TestDrawStrategy
{
 public:
   explicit TestDrawStrategy( Color color ) : color_(color) {}

   void operator()( Circle const& circle ) const
   {
      std::cout << "circle: radius=" << circle.radius()
                << ", color = " << to_string(color_) << '\n';
   }

   void operator()( Square const& square ) const
   {
      std::cout << "square: side=" << square.side()
                << ", color = " << to_string(color_) << '\n';
   }

 private:
   Color color_;
};


//---- <Shapes.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
#include <vector>

using Shapes = std::vector<Shape>;


//---- <DrawAllShapes.h> --------------------------------------------------------------------------

//#include <Shapes.h>

void drawAllShapes( Shapes const& shapes );


//---- <DrawAllShapes.cpp> ------------------------------------------------------------------------

//#include <DrawAllShapes.h>
//#include <Draw.h>

void drawAllShapes( Shapes const& shapes )
{
   for( auto const& shape : shapes )
   {
      free_draw( shape );
   }
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <Shapes.h>
//#include <DrawAllShapes.h>
#include <cstdlib>

int main()
{
   Shapes shapes{};

   shapes.emplace_back( Circle{ 2.3 } );
   shapes.emplace_back( Square{ 1.2 } );
   shapes.emplace_back( Circle{ 4.1 } );

   drawAllShapes( shapes );

   return EXIT_SUCCESS;
}

