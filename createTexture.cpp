#include "SimpleImage.h"
void createTexture()
{
   //background mask makes background noisy and not just a solid color
   SimpleImage background("brush_strokes/background.png");

   //brush strokes used to create masks
   SimpleImage brush1("Brush_strokes/brush09.png");
   SimpleImage brush2("Brush_strokes/brush02.png");
   SimpleImage brush3("Brush_strokes/brush08.png");
   SimpleImage brush4("Brush_strokes/brush12.png");
   
   //gradients used to create colors on the masks
   SimpleImage gradient1("gradients/gradient01.png");
   SimpleImage gradient2("gradients/gradient02.png");
   SimpleImage gradient3("gradients/gradient04.png");
   SimpleImage gradient4("gradients/gradient09.png");

   //the masks used to create the opacity and color masks
   SimpleImage mask1(brush1.width()*3, brush1.height()*3, RGBColor(0,0,0));
   SimpleImage mask2(brush1.width()*3, brush1.height()*3, RGBColor(0,0,0));
   SimpleImage mask3(brush1.width()*3, brush1.height()*3, RGBColor(0,0,0));
   SimpleImage mask4(brush1.width()*3, brush1.height()*3, RGBColor(0,0,0));
   SimpleImage mask5(brush1.width()*3, brush1.height()*3, RGBColor(0,0,0));
   SimpleImage mask6(brush1.width()*3, brush1.height()*3, RGBColor(0,0,0));
   
   //color masks used to create the final layers
   SimpleImage mask1color(brush1.width()*3, brush1.height()*3, RGBColor(0,0,0));
   SimpleImage mask2color(brush1.width()*3, brush1.height()*3, RGBColor(0,0,0));
   SimpleImage mask3color(brush1.width()*3, brush1.height()*3, RGBColor(0,0,0));
   SimpleImage mask4color(brush1.width()*3, brush1.height()*3, RGBColor(0,0,0));
   SimpleImage mask5color(brush1.width()*3, brush1.height()*3, RGBColor(0,0,0));
   SimpleImage mask6color(brush1.width()*3, brush1.height()*3, RGBColor(0,0,0));
   
   //result image
   SimpleImage result(brush1.width()*3, brush1.height()*3, RGBColor(1,1,1));

   int j, y, i, x;

   float opacity1=.9;
   float opacity2=.9;
   float opacity3=.7;

   RGBColor back(.8,.85,.25);
   RGBColor red(1,0,0);
   RGBColor green(.1,.85,.1);
   RGBColor yellow(.75,.9,.1);
   RGBColor orange(.80,.6,.1);
   RGBColor blue(0,0,1);
   RGBColor black(0,0,0);
   RGBColor white(1,1,1);
   RGBColor almostBlack(0.1, 0.1, 0.1);

   for(j=0; j < result.height(); j++)
   {
      for(i=0; i < result.width(); i++)
      {
	 RGBColor c = (result(i,j)*(white-background(i,j)))+((background(i,j)*back));
	 result.set(i,j,c);
      }
   }
   for(j=0, y=0; j < mask1.height(); j++, y++)
   {
      if(y>=brush1.height())
      {
	 y=0;
      }
      for(i=0, x=0; i < mask1.width(); i++, x++)
      {
	 if(x>=brush1.width())
	 {
	    x=0;
	 }
	 RGBColor o = brush1(x,y)*opacity1;
	 mask1.set(i,j,o);
	 RGBColor c = brush1(x,y)*gradient1(i,j);
	 mask1color.set(i,j,c);
      }
   }
   for(j=0, y=0; j < mask2.height(); j++, y+=2)
   {
      if(y>=brush2.height())
      {
	 y=0;
      }
      for(i=0, x=0; i < mask2.width(); i++, x+=2)
      {
	 if(x>=brush2.width())
	 {
	    x=0;
	 }
	 RGBColor o = brush2(x,y)*opacity2;
	 mask2.set(i,j,o);
	 RGBColor c = brush2(x,y)*gradient4(i,j);
	 mask2color.set(i,j,c);
      }
   }
   for(j=0, y=50; j < mask3.height(); j++, y+=2)
   {
      if(y>=brush3.height())
      {
	 y=0;
      }
      for(i=0, x=100; i < mask3.width(); i++, x+=2)
      {
	 if(x>=brush3.width())
	 {
	    x=0;
	 }
	 RGBColor o = brush3(x,y)*opacity3;
	 mask3.set(i,j,o);
	 RGBColor c = brush3(x,y)*green;
	 mask3color.set(i,j,c);
      }
   }
   for(j=0, y=0; j < mask4.height(); j++, y+=2)
   {
      if(y>=brush3.height())
      {
	 y=0;
      }
      for(i=0, x=100; i < mask4.width(); i++, x+=2)
      {
	 if(x>=brush3.width())
	 {
	    x=0;
	 }
	 RGBColor o = brush3(x,y)*opacity3;
	 mask4.set(i,j,o);
	 RGBColor c = brush3(x,y)*yellow;
	 mask4color.set(i,j,c);
      }
   }
   for(j=0, y=0; j < mask5.height(); j++, y+=2)
   {
      if(y>=brush3.height())
      {
	 y=0;
      }
      for(i=0, x=0; i < mask5.width(); i++, x+=2)
      {
	 if(x>=brush3.width())
	 {
	    x=0;
	 }
	 RGBColor o = brush3(x,y)*opacity3;
	 mask5.set(i,j,o);
	 RGBColor c = brush3(x,y)*gradient1(i,j);
	 mask5color.set(i,j,c);
      }
   }
   for(j=0, y=90; j < mask6.height(); j++, y+=2)
   {
      if(y>=brush4.height())
      {
	 y=0;
      }
      for(i=0, x=120; i < mask6.width(); i++, x+=2)
      {
	 if(x>=brush4.width())
	 {
	    x=0;
	 }
	 RGBColor o = brush4(x,y)*opacity2;
	 mask6.set(i,j,o);
	 RGBColor c = brush4(x,y)*orange;
	 mask6color.set(i,j,c);
      }
   }
   for(j=0; j < result.height(); j++)
   {
      for(i=0; i < result.width(); i++)
      {
	 RGBColor c = (result(i,j)*(white-mask1(i,j)))+((mask1color(i,j)*mask1(i,j)));
	 c=(c*(white-mask6(i,j)))+((mask6color(i,j)*mask6(i,j)));
	 c=(c*(white-mask2(i,j)))+((mask2color(i,j)*mask2(i,j)));
	 c=(c*(white-mask3(i,j)))+((mask3color(i,j)*mask3(i,j)));
	 c=(c*(white-mask4(i,j)))+((mask4color(i,j)*mask4(i,j)));
	 c=(c*(white-mask5(i,j)))+((mask5color(i,j)*mask5(i,j)));
	 result.set(i,j,c);
      }
   }
   result.save("textures/paintTexture.png");
}
