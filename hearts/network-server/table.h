#ifndef TABLE_H
#define TABLE_H
#include <qobject.h>
#include <vector>
#include "network/tableid.h"

class Player;

class Table : public QObject
{
	Q_OBJECT
	public:
		typedef table_id id;
		//Table();
	
		Table( QObject* parent, QString name );
		bool full() const;
	
		Player* player( int idx ) const;
		QString name() const { return name_; }
		
	public slots:
		void addPlayer( Player* );
		void removePlayer( Player* );
		void delayedTableFull();
		
	signals:
		void tableFull( Table* );
		
	private slots:
		void removePlayer( QObject* );
	private:
		std::vector< Player* > players_;
		QString name_;
};
#endif // TABLE_H
