#include <qwidget.h>

inline int below(QWidget* w)
{
		return w->y() + w->height();
}

inline int right_of(QWidget* w)
{
		return w->x() + w->width();
}

inline void adjust_size(QWidget* w)
{
		w->setMinimumSize(w->sizeHint());
		w->setMaximumSize(w->sizeHint());
}

