/**     *************************************************************************
                          carddisplay.cpp  -  description
                             -------------------
    begin                : Tue Dec 28 1999
    copyright            : (C) 1999 by Luis Pedro Coelho
    email                : luis.coelho@netc.pt
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "general/helper.h" // must be before Qt's headers
#include "carddisplay.h"
#include <qpainter.h>
#include <strstream>
#include <kstddirs.h>

CardDisplay::cache_t CardDisplay::images;
CardDisplay::cache_t CardDisplay::selected_images;

CardDisplay::cleaner CardDisplay::cleaner_obj;

const int CardDisplay::CardWidth = 72;
const int CardDisplay::CardHeight = 96;


 CardDisplay::CardDisplay(Card ref_, QWidget *parent, const char *name )
        : QWidget(parent,name),
          ref(ref_),
          isSelected(false),
          isSelectable(false)
 {
        setMinimumSize(CardWidth,CardHeight);
        setMaximumSize(CardWidth,CardHeight);
        unselect();

 }

  QPixmap* CardDisplay::get_image(Card ref)
  {
        cache_t::iterator res = images.find(ref);
        if (res == images.end())
        {
                res = load(ref);
        }
        return res->second;
  }

  QPixmap* CardDisplay::get_selected_image(Card ref)
  {
        cache_t::iterator res = selected_images.find(ref);
        if (res == selected_images.end())
        {
                res = load_selected(ref);
        }
        return res->second;
  }

  void CardDisplay::unload_all()
  {
        LOG_PLACE() << " doing cleanup.\n";
        cache_t::iterator ref;
        for (ref = images.begin(); ref != images.end(); ++ref)
        {
               delete ref->second;
               ref->second = 0; // no dangling pointer even if some delete throws
        }
        images.clear();
        for (ref = selected_images.begin(); ref != selected_images.end();++ref)
        {
                delete ref->second;
                ref->second  = 0;
        }
        selected_images.clear();
  }

  CardDisplay::cache_t::iterator CardDisplay::load(const Card ref)
  {
        massert (images.find(ref) == images.end()); // it must not be loaded

        char buf[256];
        std::ostrstream out(buf,sizeof(buf));
        out << "hearts/" << ref << ".bmp" << std::ends;
		
        QPixmap* res = new QPixmap(locate("data",buf));
        if (res->isNull()) std::cerr << "Unable to load card: " << ref << ", (trying at location " << buf << "). Please check your installation.\n";
        images[ref] = res;
        return images.find(ref);
  }

  CardDisplay::cache_t::iterator CardDisplay::load_selected(Card ref)
  {

        massert (selected_images.find(ref) == selected_images.end()); // it must not be loaded

      LOG_PLACE() << " loading: " << ref << ".\n";

        QPixmap* res = new QPixmap(*get_image(ref)); // since it is probably loaded anyway, this is better
        massert(res); // new should throw
        if (res->isNull()) std::cerr << "Unable to get image " << ref << std::endl;

        // paint the image
        QPainter painter;
        painter.begin(res);
        for (int x = 0; x < res->width(); x += 2)
        {
                for (int y = 0; y < res->height(); y += 2)
                {
                        painter.drawPoint(QPoint(x,y));
                }
        }
        painter.end();

        selected_images[ref] = res;
        return selected_images.find(ref);
  }

   void CardDisplay::select()
   {
        if (selectable() and !isSelected)
        {
                isSelected = true;
                repaint();
                emit selected(ref);
        }
   }

   void CardDisplay::paintEvent(QPaintEvent*)
   {
        QPainter p;
        p.begin(this);
        QPixmap* image = selected()? get_selected_image(ref) : get_image(ref);
        p.drawPixmap(0,0,*image);
        p.end();
   }

   void CardDisplay::unselect()
   {
        if (isSelected)
        {
                isSelected = false;
                repaint();
                emit unselected(ref);
        }
   }

   void CardDisplay::mousePressEvent(QMouseEvent*)
   {
        emit clicked(ref);
        if (selected()) unselect();
        else select();
   }

   void CardDisplay::setSelectable(bool s)
   {
        isSelectable = s;
        repaint();
   }

   void CardDisplay::setCard(Card r)
   {
        ref = r;
        repaint();
   }

   void CardDisplay::repaint()
   {
        QPaintEvent ev(this->rect());
        paintEvent(&ev);
   }
