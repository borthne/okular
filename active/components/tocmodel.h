/***************************************************************************
 *   Copyright (C) 2007 by Pino Toscano <pino@kde.org>                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef TOCMODEL_H
#define TOCMODEL_H

#include <qabstractitemmodel.h>

namespace Okular {
class Document;
class DocumentSynopsis;
class DocumentViewport;
}

class TOCModelPrivate;

class TOCModel : public QAbstractItemModel
{
    Q_OBJECT

    /**
     * How many items are in this model
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)

    public:
        enum TOCRoles {
            PageRole = Qt::UserRole + 1,
            PageLabelRole = Qt::UserRole + 2
        };

        explicit TOCModel( Okular::Document *document, QObject *parent = 0 );
        virtual ~TOCModel();

        // reimplementations from QAbstractItemModel
        virtual int columnCount( const QModelIndex &parent = QModelIndex() ) const;
        virtual QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const;
        virtual bool hasChildren( const QModelIndex &parent = QModelIndex() ) const;
        virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
        virtual QModelIndex index( int row, int column, const QModelIndex &parent = QModelIndex() ) const;
        virtual QModelIndex parent( const QModelIndex &index ) const;
        virtual int rowCount( const QModelIndex &parent = QModelIndex() ) const;

        void fill( const Okular::DocumentSynopsis *toc );
        void clear();
        void setCurrentViewport( const Okular::DocumentViewport &viewport );

        bool isEmpty() const;

        QString externalFileNameForIndex( const QModelIndex &index ) const;
        Okular::DocumentViewport viewportForIndex( const QModelIndex &index ) const;
        QString urlForIndex( const QModelIndex &index ) const;

        int count() const {return rowCount();}

    Q_SIGNALS:
        void countChanged();

    private:
        // storage
        friend class TOCModelPrivate;
        TOCModelPrivate *const d;
};

#endif
